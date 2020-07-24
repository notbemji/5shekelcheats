#include "menu.hpp"

bool menu_locked = false;

void text(int x, int* y, std::string text, text_type type, int alpha = 255) {
	if (menu_locked)
		alpha *= 0.33f;
	color text_color;
	switch (type) {
		case info: text_color = color::yellow(alpha); break;
		case regular: text_color = color::white(alpha); break;
		case enabled: text_color = color::blue(alpha); break;
		case enabled_green: text_color = color::green(alpha); break;
		case warning: text_color = color::red(alpha); break;
		case extra:	text_color = color::turquoise(alpha); break;
		default: text_color = color::white(alpha); break;
	}
	render::text(x, *y, render::fonts::tahoma, text, false, text_color);
	*y += 15;
}

void option_bool(int x, int* y, std::string text, bool* option, int key, bool special = false, int alpha = 255) {
	if (menu_locked)
		alpha *= 0.33f;
	render::text(x, *y, render::fonts::tahoma, text, false, color::white(alpha));
	if (GetAsyncKeyState(key) & 1 && !menu_locked)
		*option = !(*option);
	render::text(x + 100, *y, render::fonts::tahoma, *option ? "ON" : "OFF", false, *option ? (special ? color::turquoise(alpha) : color::blue(alpha)) : color::white(alpha));
	*y += 15;
}

void option_int(int x, int* y, std::string text, int* option, std::vector<std::string> aliases, int key, bool special = false, int alpha = 255) {
	if (menu_locked)
		alpha *= 0.33f;
	render::text(x, *y, render::fonts::tahoma, text, false, color::white(alpha));
	if (GetAsyncKeyState(key) & 1 && !menu_locked) {
		if (*option < aliases.size())
			*option += 1;
		if (*option >= aliases.size())
			*option = 0;
	}
	render::text(x + 100, *y, render::fonts::tahoma, aliases.at(*option), false, *option != 0 ? (special ? color::turquoise(alpha) : color::blue(alpha)) : color::white(alpha));
	*y += 15;
}

void menu::draw() {
	int screen[2];
	interfaces::engine->get_screen_size(screen[0], screen[1]);

	//float hud_scale = interfaces::console->get_convar("hud_scaling")->get_float();
	//int x = ((screen[0] / 100) * 19.2) * hud_scale; fix this shit pls

	int x = 300;
	int y = 5;

	if (GetAsyncKeyState(VK_INSERT) & 1)
		menu_locked = !menu_locked;

	static std::string name = "Gamer";
	if (csgo::local_player) {
		player_info_t player_info;
		interfaces::engine->get_player_info(interfaces::engine->get_local_player(), &player_info);
		name = player_info.name;
	}
	text(x, &y, "Hemlo " + name + " ))", text_type::info);
	std::stringstream address_string;
	address_string << interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
	text(x, &y, "LocalPlayer " + address_string.str(), text_type::info);

	y += 10;

	render::text(5, y, render::fonts::tahoma, "5$hekelCheats", false, color(255, 150, 150));

	option_bool(x, &y, "ESP:", &variables::esp, VK_NUMPAD7);
	option_bool(x, &y, "Bunnyhop:", &variables::bunnyhop, VK_NUMPAD8);
	option_int(x, &y, "Chams:", &variables::chams, std::vector<std::string>{ "OFF", "Visible", "XQZ" }, VK_NUMPAD9);
	option_bool(x, &y, "Rank ESP:", &variables::reveal_competitive_ranks, VK_NUMPAD4);
	option_bool(x, &y, "Backtrack:", &variables::backtrack, VK_NUMPAD5);
	option_bool(x, &y, "BT Chams:", &variables::backtrack_chams, VK_NUMPAD6);
	//option_int(x, &y, "AA:", &variables::antiaim, std::vector<std::string>{ "OFF", "Back Down", "Jitter Down", "180 Down" }, VK_NUMPAD1);
	option_int(x, &y, "Crosshair:", &variables::crosshair, std::vector<std::string>{ "OFF", "Static", "Recoil" }, VK_NUMPAD2);
}