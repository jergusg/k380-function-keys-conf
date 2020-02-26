CC = gcc
PREFIX = /usr/local
BINDIR = $(DESTDIR)$(PREFIX)/bin
UDEVDIR = $(DESTDIR)/etc/udev/rules.d

all: k380_conf

k380_conf:
	$(CC) k380_conf.c -o k380_conf

reload:
	udevadm control --reload

install: k380_conf
	install -d $(BINDIR)
	install k380_conf fn_on.sh $(BINDIR)
	install -d $(UDEVDIR)
	echo "ACTION==\"add\", KERNEL==\"hidraw[0-9]*\", RUN+=\"$(BINDIR)/fn_on.sh /dev/%k\"" > $(UDEVDIR)/80-k380.rules

clean:
	rm k380_conf
