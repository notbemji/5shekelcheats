#pragma once
#include "../../../dependencies/utilities/csgo.hpp"

#define TICK_INTERVAL			( interfaces::globals->interval_per_tick )
#define TIME_TO_TICKS( t )		( (int)( 0.5f + (float)( t ) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL * (float)( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * time_to_ticks( t ) )
#define TICK_NEVER_THINK		( -1 )

namespace prediction {
	void start(c_usercmd* cmd);
	void end();

	inline player_move_data data;
	inline float old_cur_time;
	inline float old_frame_time;
	inline int* prediction_random_seed;
};
