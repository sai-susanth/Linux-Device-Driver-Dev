#include <linux/module.h>


static int __init curious_init(void)
{
 //using wrapper function - default kerenle level log to 6 -> KERN_INFO
  pr_info("Hi !!! Curious cat\n");
  return 0;
}

static void __exit curious_exit(void)
{
  printk(KERN_INFO "SEE YOU SOON, Offloading from kernel\n");
}

//module entry points
module_init(curious_init);
module_exit(curious_exit);

//module comments

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Susanth");
MODULE_DESCRIPTION("This is for practice");
