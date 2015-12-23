/*
 * based on
 * k480_conf.c by Emir Bucalovic <betoneful@gmail.com> www.betoneful.com
 *          https://betoneful.com/tech/logitech-k480-on-ubuntu-and-fn-buttons-default-behaviour/
 * k810_conf.c by Mario Scholz <mario@expires-2013.mail.trial-n-error.net>
 *          http://www.trial-n-error.de/posts/2012/12/31/logitech-k810-keyboard-configurator/
 * pairing_tool.c from Benjamin Tissoires <benjamin.tissoires@gmail.com>
 *          see also https://lkml.org/lkml/2011/9/22/367
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
 */
#include <linux/input.h>
#include <linux/hidraw.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define HID_VENDOR_ID_LOGITECH			(__u32)0x046d
#define HID_DEVICE_ID_K380              (__s16)0xb342


const char k380_seq_fkeys_on[]  = {0x10, 0xff, 0x0b, 0x1e, 0x00, 0x00, 0x00};
const char k380_seq_fkeys_off[] = {0x10, 0xff, 0x0b, 0x1e, 0x01, 0x00, 0x00};

const char opt_on[]  = "on";
const char opt_off[] = "off";

void send(const int fd, const char * buf, const int len)
{
	int res;

	/* Send sequence to the Device */
	res = write(fd, buf, len);

	if (res < 0)
	{
		printf("Error: %d\n", errno);
		perror("write");
	}
	else if (res == len)
       	{
		// printf("Configuration sent.\n");
	}
	else
	{
		errno = ENOMEM;
		printf("write: %d were written instead of %d.\n", res, len);
	}
}

int main(int argc, char **argv)
{
	int fd;
	int res;
	struct hidraw_devinfo info;
	const char * seq;
	char *dev = NULL;
	int flag_fkeys = 1;
	int c;

	if (argc < 5)
	{
		printf("Logitech Keyboard Configurator (by trial-n-error)\n\n");
		printf("Usage: %s -d /dev/hidraw{0,1,...} -f {on|off}:\n\n", argv[0]);
		printf("-d /dev/hidrawX\n"
		       "   Path to hidraw device. Determine by e.g.:\n"
		       "     ls /sys/class/hidraw/hidraw*/device/uevent\n"
		       "   and/or\n"
		       "     cat /sys/class/hidraw/hidraw*/device/uevent\n");
		printf("-f <on|off>\n"
		       "   To enable direct access to F-keys.\n");
		printf("\n");
	}

	while ((c = getopt (argc, argv, "d:f:")) != -1)
	{
		switch (c)
		{
			case 'd':
				dev = optarg;
				break;
			case 'f':
				if (strcmp(opt_on, optarg) == 0)
				{
					flag_fkeys = 1;
				}
				else if (strcmp(opt_off, optarg) == 0)
				{
					flag_fkeys = 0;
				}
				else
				{
					fprintf (stderr, "Option -%c requires argument '%s' or '%s'.\n", optopt, opt_on, opt_off);
					return 1;
				}
				break;
			case '?':
				if (optopt == 'f')
				{
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				}
				else if (isprint (optopt))
				{
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				}
				else
				{
					fprintf (stderr,
							"Unknown option character `\\x%x'.\n",
							optopt);
				}
				return 1;
			default:
				abort ();
		}
	}

	/* Open the Device with non-blocking reads. */
	fd = open(dev, O_RDWR|O_NONBLOCK);
	if (fd < 0)
	{
		perror("Unable to open device");
		return 1;
	}

	/* Get Raw Info */
	res = ioctl(fd, HIDIOCGRAWINFO, &info);
	if (res < 0)
	{
		perror("error while getting info from device");
	}
	else
       	{
		if (info.bustype != BUS_BLUETOOTH || 
		    info.vendor  != HID_VENDOR_ID_LOGITECH ||
		    info.product != HID_DEVICE_ID_K380)
		{
			errno = EPERM;
			perror("The given device is not a supported "
			       "Logitech keyboard");
			printf("Product : %x", info.product);

			return 1;
		}
	}

	if (flag_fkeys)
	{
		printf("Sending ON: \n");
		send(fd, k380_seq_fkeys_on,  sizeof(k380_seq_fkeys_on));
	}
	else
	{
		printf("Sending OFF: \n");
		send(fd, k380_seq_fkeys_off, sizeof(k380_seq_fkeys_off));
	}

	close(fd);
	return 0;
}
