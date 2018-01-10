/*
   driverLED.c

#define    KERN_EMERG     «<0>»     system is unusable             
#define    KERN_ALERT     «<1>»      action must be taken immediately  
#define    KERN_CRIT     «<2>»      critical conditions         
#define    KERN_ERR     «<3>»     error conditions             
#define    KERN_WARNING  «<4>»     warning conditions             
#define    KERN_NOTICE «<5>»     normal but significant condition  
#define    KERN_INFO     “<6>”     informational             
#define    KERN_DEBUG     «<7>»     debug-level messages         

*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/smp_lock.h>
#include "linuxgpio.h" // pour la simulation
//#include <asm/arch/gpio.h> // pour la carte fox
#include "driverioctl.h"
#include "ioportfoxg20.h"

#define BUFFMAX 56

static char buffer[BUFFMAX];
static unsigned int majeur = 190, mineur;

int mode = 0;

static int driverLED_open(struct inode *pinode,struct file *pfile) {
  
  printk(KERN_INFO"driver port Open\n");
  mineur = MINOR(pinode->i_rdev);
  majeur = MAJOR(pinode->i_rdev);
  printk(KERN_INFO"majeur %d mineur %d\n", majeur, mineur);
  
  /*
  if(pfile->f_flags == O_RDONLY)
  {
	  mode = 1;
  }
  else if(pfile->f_flags == O_WRONLY)
  {
	  mode = 2;
  }
  else if(pfile->f_flags == O_RDWR)
  {
	  mode = 3;
  }
  */

  return 0;
}

static int driverLED_release(struct inode *pinode,struct file *pfile) {

   printk(KERN_INFO"driver port Close\n");
   return 0;
}


static ssize_t driverLED_write(struct file *pfile, const char *poctets, size_t nb,loff_t *pos) {
  
/*
	if(mode > 1)
	{*/
		unsigned int bit_write = 0;
		printk(KERN_INFO"mondriver write %d \n", nb);
		
		//Get the number of bit received from the userland
		bit_write =  nb - copy_from_user(buffer, poctets, nb);
		//Update the postion
		*pos += bit_write;
		//Bytes used to light the leds
		unsigned char leds = 0;

		int place_holder = 8;
		
		// If the number of character received is greater than 8 + the end line character, the characters received are ignored
		if( nb <= 9 )
		{
			int i = 0;
			// test each charactère received if it is a 1 or a 0. In case if it is not one of them, the character is ignored.
			while( (i < 8) && i < (nb-1) )
			{
				// Construct the byte : first shift from right to left, then add the character received.
				if(*(buffer + i) == '1')
				{
					leds = (leds << 1) | 1;		
					place_holder--;	
				}
				else if (*(buffer + i) == '0')
				{
					leds = leds << 1;
					place_holder--;
				}
				i++;
			}
			// Shift from right to left the leds byte to have the first bit received at the Most significant bytes place. 
			//Only occur when the number of character received is lower than 8.
			leds = leds << place_holder;
		}
		printk(KERN_INFO"led = %x , bits lu = %d \n", leds, bit_write);
		
		// Shift the bit corresponding to the led on the right of the byte and extract the value
		gpio_set_value(67, (leds & 1));
		gpio_set_value(65, ((leds >> 1) & 1));
		gpio_set_value(64, ((leds >> 2) & 1));
		gpio_set_value(66, ((leds >> 3) & 1));
		gpio_set_value(59, ((leds >> 4) & 1));
		gpio_set_value(60, ((leds >> 5) & 1));
		gpio_set_value(57, ((leds >> 6) & 1));
		gpio_set_value(58, ((leds >> 7) & 1));
		return bit_write;
	/*}
	else
	{
		return -1;
	}*/
}


static ssize_t driverLED_read(struct file *pfile, char *poctets, size_t nb,loff_t *pos) {
/*if(mode == 1 || mode == 3)
	{*/
		printk(KERN_INFO"read %d bits\n", nb);
		
		// boolean flag for telling if the Switchs was read or not.
		static char is_read_finish = 0;
		
		//Send that 0 bit can be read to tell that the switch was read.
		if(is_read_finish == 1)
		{
			//reset the boolean for next time
			is_read_finish = 0;
			return 0;
		}
			
		
		int i = 0;
		
		//Read the Switchs pins 
		if(7 < nb)
		{
			//Convert pin state in character
			if(gpio_get_value(95) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(95) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(6 < nb)
		{
			if(gpio_get_value(94) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(94) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(5 < nb)
		{
			if(gpio_get_value(38) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(38) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(4 < nb)
		{
			if(gpio_get_value(39) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(39) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(3 < nb)
		{
			if(gpio_get_value(41) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(41) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(2 < nb)
		{
			if(gpio_get_value(42) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(42) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(1 < nb)
		{
			if(gpio_get_value(54) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(54) == 0)
			{
				buffer[*pos + i] = '0';
			}
			i++;
		}
		if(0 < nb)
		{
			if(gpio_get_value(43) == 1)
			{
				buffer[*pos + i] = '1';
			}
			else if (gpio_get_value(43) == 0)
			{
				buffer[*pos + i] = '0';
			}
		}
				
		//Get the number of bits read
		copy_to_user(poctets, buffer, nb);
		
		//Test if all switchs was read.
		is_read_finish = 1;
		//return buffer size the after reading the bits to trick cat command, because if not it will not display the charcater read
		return BUFFMAX;
	/*}
	else
	{
		return -1;
	}*/
}

static long driverLED_ioctl(struct file *pfile,unsigned int cmd,unsigned long arg) {
	
  lock_kernel();
  printk(KERN_INFO"driver port IOCTL cmd : %u\n",cmd);
  unlock_kernel();
  return 0;
}

struct file_operations driverLED_fops = {
	owner: THIS_MODULE,
	open:driverLED_open,
	write:driverLED_write,
	read:driverLED_read,
	unlocked_ioctl:driverLED_ioctl,
	release:driverLED_release,
};

// initialisation
static int __init driverLED_init(void) {
	printk("driverLED init %u\n", majeur);

	int errorcode = register_chrdev(majeur, "driverLED", &driverLED_fops);

	if(errorcode < 0)
	{
		printk(KERN_WARNING "driverLED error major\n");
		return errorcode;
	}

	printk(KERN_INFO "driverLED init success\n");
	return 0;
}

// suppression
static void __exit driverLED_cleanup(void) {
	printk("driverLED exit %u\n", majeur);
	unregister_chrdev(majeur, "driverLED");
}

// valeurs pour modinfo : description auteur licence
MODULE_DESCRIPTION("8 bits port driver with 190 major number");
MODULE_AUTHOR("Zeissloff Louis");
MODULE_LICENSE("GPL");


module_init(driverLED_init); // assignation de la fonction d'initialisation
module_exit(driverLED_cleanup); // assignation de la fonction de destruction
