#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

/* nReset：模块复位信号，输入。低电平有效，模块内部有 100K 上拉电阻和 100nF 对地电容。当模块
上电时或者出现故障时，MCU 需要对模块做复位操作，引脚拉低至少 100us，然后拉高或悬空复位。所以这里先尝试1000us看看情况 */
#define SLEEP_TIME_MS   1000

void main(void)
{
	const struct device *devB,*devA;
	//bool nRest_Low = 0;
	int ret;
    /*
	devA = device_get_binding("GPIOA");//这里设置GPIO组?
	if (devA == NULL) {
		return;
	}
	ret = gpio_pin_configure(devA, (gpio_pin_t)1, GPIO_OUTPUT_HIGH);
	if (ret < 0) {
		return;
	}*/

	devB = device_get_binding("GPIOB");//这里设置GPIO组?
	if (devB == NULL) {
		return;
	}

	ret = gpio_pin_configure(devB, (gpio_pin_t)1, GPIO_OUTPUT_HIGH);
	if (ret < 0) {
		return;
	}
    
	ret = gpio_pin_configure(devB, (gpio_pin_t)10, GPIO_OPEN_DRAIN);//Tx
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_configure(devB, (gpio_pin_t)11, GPIO_INPUT);//Rx
	if (ret < 0) {
		return;
	}
	
    gpio_pin_set(devB, (gpio_pin_t)1, 0);//nReset
	k_msleep(10);
	gpio_pin_set(devB, (gpio_pin_t)1, 1);
    k_msleep(100);
}