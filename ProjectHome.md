This is a linux kernel module for the usb missile launcher idVendor: 0x0416 idProduct: 0x9391.
It makes use of the /sys/ pseudo-filesystem for user interaction. So you could easily write an user
program in many programming languages, to control the device. An example shell-script, how to control the device
is included. Also there is hot-plugging support via some udev rules(lookup the README file, how to set it up properly).