#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
int l;
static char msg[10];
int open_file(struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	return 0;
}

ssize_t read_file(struct file *pfile,char __user *buffer,size_t length,loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	l=0;
	//printk("%s",msg);
	while(l<length)
	{
		put_user(msg[l],buffer+l);
		l++;
	}
        return 0;
}

ssize_t write_file(struct file *pfile,const char __user *buffer,size_t length,loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	copy_from_user(msg,buffer,length);
	l=0;
	while(l<length)
	{
		msg[l]+=3;
		l++;
	}
	//printk("%s",msg);
        return length;
}

int close_file(struct inode *pinode,struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
        return 0;
}

struct file_operations file_ops = {
        .owner    = THIS_MODULE,
        .open     = open_file,
        .read     = read_file,
        .write    = write_file,
        .release  = close_file,
};
int char_module_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	register_chrdev(240,"Char Drive",&file_ops);
	return 0;
}
void char_module_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	unregister_chrdev(240,"Char Drive");
}

module_init(char_module_init);
module_exit(char_module_exit);
