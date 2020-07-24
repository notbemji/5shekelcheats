#pragma once

#pragma pack(push, 1)

class i_client_state {
public:
	char		u0[ 156 ];
	i_net_channel	*net_channel;
	uint32_t	challenge_nr;
	char		u1[ 100 ];
	uint32_t	signon_state_count;
	char		u2[ 8 ];
	float		next_cmd_time;
	uint32_t	server_count;
	uint32_t	current_sequence;
	char		u3[ 84 ];
	uint32_t	delta_tick;
	bool		paused;
	char		u4[ 3 ];
	uint32_t	view_entity;
	uint32_t	player_slot;
	char		level_name[ 260 ];
	char		level_name_short[ 80 ];
	char		group_name[ 80 ];
	char		u5[ 92 ];
	uint32_t	max_clients;
	char		u6[ 18824 ];
	float		last_server_tick_time;
	bool		in_simulation;
	char		u7[ 3 ];
	uint32_t	old_tick_count;
	float		tick_remainder;
	float		frame_time;
	int		last_outgoing_command;
	int		choked_commands;
	int		last_command_ack;
	int		command_ack;
	int		sound_sequence;
	char		u8[ 80 ];
	vec3_t		view_angles;

	void full_update() {
		delta_tick = -1;
	}
};

#pragma pack(pop)
