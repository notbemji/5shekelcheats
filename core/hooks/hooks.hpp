#pragma once

namespace hooks {
	bool initialize();
	void release();

	inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

	namespace create_move {
		using fn = bool(__stdcall*)(float, c_usercmd*);
		bool __stdcall hook(float input_sample_frametime, c_usercmd* cmd);
	};

	namespace paint_traverse {
		using fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
		void __stdcall hook(unsigned int panel, bool force_repaint, bool allow_force);
	}

	namespace draw_model_execute {
		using fn = void(__fastcall*)(void*, int, i_mat_render_context*, const draw_model_state_t&, const model_render_info_t&, matrix_t*);
		void __fastcall hook(void* _this, int edx, i_mat_render_context* ctx, const draw_model_state_t& state, const model_render_info_t& pInfo, matrix_t* pCustomBoneToWorld);
	}

	namespace sv_cheats {
		using fn = bool(__thiscall*)(void*);
		bool __fastcall hook(PVOID convar, int edx);
	}

	namespace frame_stage_notify {
		using fn = void(__thiscall*)(void*, client_frame_stage_t);
		void __stdcall hook(client_frame_stage_t frame_stage);
	}

	namespace bsp_query {
		using fn = int(__fastcall*)(void*, int, const vec3_t*, const vec3_t*, unsigned short*, int);
		int __fastcall hook(void* ecx, int edx, vec3_t* mins, vec3_t* maxs, unsigned short* list, int list_max);
	}
}
