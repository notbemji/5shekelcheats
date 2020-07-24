#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "variables.hpp"

enum text_type {
	info = 0,
	regular,
	enabled,
	enabled_green,
	warning,
	extra
};

namespace menu {
	void draw();
}