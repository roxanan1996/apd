/*
	// parallize this for 
	for (i = 0; i < num_snakes; ++i) {
		int found_tail = 0;
		for (line = 0; line < num_lines; ++line) {
			for (col = 0; col < num_cols; ++col) {
				if (world[line][col] == world[snakes[i].head.line][snakes[i].head.col]) {
					if (line != snakes[i].head.line &&
						col != snakes[i].head.col) {

						if (is_tail(line, col, num_lines, num_cols, world)) {
							snakes[i].tail.line = line;
							snakes[i].tail.col = col;
							found_tail = 1;
							break;
						}
					}	
				}
			}

			if (found_tail) {
				break;
			}
		}
	}
*/
/*
	for (i = 0; i < num_snakes; ++i) {
		printf("tail line is %d, tail col is %d, encod is %d\n", snakes[i].tail.line, snakes[i].tail.col, snakes[i].encoding);
	}
*/