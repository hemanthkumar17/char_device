#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/ctype.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

int i;
int key=3;
int ch;
static char encrypted_message[100];
static char msg[100];

int open_file(struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	return 0;
}

ssize_t read_file(struct file *pfile,char __user *buffer,size_t length,loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	copy_to_user(buffer,encrypted_message,length);
        return 0;
}

ssize_t write_file(struct file *pfile,const char __user *buffer,size_t length,loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n",__FUNCTION__);
	copy_from_user(msg,buffer,length);
	i=0;
	while(i<length)
   	{ 		
		printk(KERN_INFO "%d, %d\n", i, msg[i]);	
		if (isupper(msg[i])) //Encrypt uppercase letters
		{
			if(msg[i]+key > 'Z')
				encrypted_message[i] = 'A' + msg[i] + key - 'Z';
			else
           			encrypted_message[i] = msg[i] + key;
		}
   		else  // Encrypt Lowercase letters 
		{
			if(msg[i]+key > 'z')
                                encrypted_message[i] = 'a' + msg[i] + key - 'z';
                        else
                                encrypted_message[i] = msg[i] + key;
		}
		i++;
		printk(KERN_INFO "Encoded: %d\n",encrypted_message[i]); 
   	}
	encrypted_message[i] = '\0';
	printk(KERN_INFO "Message: %s\n", encrypted_message);
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
