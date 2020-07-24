#include "../features.hpp"

void misc::movement::bunny_hop(c_usercmd* cmd) {
	if (!variables::bunnyhop)
		return;

	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
		cmd->buttons &= ~in_jump;
};

void misc::thirdperson() {
	static bool in_thirdperson = false;

	if (GetAsyncKeyState(VK_MBUTTON) & 1)
		in_thirdperson = !in_thirdperson;

	if (interfaces::input->camera_in_third_person = in_thirdperson)
		interfaces::input->camera_offset.z = 100;
}