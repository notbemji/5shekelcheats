#include "../features.hpp"

RECT get_bbox(player_t* player) {
	RECT box;
	vec3_t bottom, top;

	math::world_to_screen(player->abs_origin() - vec3_t(0, 0, 8), bottom); // vecorigin to absorigin for no lag in esp
	math::world_to_screen(player->get_hitbox_position(hitboxes::hitbox_head) + vec3_t(0, 0, 8), top);

	int mid = bottom.y - top.y;
	int width = mid / 4.f;

	box.bottom = top.y + mid;
	box.top = top.y;
	box.left = bottom.x - width;
	box.right = bottom.x - width + width * 2;

	return box;
}

void visuals::players::esp_draw() {
	if (!csgo::local_player)
		return;

	if (!variables::esp)
		return;

	for (uint32_t i = 0; i < interfaces::globals->max_clients; i++) {
		player_t* player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (player && player->is_player() && player->is_alive() && player != csgo::local_player && player->team() != csgo::local_player->team()) {
			static int alpha = 255;

			alpha += player->dormant() ? -1 : 25;

			if (alpha < 0)
				alpha = 0;
			if (alpha > 255)
				alpha = 255;

			RECT box = get_bbox(player);
			bool is_visible = csgo::local_player->can_see_player_pos(player, player->get_hitbox_position(hitboxes::hitbox_pelvis));
			int green = int(player->health() * 2.55f);
			int red = 255 - green;

			render::draw_outline(box.left, box.top, (box.right - box.left), (box.bottom - box.top), is_visible ? color::white(alpha) : color(red, green, 0, alpha));
			render::draw_outline(box.left - 1, box.top - 1, (box.right - box.left) + 2, (box.bottom - box.top) + 2, color::black(alpha));
			render::draw_outline(box.left + 1, box.top + 1, (box.right - box.left) - 2, (box.bottom - box.top) - 2, color::black(alpha));

			player_info_t player_info;
			interfaces::engine->get_player_info(i, &player_info);

			if (player->active_weapon())
				render::text(box.left + 1, box.top - 38, render::fonts::tahoma, std::to_string(player->active_weapon()->clip1_count()), false, color::white(alpha));

			render::text(box.left + 1, box.top - 18, render::fonts::tahoma, player_info.name, false, color(red, green, 0, alpha));

			render::text(box.right + 3, box.bottom + 5, render::fonts::tahoma, "HP: " + std::to_string(player->health()), false, color(red, green, 0, alpha));
			if (player->has_c4())
				render::text(box.right - 16, box.bottom + 5, render::fonts::tahoma, "C4", false, color(0, 175, 255, alpha));
			render::text(box.right + 3, box.bottom + 17, render::fonts::tahoma, "Armor: " + std::to_string(player->armor()), false, color(red, green, 0, alpha));
			if (player->active_weapon())
				render::text(box.right + 3, box.bottom + 30, render::fonts::tahoma, player->active_weapon()->get_weapon_name(), false, color::white(alpha));
		}
	}
}

void visuals::entities::grenades_draw() {
	if (!csgo::local_player)
		return;

	if (!variables::esp)
		return;

	for (int i = 1; i <= interfaces::entity_list->get_highest_index(); i++) {
		auto entity = reinterpret_cast<entity_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity)
			continue;

		vec3_t origin = entity->origin(), w2s;

		if (math::world_to_screen(origin, w2s)) {
			auto class_id = entity->client_class()->class_id;
			switch (class_id) {
				case cbasecsgrenadeprojectile: {
						const model_t* model = entity->model();
						if (!model)
							return;
						studio_hdr_t* hdr = interfaces::model_info->get_studio_model(model);
						if (!hdr)
							return;
						std::string name = hdr->name_char_array;
						if (name.find("incendiarygrenade") != std::string::npos || name.find("fraggrenade") != std::string::npos) {
							render::text(w2s.x, w2s.y, render::fonts::tahoma, "frag", true, color(255, 0, 0));
							break;
						}
						render::text(w2s.x, w2s.y, render::fonts::tahoma, "flash", true, color(255, 255, 0));
					}
					break;
				case cmolotovprojectile:
				case cinferno: {
						render::text(w2s.x, w2s.y, render::fonts::tahoma, "fire", true, color(255, 0, 0));
					}
					break;
				case csmokegrenadeprojectile: {
						render::text(w2s.x, w2s.y, render::fonts::tahoma, "smoke", true, color(255, 0, 255));
					}
					break;
				case cdecoyprojectile: {
						render::text(w2s.x, w2s.y, render::fonts::tahoma, "decoy", true, color(rand() % 255, rand() % 255, rand() % 255));
					}
					break;
				default: break;	
			}
		}
	}
}

void visuals::misc::recoil_crosshair_draw() {
	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (!variables::crosshair)
		return;

	std::pair<int, int> screen_size;

	interfaces::surface->get_screen_size(screen_size.first, screen_size.second);
	int x = screen_size.first / 2;
	int y = screen_size.second / 2;

	if (variables::crosshair == 2) {
		vec3_t punch = csgo::local_player->aim_punch_angle();
		if (csgo::local_player->is_scoped())
			punch /= .5f;

		// subtract the punch from the position
		x -= (screen_size.first / 90) * punch.y;
		y += (screen_size.second / 90) * punch.x;
	}

	render::draw_xhair(x, y, true, color::white());
}

void visuals::misc::spectator_list_draw() {
	if (!csgo::local_player)
		return;

	auto text_y_offset = 5; // yea
	int screen[2];

	interfaces::engine->get_screen_size(screen[0], screen[1]);

	player_t* spec_player = csgo::local_player->is_alive() ? csgo::local_player : reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(csgo::local_player->observer_target()));
	
	if (!spec_player)
		return;

	for (int i = 1; i <= interfaces::globals->max_clients; ++i) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || entity->dormant() || entity->is_alive() || reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(entity->observer_target())) != spec_player || entity == csgo::local_player)
			continue;
		player_info_t player_info;

		interfaces::engine->get_player_info(i, &player_info); // bypasing ipv88 and connecting localling to the masterlloser mainfraim

		if (wchar_t name[128]; MultiByteToWideChar(CP_UTF8, 0, player_info.name, -1, name, 128)) {
			int text_width, text_height;
			interfaces::surface->get_text_size(render::fonts::tahoma, name, text_width, text_height);
			render::text(screen[0] * 0.73f, text_y_offset, render::fonts::tahoma, name, false, color(0, 255, 255, 255));
			text_y_offset += text_height + 3;
		}
	}
}