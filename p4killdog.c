#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

static int ttyACM0_fd = -1;

unsigned char sp_cnf_req[8] = {0x20, 0x06, 0x04, 0x06, 0x00, 0x08, 0x02, 0x00};
unsigned char wdog_close_req[3] = {0x07, 0x01, 0x30};

unsigned char hm_sp_cnf_req[13] = {0};
unsigned char hm_wdog_close_req[8] = {0};

char check_xor(const char device_data[], int len)
{
	char ret = 0;
	int i = 0;
	
	for (; i < len; i++)
	{
		ret ^= device_data[i];
	}
	return ret;
}

void hm_sp_cnf_req_fra(char hm_sp_cnf_req[], int len)
{
	int i = 0;
	hm_sp_cnf_req[0] = 0x7E;
	hm_sp_cnf_req[1] = 0x80;
	hm_sp_cnf_req[2] = 0x01;
	hm_sp_cnf_req[3] = check_xor(sp_cnf_req, sizeof(sp_cnf_req));
	
	for (; i < sizeof(sp_cnf_req); i++)
	{
		hm_sp_cnf_req[i+4] = sp_cnf_req[i];
	}
	hm_sp_cnf_req[len-1] = 0x7F;

	return;
}


void hm_wdog_close_req_fra(char hm_wdog_close_req[], int len)
{
	int i = 0;
	hm_wdog_close_req[0] = 0x7E;
	hm_wdog_close_req[1] = 0x80;
	hm_wdog_close_req[2] = 0x01;
	hm_wdog_close_req[3] = check_xor(wdog_close_req, sizeof(wdog_close_req));
	
	for (; i < sizeof(wdog_close_req); i++)
	{
		hm_wdog_close_req[i+4] = wdog_close_req[i];
	}
	hm_wdog_close_req[len-1] = 0x7F;	

	return;
}

void led_serial_init(void)
{
	int ret = -1;

	ttyACM0_fd = open("/dev/ttyACM0", O_RDWR);	
	if (ttyACM0_fd == -1)
	{
		perror("open /dev/ttyACM0 fail");
		exit(EXIT_FAILURE);
	}
	
	hm_wdog_close_req_fra(hm_wdog_close_req, sizeof(hm_wdog_close_req));
	ret = write(ttyACM0_fd, hm_wdog_close_req, sizeof(hm_wdog_close_req));
	if (ret == -1)
	{
		fprintf(stderr, "hm_wdog_close_req write /dev/ttyACM0 fail");
		return;	
	}

	hm_sp_cnf_req_fra(hm_sp_cnf_req, sizeof(hm_sp_cnf_req));
	ret = write(ttyACM0_fd, hm_sp_cnf_req, sizeof(hm_sp_cnf_req));
	if (ret == -1)
	{
		fprintf(stderr, "hm_sp_cnf_req write /dev/ttyACM0 fail");
		return;	
	}

	return;
}

int main(void)
{
	led_serial_init();

	return 0;
}


