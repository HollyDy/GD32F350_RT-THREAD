#include "led.h"
#include "gd32f3x0_gpio.h"
#include "gd32f3x0.h"
#include "gd32f3x0_rcu.h"

void rt_LedConfig(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, 
                  GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, 
                            GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10);
}

void rt_LedControl1(int cmd)
{
		if (cmd == LED_ON)
		{
				gpio_bit_set(GPIOB, GPIO_PIN_8); 
		}
		else
		{
				gpio_bit_reset(GPIOB, GPIO_PIN_8); 
		}
}

void rt_LedControl2(int cmd)
{
		if (cmd == LED_ON)
		{
				gpio_bit_set(GPIOB, GPIO_PIN_9); 
		}
		else
		{
				gpio_bit_reset(GPIOB, GPIO_PIN_9); 
		}
}

void rt_LedControl3(int cmd)
{
		if (cmd == LED_ON)
		{
				gpio_bit_set(GPIOB, GPIO_PIN_10); 
		}
		else
		{
				gpio_bit_reset(GPIOB, GPIO_PIN_10); 
		}
}

void rt_LedControl(int index, int cmd)
{
    switch (index)
    {
        case LED1:
        {
            if (cmd == LED_ON)
            {
                gpio_bit_set(GPIOB, GPIO_PIN_8); 
            }
            else
            {
                gpio_bit_reset(GPIOB, GPIO_PIN_8); 
            }
            break;
        }
        case LED2:
        {
            if (cmd == LED_ON)
            {
                gpio_bit_set(GPIOB, GPIO_PIN_9); 
            }
            else
            {
                gpio_bit_reset(GPIOB, GPIO_PIN_9); 
            }
            break;
        }
        case LED3:
        {
            if (cmd == LED_ON)
            {
                gpio_bit_set(GPIOB, GPIO_PIN_10); 
            }
            else
            {
                gpio_bit_reset(GPIOB, GPIO_PIN_10); 
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
