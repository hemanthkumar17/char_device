#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/ctype.h>

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
		if (isupper(msg[i])) //Encrypt uppercase letters
		{
			ch = (int(msg[i]-'A')+key)%26;
           		encrypted_message[i] = char(ch)+'A';
		}
   		else  // Encrypt Lowercase letters 
		{
			ch = (int(msg[i]-'a')+key)%26;
   			encrypted_message[i] = char(ch)+'a';
		}
		i++;
   	}
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
