/*
 * File:   antcheck_driver.c
 *
 * Created on 2022-09-03
 */

#define DEBUG

/* Standard Linux includes */
#include <linux/init.h>				// __init, __initdata, etc
#include <linux/module.h>			// Needed to be a module
#include <linux/kernel.h>			// Needed to be a kernel module
#include <linux/i2c.h>				// I2C functionality
#include <linux/slab.h>				// devm_kzalloc
#include <linux/types.h>			// Kernel datatypes
#include <linux/errno.h>			// EINVAL, ERANGE, etc
#include <linux/of_device.h>			// Device tree functionality
#include <linux/interrupt.h>
#include "vituralsar_driver.h"
#include <linux/regulator/consumer.h>
#include <linux/delay.h>
#include <linux/gpio.h>



/******************************************************************************
* Driver functions
******************************************************************************/


int sar_int_gpio;
static int sar_parse_dt(struct device *dev)
{
	struct device_node *np = dev->of_node;

	sar_int_gpio = of_get_named_gpio(np, "vituralsar,irq-gpio", 0);
	printk("antcheck sar_int_gpio=%d\n", sar_int_gpio);
	if (sar_int_gpio == 122) {
		printk("keven: parse irq gpio correctly\n ");
		return 0;
	} else {
		printk("keven: parse irq gpio incorrectly\n ");
		return -ENOMEM;
	}
}

int input_data = -1;
int old_data = -1;
static irqreturn_t sar_irq_handler(int irq, void *dev_id)
{
	struct vituralsar_data *sdata = dev_id;
	unsigned long irqflags = 0;

	spin_lock_irqsave(&sdata->irq_lock, irqflags);
	//sar_irq_disable(sdata);
	input_data = gpio_get_value(sar_int_gpio);
	printk("%s keven input_data = %d \n", __func__, input_data);
	if(input_data != old_data)
	{
		if (input_data == 0)
		{
			input_report_key(sdata->input_dev, KEY_ANT, 0);
			old_data = input_data;
		} else {
			input_report_key(sdata->input_dev, KEY_ANT, 1);
			old_data = input_data;
		}
	}
	printk("input_report_key ,status :%d\n", input_data);
	input_sync(sdata->input_dev);
	spin_unlock_irqrestore(&sdata->irq_lock, irqflags);
	//sar_irq_enable(sdata);

	printk("gpio_get_value : %d\n", input_data);

	return IRQ_HANDLED;
}

static s8 sar_request_irq(struct vituralsar_data *sdata)
{
	s32 ret = -1;
	const u8 irq_table[] = SAR_IRQ_TAB;
	printk("%s start ...", __func__);
	ret  = request_irq(sdata->client->irq, sar_irq_handler, irq_table[sdata->int_trigger_type], sdata->client->name, sdata);
	if (ret) {
		printk("Request IRQ failed!ERRNO:%d.", ret);
	} else {
		irq = sdata->client->irq;
		return 0;
	}
	return -ENOMEM;
}

static s8 sar_request_io_port(struct vituralsar_data *sdata)
{
	s32 ret = 0;

	ret = gpio_request(sar_int_gpio, "SAR_ANTCHECK_IRQ");
	if (ret) {
		printk("[GPIO]irq gpio request failed");
	}

	ret = gpio_direction_input(sar_int_gpio);
	if (ret) {
		printk("[GPIO]set_direction for irq gpio failed");
		goto err_irq_gpio_dir;
	}
	return 0;

err_irq_gpio_dir:
	gpio_free(sar_int_gpio);

	return ret;
}

static s8 sar_request_input_dev(struct vituralsar_data *sdata)
{
	s8 ret = -1;

	printk("start sar_request_input_dev ...\n");
	sdata->input_dev = input_allocate_device();
	if (sdata->input_dev == NULL) {
		printk("Failed to allocate input device.");
		return -ENOMEM;
	}

	__set_bit(EV_SYN, sdata->input_dev->evbit);
	__set_bit(EV_ABS, sdata->input_dev->evbit);
	__set_bit(EV_KEY, sdata->input_dev->evbit);


	sdata->input_dev->name = sar_name;
	sdata->input_dev->phys = sar_input_phys;
	sdata->input_dev->id.bustype = BUS_I2C;

	input_set_abs_params(sdata->input_dev, KEY_ANT, -1, 100, 0, 0);

	ret = input_register_device(sdata->input_dev);
	if (ret) {
		printk("Register %s input device failed", sdata->input_dev->name);
		return -ENODEV;
	}
	input_set_capability(sdata->input_dev, EV_KEY, KEY_ANT);

	return 0;
}
static struct proc_dir_entry *gpio_status;
#define GOIP_STATUS "antcheck"

