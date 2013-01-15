
all:
	gcc	usb_linux.c phy.c -o phy

clean:
	rm -rf *.o phy
	rm -rf cscope.out tags
