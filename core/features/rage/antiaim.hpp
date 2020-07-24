#pragma once
#include "../../../dependencies/utilities/csgo.hpp"

namespace antiaim {
	namespace base {
		void run(c_usercmd* cmd);
	}

	namespace fakelag {
		void run(bool* send_packet);
	}

	namespace fakeangles {
		void run(c_usercmd* cmd, bool* send_packet);
	}
}