static int gpio_proc_show(struct seq_file *file, void *data)
{

	printk("%s keven: antcheck sar_int_gpio was %d \n", __func__, sar_int_gpio);
	input_data = gpio_get_value(sar_int_gpio);
	printk("%s keven:  input_data=%d \n", __func__, input_data);
	seq_printf(file, "%d\n", input_data);

	return 0;
}


static int gpio_proc_open (struct inode *inode, struct file *file)
{
	return single_open(file, gpio_proc_show, inode->i_private);
}


static const struct file_operations gpio_status_ops = {
	.open = gpio_proc_open,
	.read = seq_read,
};

static int virtualsar_suspend(struct device *dev)
{
	int ret;

	ret = enable_irq_wake(irq);
	if (ret) {
		printk("virtualsar_suspend enable_irq_wake failed!\n");
		return -ENODEV;
	}

	return 0;
}

static int virtualsar_resume(struct device *dev)
{
	int ret;

	ret = disable_irq_wake(irq);
	if (ret) {
		printk("virtualsar_resume disable_irq_wake failed!\n");
		return -ENODEV;
	}

	return 0;
}

static int virtualsar_probe (struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = 0;
	struct vituralsar_data *sdata;

	if (!client) {
		pr_err("antcheck  %s - Error: Client structure is NULL!\n", __func__);
		return -EINVAL;
	}
	dev_info(&client->dev, "%s\n", __func__);

	/* Make sure probe was called on a compatible device */
	if (!of_match_device(virtualsar_dt_match, &client->dev)) {
		dev_err(&client->dev, "antcheck  %s - Error: Device tree mismatch!\n", __func__);
		return -EINVAL;
	}
	pr_debug("antcheck  %s - Device tree matched!\n", __func__);

	sdata = kzalloc(sizeof(*sdata), GFP_KERNEL);
	if (sdata == NULL) {
		printk("Alloc GFP_KERNEL memory failed.");
		return -ENOMEM;
	}
	//parse dt for irq
	if (client->dev.of_node) {
		ret = sar_parse_dt(&client->dev);
		if (!ret)
			printk("sar_parse_dt success\n");
	}
	//set irq Trigger mode
	sdata->int_trigger_type = SAR_INT_TRIGGER;

	sdata->client = client;
	spin_lock_init(&sdata->irq_lock);

	//request input dev
	ret = sar_request_input_dev(sdata);
	if (ret < 0) {
		printk("SAR request input dev failed");
	}

	//request io port
	if (gpio_is_valid(sar_int_gpio)) {
		ret = sar_request_io_port(sdata);
		if (ret < 0) {
			printk("SAR %s -request io port fail\n", __func__);
			return -ENOMEM;
		}
	} else {
		printk("SAR %s -gpio is not valid\n", __func__);
		return -ENOMEM;
	}


	//request irq
	ret = sar_request_irq(sdata);
	if (ret < 0) {
		printk("SAR %s -request irq fail\n", __func__);
	}

	__set_bit(EV_KEY, sdata->input_dev->evbit);
	__set_bit(EV_SYN, sdata->input_dev->evbit);
	__set_bit(KEY_ANT, sdata->input_dev->keybit);


	//enable irq
	printk("after sar_irq_enable,probe end \n");

	gpio_status = proc_create(GOIP_STATUS, 0644, NULL, &gpio_status_ops);
	if (gpio_status == NULL) {
		printk("tpd, create_proc_entry gpio_status_ops failed\n");
	}

	return 0;
}


static int __init virtualsar_init(void)
{
	int ret = 0;
	pr_debug("antcheck  %s - Start driver initialization...\n", __func__);

	ret = i2c_add_driver(&virtualsar_driver);
	printk("ret : %d\n", ret);
	return ret;
}

static void __exit virtualsar_exit(void)
{
	i2c_del_driver(&virtualsar_driver);
	pr_debug("SAR  %s - Driver deleted...\n", __func__);
}


/*******************************************************************************
 * Driver macros
 ******************************************************************************/
module_init(virtualsar_init);			// Defines the module's entrance function
//#endif
module_exit(virtualsar_exit);			// Defines the module's exit function

MODULE_LICENSE("GPL");				// Exposed on call to modinfo
MODULE_DESCRIPTION("VirtualSAR Driver");	// Exposed on call to modinfo
MODULE_AUTHOR("VirtualSar");			// Exposed on call to modinfo

