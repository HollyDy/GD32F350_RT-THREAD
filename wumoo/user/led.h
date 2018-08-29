#ifndef __LED_H
#define __LED_H

#define LED_ON  (1)
#define LED_OFF (0)
#define LED1    (1)
#define LED2    (2)
#define LED3    (3)

void rt_LedConfig(void);
void rt_LedControl(int index, int cmd);
#endif

