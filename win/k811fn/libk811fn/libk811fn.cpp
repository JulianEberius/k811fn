// libk811fn.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "libk811fn.h"

namespace K811fn {
	extern "C" {

		static const int LOGITECH = 0x046d;
		static const int K811 = 0xb317;
		static const int TARGET_USAGE = 1;
		static const int TARGET_USAGE_PAGE = 65280;

		static const unsigned char setNormalMsg[] = {0x10, 0xFF, 0x06, 0x14, 0x00, 0x00, 0x00};
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
					hid_close(handle);
					if (res != msgLength) {
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
	}
	
}

