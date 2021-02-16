#include <linux/module.h>

/* add header files to support character devices */
#include <linux/cdev.h>
#include <linux/fs.h>

/* device_create */
#include <linux/device.h>

/* Define Class Name, Device Name */
#define DEVICE_NAME		"my_char_device"
#define CLASS_NAME		"hello_class"

static struct class *hello_class;
static struct cdev my_dev;
dev_t dev;


static int my_dev_open (struct inode *inode, struct file *file)
{
	pr_info("%s is called.\n", __FUNCTION__);
	return 0;
}

static int my_dev_close (struct inode *inode, struct file *flie)
{
	pr_info("%s is called.\n", __FUNCTION__);
	return 0;
}

static long my_dev_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	pr_info("%s is called.\n", __FUNCTION__);
	pr_info("cmd:%d, arg:%ld\n", cmd, arg);
	return 0;
}

static const struct file_operations my_dev_ops = {
	.owner = THIS_MODULE,
	.open = my_dev_open,
	.release = my_dev_close,
	.unlocked_ioctl = my_dev_ioctl,
};


static int __init hello_init (void)
{
	int ret;
	int major;
	dev_t dev_no;
	struct device *hello_device;
	
        pr_info("Hello world init\n");
	
	ret = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
	if (ret < 0) {
		pr_info("Unable to allocate chrdev region\n");
		return ret;
	}

	/* Get the major number from the first device identifier */
	major = MAJOR(dev_no);

	/* Get the first device identifier, that matches with dev_no */
	dev = MKDEV(major, 0);

	pr_info("Allocated correctly with major number %d\n", major);

	cdev_init(&my_dev, &my_dev_ops);
	ret = cdev_add(&my_dev, dev, 1);
	if (ret < 0) {
		pr_info("Unable to add cdev\n");
		return ret;
	}

	/* Register the device class */
	hello_class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(hello_class)) {
		unregister_chrdev_region(dev, 1);
		cdev_del(&my_dev);
		pr_info("Failed to register device class\n");
		return PTR_ERR(hello_class);
	}
	pr_info("device class registered correctly\n");

	/* Create a device node named DEVICE_NAME associated a dev */
	hello_device = device_create(hello_class, NULL, dev, NULL, DEVICE_NAME);
	if (IS_ERR(hello_device)) {
		class_destroy(hello_class);
		unregister_chrdev_region(dev, 1);
		cdev_del(&my_dev);
		pr_info("Failed to create the device\n");
		return PTR_ERR(hello_device);
	}
	pr_info("The device is created correctly\n");

        return 0;
}

static void __exit hello_exit (void)
{
        pr_info("Hello world exit\n");
	device_destroy(hello_class, dev);
	class_destroy(hello_class);
	cdev_del(&my_dev);
	unregister_chrdev_region(dev, 1);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ttaem <ttaem1@gmail.com>");
MODULE_DESCRIPTION("This is a simple char device module");

