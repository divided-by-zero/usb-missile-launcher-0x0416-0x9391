/**
* @filename missile_launcher.c
*
* @brief Missile Launcher driver for idVendor: 0x0416 idProduct: 0x9391
* @copyright Copyright (C) 2012  Dirk Stanke, Dennis Labriola
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* @author Dirk Stanke <dirk@stanke.eu>, Dennis Labriola <l@briola.net>
*
*/

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/delay.h>

#define VENDOR_ID 0x0416
#define PRODUCT_ID 0x9391

#define LEFT 0x8
#define RIGHT 0x4
#define UP 0x2
#define DOWN 0x1
#define FIRE 0x10
#define STOP 0x0 


/* table of devices that work with this driver */
static struct usb_device_id id_table [] = {
	{ USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
	{ },
};
MODULE_DEVICE_TABLE (usb, id_table);

struct usb_launcher {
	struct usb_device	*udev;
	unsigned char left;
	unsigned char right;
	unsigned char up;
	unsigned char down;
	unsigned char fire;
	unsigned char stop;
};

static struct usb_launcher* launcher = {0};

/**
* @brief Invoked function if the "left-file" is read
* @return Returns the current value of the "left-file"
*/
static ssize_t show_left(struct device *dev, struct device_attribute *attr, char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->left);   
}

/**
* @brief Invoked function if something is stored in "left-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_left(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;
    
    unsigned char direction[] = {0x5f, LEFT, 0xe0, 0xff, 0xfe};
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	
		launcher->left = 0;
		    
		retval = usb_control_msg(
		            launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                 );
                 
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        } 
	}
		
	if (sysfs_streq(buf, "1")){
	
	    launcher->left = 1;
	
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
       retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            direction,
                                                sizeof(direction),
                                                    2000
                );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }
    }
    
    return count;
}

/**
* @brief Invoked function if the "right-file" is read
* @return Returns the current value of the "right-file"
*/
static ssize_t show_right(struct device *dev, struct device_attribute *attr, char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->right);   

}

/**
* @brief Invoked function if something is stored in "right-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_right(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;
  
    unsigned char direction[] = {0x5f, RIGHT, 0xe0, 0xff, 0xfe};
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	
		launcher->right = 0;
		
		retval = usb_control_msg(
		            launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                 );
                 
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        } 
	}
		
	if (sysfs_streq(buf, "1")){
	    
	    launcher->right = 1;
	    
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
       retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            direction,
                                                sizeof(direction),
                                                    2000
                    );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }       
	}
	
    return count;
}

/**
* @brief Invoked function if the "up-file" is read
* @return Returns the current value of the "up-file"
*/
static ssize_t show_up(struct device *dev, struct device_attribute *attr, char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->up);   
}

/**
* @brief Invoked function if something is stored in "up-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_up(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;

    unsigned char direction[] = {0x5f, UP, 0xe0, 0xff, 0xfe};
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	
		launcher->up = 0;
		
		retval = usb_control_msg(
		            launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                 );
                 
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        } 
	}
		
	if (sysfs_streq(buf, "1")){
	    
	    launcher->up = 1;
	    
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
       retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            direction,
                                                sizeof(direction),
                                                    2000
                    );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }
        
	}
	
    return count;
}

/**
* @brief Invoked function if the "down-file" is read
* @return Returns the current value of the "down-file"
*/
static ssize_t show_down(struct device *dev, struct device_attribute *attr,	char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->down);   

}

/**
* @brief Invoked function if something is stored in "down-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_down(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;

    unsigned char direction[] = {0x5f, DOWN, 0xe0, 0xff, 0xfe};
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	 
		launcher->down = 0;
		
		retval = usb_control_msg(
		            launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                 );
                 
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        } 
	}
		
	if (sysfs_streq(buf, "1")){
	
	    launcher->down = 1;
	    
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
       retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            direction,
                                                sizeof(direction),
                                                    2000
                    );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }
        
	}
	
    return count;
}

/**
* @brief Invoked function if the "fire-file" is read
* @return Returns the current value of the "fire-file"
*/
static ssize_t show_fire(struct device *dev, struct device_attribute *attr, char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->fire);   
}

/**
* @brief Invoked function if something is stored in "fire-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_fire(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;
    
    unsigned char direction[] = {0x5f, FIRE, 0xe0, 0xff, 0xfe};
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	
		launcher->fire = 0;
		
		retval = usb_control_msg(
		            launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                 );
                 
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        } 
	}
		
	if (sysfs_streq(buf, "1")){
	
	    launcher->fire = 1;
	    
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
        retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            direction,
                                                sizeof(direction),
                                                    2000
                    );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }
         
	}
	
    return count;
}

/**
* @brief Invoked function if the "stop-file" is read
* @return Returns the current value of the "stop-file"
*/
static ssize_t show_stop(struct device *dev, struct device_attribute *attr, char *buf){

    struct usb_interface *intf;
    
    intf = to_usb_interface(dev);
    launcher = usb_get_intfdata(intf);
    
    return sprintf(buf, "%d\n", launcher->stop);   
}

