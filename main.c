#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Dummy module");
MODULE_AUTHOR("Julien Heulot");
MODULE_VERSION("1. O");


unsigned int irq_number_180, irq_number_107;

//Interruptionn reception signal echo
static irq_handler_t gpio_irq_handler_180(unsigned int irq, void *dev_id, struct pt_regs *regs){
        s64 echo_debut=0,echo_fin=0;
        s64 echo_difference=0;
        s64 echo_distance=0;

        printk("Interrupt ECHO\n");

        echo_debut= ktime_get().tv64;
        while(gpio_get_value(180)==1)
        {
        //WAIT
        }

        echo_fin = ktime_get().tv64;
        echo_difference = echo_fin - echo_debut;
        echo_distance = echo_difference;

        printk("Debut      (exit) = %lld\n", echo_debut);
        printk("Fin        (exit) = %lld\n", echo_fin);
        printk("Difference (exit) = %lld\n", echo_difference);
        printk("Distance = %lld cm \n", echo_distance);

        return  (irq_handler_t) IRQ_HANDLED;
}


//Interruption user, e�mission signal trigger
static irq_handler_t gpio_irq_handler_107(unsigned int irq, void *dev_id, struct pt_regs *regs){
        s64 trigger_debut=0;
        s64 trigger_temps;
        trigger_temps=0;
        printk("Interrupt USER\n");

        gpio_set_value(181,1);
        trigger_debut = ktime_get().tv64;
        while(trigger_temps <trigger_debut + 10500)
        {
         trigger_temps = ktime_get().tv64;
        }
        gpio_set_value(181,0);
        trigger_temps = trigger_temps - trigger_debut;
        printk("Debut_trigger = %lld\n", trigger_debut);
        printk("Temps_trigger = %lld\n", trigger_temps);

        return  (irq_handler_t) IRQ_HANDLED;
}

static void kexit(void){
        gpio_set_value(181,0);
        gpio_set_value(180,0);
        free_irq(irq_number_180,NULL);
        free_irq(irq_number_107,NULL);
        gpio_free(181);
        gpio_free(180);
        gpio_free(107);

        printk("Exit dummy module \n");
}

static int kinit (void) {
        gpio_direction_input(180);
        gpio_direction_output(181,0);

        irq_number_180 = gpio_to_irq(180);
        if(request_irq(irq_number_180, (irq_handler_t) gpio_irq_handler_180, IRQF_TRIGGER_RISING, "my_gpio_irq_180",NULL) !=0)
        {
                printk("Can not request interrupt impossible: %d\n",irq_number_180);
                gpio_free(180);
        }
        irq_number_107 = gpio_to_irq(107);
        if(request_irq(irq_number_107, (irq_handler_t) gpio_irq_handler_107, IRQF_TRIGGER_RISING, "my_gpio_irq_107",NULL) !=0)
        {
                printk("Can not request interrupt impossible: %d\n",irq_number_107);
                gpio_free(107);
        }

        printk("Init dummy module \n");
        return 0;
}
module_init(kinit);
module_exit(kexit);