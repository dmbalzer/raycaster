#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

typedef struct {
	float x;
	float y;
	int turn_dir; /* -1 left +1 right */
	int walk_dir; /* -1 back +1 front */
	float rot_angle;
	float speed;
	float rot_speed;
} Player;

void player_move(Player* player);
void player_draw(Player player);

#endif // PLAYER_INCLUDED
