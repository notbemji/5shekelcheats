#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

#include "lagcompensation/backtrack.hpp"
#include "rage/antiaim.hpp"

namespace visuals {
	namespace players {
		void esp_draw();
		void chams_run(i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix);
	}
	namespace entities {
		void grenades_draw();
	}
	namespace misc {
		void recoil_crosshair_draw();
		void spectator_list_draw();
	}
}

namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};
	void thirdperson();
}