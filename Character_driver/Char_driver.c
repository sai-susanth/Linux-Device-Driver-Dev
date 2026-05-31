#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>

static dev_t dev_nr;
static const char *device_name = "susanth_char_device";
static struct cdev my_cdev;
static struct class *my_class;
static struct device *my_dev;
static const struct file_operations fops = {
};


static int my_init(void) {
	int status;
	pr_info("Module init called\n");
	status = alloc_chrdev_region(&dev_nr, 0, 1, device_name);

	if(status < 0) {
		pr_err("The range allocation failed\n");
		return status;
	}

	pr_info("Allocated the Major: %d and Minor:%d to the device\n",MAJOR(dev_nr),MINOR(dev_nr));
	
	cdev_init(&my_cdev, &fops);

	status = cdev_add(&my_cdev, dev_nr, 1);

	if(status < 0) {
		pr_err("cdev_add failed eventually failed to register the device file operations with the VFS\n");
		cdev_del(&my_cdev);
		unregister_chrdev_region(dev_nr, 1);
		return status;
	}

	pr_info("Sucessfully register the device file operations with the VFS layer\n");

	my_class = class_create("Susanth_class");

	if(!my_class) {
		pr_err("The class was failed to create\n");
		cdev_del(&my_cdev);
		unregister_chrdev_region(dev_nr, 1);
		return 0;
	}

	my_dev = device_create(my_class, NULL, dev_nr, NULL, "susanth_device_node%d",1);
	
	if(IS_ERR(my_dev)) {
		pr_err("Failed to create the device node\n");
		class_destroy(my_class);
		cdev_del(&my_cdev);
		unregister_chrdev_region(dev_nr, 1);
		return -1;
	}

	pr_info("Sucessfully created the device node in sysfs\n");


	return 0;
}

static void my_exit(void) {
	pr_info("Module exit called\n");
	device_destroy(my_class, dev_nr);
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev_nr, 1);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Susanth");
MODULE_DESCRIPTION("Minimal Character Driver");
