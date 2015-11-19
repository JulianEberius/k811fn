// k811fnCLI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static const int LOGITECH = 0x046d;
static const int K811 = 0xb317;
static const int TARGET_USAGE = 1;
static const int TARGET_USAGE_PAGE = 65280;

static const unsigned char setNormalMsg[] = { 0x10, 0xFF, 0x06, 0x14, 0x00, 0x00, 0x00 };
static const unsigned char setSpecialMsg[] = { 0x10, 0xFF, 0x06, 0x14, 0x01, 0x00, 0x00 };
static const int msgLength = 7;

bool sendMessage(const unsigned char msg[]) {

	int res;
	hid_device *handle;
	struct hid_device_info *devs, *cur_dev;
	bool result = false;
	res = hid_init();
	devs = hid_enumerate(LOGITECH, K811);
	cur_dev = devs;
	while (cur_dev) {

		if (cur_dev->usage == TARGET_USAGE &&
			cur_dev->usage_page == TARGET_USAGE_PAGE) {
			handle = hid_open_path(cur_dev->path);

			res = hid_write(handle, msg, msgLength);
			if (res != msgLength) {
				printf("error: %ls\n", hid_error(handle));
			}
			
			hid_close(handle);
			if (res < 0) {
				result = false;
				break;
			}
			else {
				result = true;
				break;
			}

		}
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);
	hid_exit();
	return result;
}

bool setNormal(void)
{
	return sendMessage(setNormalMsg);
}

bool setSpecial(void)
{
	return sendMessage(setSpecialMsg);
}

int main(int argc, char* argv[])
{
	bool success = setNormal();
	int res;
	unsigned char buf[7];
	hid_device *handle;
	struct hid_device_info *devs, *cur_dev;

	static const int LOGITECH = 0x046d;
	static const int K811 = 0xb317;

	if (argc != 2) {
		printf("Usage: k811fn <-normal|-special>\n");
		return 1;
	}

	if (strcmp(argv[1], "-normal") == 0) {
		setNormal();
	}
	else if (strcmp(argv[1], "-special") == 0) {
		setSpecial();
	}
	else {
		printf("Usage: k811fn <-normal|-special>\n");
		return 1;
	}

	system("pause");
	return 0;
}


