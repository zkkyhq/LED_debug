all:test

test:
	arm-hisiv100nptl-linux-gcc -o p4led p4ledfun.c p4led.c libiconv.a

clean:
	rm *~ test -rf
	rm /mnt/hgfs/share/led -rf
	cp ../led /mnt/hgfs/share/ -rf

