#include "antiaim.hpp"
#include "../../menu/variables.hpp"

int random(int min, int max) {
	static bool first = true;
	if (first) {
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void antiaim::base::run(c_usercmd* cmd) {
	if (!csgo::local_player)
		return;

	if (!variables::antiaim)
		return;

	if(cmd->buttons & in_attack ||
		cmd->buttons & in_use ||
		csgo::local_player->move_type() == movetype_ladder ||
		csgo::local_player->move_type() == movetype_noclip)
		return;

	float yaw_base;
	vec3_t engine_angles;
	interfaces::engine->get_view_angles(engine_angles);
	yaw_base = engine_angles.y;

	switch (variables::antiaim) {
		case 1:
			cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
			break;
		case 2:
			cmd->viewangles = vec3_t(89.f, yaw_base + 180.f, 0.f);
			cmd->viewangles.y += random(-35, 35);
			break;
		case 3:
			cmd->viewangles = vec3_t(89.f, yaw_base + (cmd->command_number % 2 ? -90.f : 90.f), 0.f);
			break;
		default: break;
	}
}

void antiaim::fakelag::run(bool* send_packet) {

}

void antiaim::fakeangles::run(c_usercmd* cmd, bool* send_packet) {

}
