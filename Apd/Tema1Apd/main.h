#ifndef __MAIN_H__
#define __MAIN_H__

struct coord
{
	int line;
	int col;
};

struct snake
{
	struct coord head;
	struct coord tail;
	int encoding;
	char direction;
	int moved;
};

void print_world(char *file_name, int num_snakes, struct snake *snakes,
	int num_lines, int num_cols, int **world);

void read_data(char *file_name, int *num_snakes, struct snake **snakes,
	int *num_lines, int *num_cols, int ***world);

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name);

// change coordinates for the walls
void connected(int *line, int *col, int num_lines, int num_cols);

// change the tail's coordinates of the snake
void update_tail(struct coord *tail, int num_lines, int num_cols, int **world, int encoding);

// find the tail's coordinates of the snake
void find_tail(int line, int col, int num_lines, int num_cols, int **world, int **viz, struct coord *tail);

// returns the opposite direction 
char opposite(char direction);

// move the head of the snakes and detects a collision
int move_head(struct snake *head, char direction, int **world, int num_lines, int num_cols, int forward);

#endif