/**
* @brief Invoked function if something is stored in "stop-file"
* @return Returns the number of bytes stored.
*/
static ssize_t store_stop(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count){
			 
    int retval;
    struct usb_interface* intf;
    
    unsigned char stop[] = {0x5f, STOP, 0xe0, 0xff, 0xfe};
    intf = to_usb_interface(dev);                       
    launcher = usb_get_intfdata(intf);
    
	if (sysfs_streq(buf, "0")){
	
		launcher->stop = 0;

	}
		
	if (sysfs_streq(buf, "1")){
	
	    launcher->stop = 1;
	    
		/*int usb_control_msg(
		        struct usb_device *dev, 
		            unsigned int pipe,
                        _ _u8 request, 
                            _ _u8 requesttype,
                                _ _u16 value, 
                                    _ _u16 index,
                                        void *data, 
                                            _ _u16 size, 
                                            int timeout);*/
	     
        retval = usb_control_msg(
	                launcher->udev,
                        usb_sndctrlpipe(launcher->udev, 0),
                            0x09,
                                0x21,
                                    0x0300,
                                        0x00,
                                            stop,
                                                sizeof(stop),
                                                    2000
                    );
	  
        if(retval < 0){
            pr_alert("error while ctrl transfer");
        }
         
	}
	
    return count;
}

/* Helper macros for creating the device attributes */
static DEVICE_ATTR(left, 0666, show_left, store_left);
static DEVICE_ATTR(right, 0666, show_right, store_right);
static DEVICE_ATTR(up, 0666, show_up, store_up);
static DEVICE_ATTR(down, 0666, show_down, store_down);
static DEVICE_ATTR(fire, 0666, show_fire, store_fire);
static DEVICE_ATTR(stop, 0666, show_stop, store_stop);

/**
* @brief Function called when the USB core has found the USB device.
* All it needs to do is initialize the device and create the sysfs files, in the proper location.
* @return Returns 0 on succes, -ENOMEM on error.  
*/
static int launcher_probe(struct usb_interface *interface, const struct usb_device_id *id){

	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_launcher *dev = NULL;
	int retval = -ENOMEM;
	int ret;

	dev = kmalloc(sizeof(struct usb_launcher), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}
	memset (dev, 0x00, sizeof (*dev));

	dev->udev = usb_get_dev(udev);
	
	/* save our data pointer in this interface device */
	usb_set_intfdata (interface, dev);
	
	
	if ((ret = device_create_file(&interface->dev, &dev_attr_left)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}
	if ((ret = device_create_file(&interface->dev, &dev_attr_right)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}
	if ((ret = device_create_file(&interface->dev, &dev_attr_up)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}
	if ((ret = device_create_file(&interface->dev, &dev_attr_down)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}
	if ((ret = device_create_file(&interface->dev, &dev_attr_fire)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}
	if ((ret = device_create_file(&interface->dev, &dev_attr_stop)) < 0){
	    err("Error while file creation. Error number %d", ret);
	}

	dev_info(&interface->dev, "USB Launcher device now attached\n");
	
	return 0;

error:
	kfree(dev);
	return retval;
	
}

/**
* @brief Function called when the USB device has been disconnected.
* It removes the files created by launcher_probe() and frees the used
* memory
*/
static void launcher_disconnect(struct usb_interface *interface){

    struct usb_launcher *dev;

	dev = usb_get_intfdata (interface);
	usb_set_intfdata (interface, NULL);

	device_remove_file(&interface->dev, &dev_attr_left);
	device_remove_file(&interface->dev, &dev_attr_right);
	device_remove_file(&interface->dev, &dev_attr_up);
	device_remove_file(&interface->dev, &dev_attr_down);
	device_remove_file(&interface->dev, &dev_attr_fire);
    device_remove_file(&interface->dev, &dev_attr_stop);
    
    /* Frees the memory of the device */
	usb_put_dev(dev->udev);

	kfree(dev);

	dev_info(&interface->dev, "Missile Launcher disconnected\n");
}


/* 
	Defines the owner, the name,
	the	function to be called when this device is plugged in(launcher_probe)
	the function to be called when the device is disconnected(launcher_disconnect)
	and our table of devices that work with this driver(id_table)
*/
static struct usb_driver launcher_driver = {
	/*.owner =	THIS_MODULE, */
	.name =		"missilelauncher",
	.probe =	launcher_probe,
	.disconnect =	launcher_disconnect,
	.id_table =	id_table,
};

/**
* @brief Initialization function called when the module is loaded
* Registers our usb_driver
* @return On success returns the value given by usb_register(), on error the error number
*/
static int __init launcher_init(void){

	int retval = 0;

	retval = usb_register(&launcher_driver);
	if (retval){
		err("usb_register failed. Error number %d", retval);
	}
	pr_alert("USB Missile Launcher drivers loaded");
    pr_alert("idVendor: 0x0416 idProduct: 0x9391\n");
    
	return retval;
}

/**
* @brief Exit function called when the driver is unloaded.
* Deregisters the usb_driver
*/
static void __exit launcher_exit(void){

    usb_deregister(&launcher_driver);
}

module_init(launcher_init);
module_exit(launcher_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Missile launcher drivers(0x416,0x9391)");
MODULE_AUTHOR("Dirk Stanke, Dennis Labriola");

