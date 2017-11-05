#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void connected(int *line, int *col, int num_lines, int num_cols) {
	if (*line < 0) {
				*line = num_lines - 1;
			} else if (*line == num_lines) {
				*line = 0;
			}


			if (*col < 0) {
				*col = num_cols - 1;
			} else if (*col == num_cols) {
				*col = 0;
			}
}

void update_tail(struct coord *tail, int num_lines, int num_cols, int **world, int encoding) {
	int directions_i[4] = {-1, 0, 1, 0};
	int directions_j[4] = {0, -1, 0, 1};
	int i = 0;
	int new_line;
	int new_col;

	for (i = 0; i < 4; ++i) {
		new_line = tail->line + directions_i[i];
		new_col = tail->col + directions_j[i];

		connected(&new_line, &new_col, num_lines, num_cols);
		
		if (world[new_line][new_col] == encoding) {
			break;
		}
	}

	tail->line = new_line;
	tail->col = new_col;

}

void find_tail(int line, int col, int num_lines, int num_cols, int **world, int **viz, struct coord *tail) {
	int directions_i[4] = {-1, 0, 1, 0};
	int directions_j[4] = {0, -1, 0, 1};
	int nb_of_visited_neighbors = 0;
	int i;
	int new_line;
	int new_col;

	while(nb_of_visited_neighbors < 4) {
		nb_of_visited_neighbors = 0;

		for (i = 0; i < 4; ++i) {
			new_line = line + directions_i[i];
			new_col = col + directions_j[i];

			connected(&new_line, &new_col, num_lines, num_cols);

			if (world[new_line][new_col] == world[line][col] && !viz[new_line][new_col]) {
				viz[new_line][new_col] = 1;
				line = new_line;
				col = new_col;
				break;
			} else {
				nb_of_visited_neighbors++;
			}
		}
	}

	tail->line = line;
	tail->col = col;
}

char opposite(char direction) {
	char opposite_direction; 

	switch(direction) {
		case 'N': opposite_direction = 'S'; break;
		case 'S': opposite_direction = 'N'; break;
		case 'V': opposite_direction = 'E'; break;
		case 'E': opposite_direction = 'V'; break;
	}

	return opposite_direction;
}

int move_head(struct coord *head, char direction, int **world, int num_lines, int num_cols, int forward) {

	int line = head->line;
	int col = head->col;
	int collision_detected = 1;
	switch(direction) {
		case 'N': line--; break;
		case 'S': line++; break;
		case 'V': col--; break;
		case 'E': col++; break;
	}

	connected(&line, &col, num_lines, num_cols);

	if (forward && !world[line][col]) {
		world[line][col] = world[head->line][head->col];
		collision_detected = 0;
	}

	// change the head anyway
	head->line = line;
	head->col = col;

	if (collision_detected)
		return 1;

	return 0;

}
void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name) 
{
	// TODO: Implement Parallel Snake simulation using the default (env. OMP_NUM_THREADS) 
	// number of threads.
	//
	// DO NOT include any I/O stuff here, but make sure that world and snakes
	// parameters are updated as required for the final state.

	int i, line, col, s;
	int collision_detected = 0;
	int collision;
	int **viz = (int**) malloc(sizeof(int) * num_lines);

	for (i = 0; i < num_cols; ++i) {
		viz[i] = (int*) calloc(num_cols, sizeof(int));
	}

	#pragma omp parallel for private(line, col)
	for (i = 0; i < num_snakes; ++i) {
		line = snakes[i].head.line;
		col = snakes[i].head.col;
		viz[line][col] = 1;
		find_tail(line, col, num_lines, num_cols, world, viz, &snakes[i].tail);
	}

	for (s = 0; s < step_count; ++s) {
		#pragma omp parallel 
		{
			#pragma omp for 
			for (i = 0; i < num_snakes; ++i) {
				// update the tail :D
				world[snakes[i].tail.line][snakes[i].tail.col] = 0;
			}
			
			#pragma omp barrier

			#pragma omp for private (collision)
			for (i = 0; i < num_snakes; ++i) {
				collision = move_head(&snakes[i].head, snakes[i].direction, world, num_lines, num_cols, 1);
		
				if (collision) {
					collision_detected = 1;
				} 
			}

			#pragma omp barrier

			#pragma omp for 
			for (i = 0; i < num_snakes; ++i) {				
				if (collision_detected) {
					world[snakes[i].tail.line][snakes[i].tail.col] = snakes[i].encoding;
					world[snakes[i].head.line][snakes[i].head.col] = 0;			
					move_head(&snakes[i].head, opposite(snakes[i].direction), world, num_lines, num_cols, 0);
					world[snakes[i].head.line][snakes[i].head.col] = snakes[i].encoding;
				} else {
					update_tail(&snakes[i].tail, num_lines, num_cols, world, snakes[i].encoding);
				}
			}

			#pragma omp barrier	
		}

		if (collision_detected) {
			break;
		}
	}
}