/*
 * Copyright (C) 2011 Vikram Pandita
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>

#include "usb.h"

int match_omap4_device(usb_ifc_info *ifc)
{
	if (ifc->dev_vendor != 0x06c2)
		return -1;
	if (ifc->dev_product != 0x0040)
		return -1;
	printf("\nFound: Phidget: vid(%x) pid(%x)\n", ifc->dev_vendor, ifc->dev_product);
	return 0;
}

int main(int argc, char **argv)
{
	usb_handle *usb;
	int once = 1;
	static int count = 0;
	char data[4];
	unsigned char port;

	fprintf(stderr,"?\n");
	if (argc != 3) {
		fprintf(stderr,"usage:test  port (1/0)\n\n");
		return 0;
	}

	memset(data, 0, sizeof(data));
	port = atoi(argv[1]);
	if (port >= 4) {
		printf("\n wrong prot %d\n", port);
		exit (0);
	}
	data[port] = !atoi(argv[2]);

	printf("\n Port = %d put to %s\n", port, (!atoi(argv[2]))?"off":"on");
	for (;;) {
		usb = usb_open(match_omap4_device);
		if (usb) {
			usb_control_write(usb, data, 4);
			exit(0);
		}
		usleep(1000);
	}

	return -1;
}
