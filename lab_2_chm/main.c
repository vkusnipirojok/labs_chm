#include <stdio.h>
#include <stdlib.h>


int WIDTH = 6;
int HEIGHT = 4;
int SIZE = 21;
int SIZE_XS = 32;

void trans_matr(double **matrix_one, double** matrix_two, double *array_b, int SIZE_WIDTH, int SIZE_HEIGHT, int STEP, int value, double *out_arr, int index);

void start_matr(double **matr, int HEIGHT, int WIDTH, double value_1, double value_2, double value_3, double value_4) {
	
	matr[0][0] = 7.22; 
	matr[0][1] = 1.42;
        matr[0][2] = -1.72;
        matr[0][3] = 1.91;
	matr[0][4] = value_1;
        matr[1][0] = 1.44;
        matr[1][1] = 6.33;
        matr[1][2] = 1.11;
        matr[1][3] = -1.82;
	matr[1][4] = value_2;
        matr[2][0] = -1.72;
        matr[2][1] = 1.11;
        matr[2][2] = 6.24;
        matr[2][3] = 1.42;
	matr[2][4] = value_3;
        matr[3][0] = 1.91;
        matr[3][1] = -1.82;
        matr[3][2] = 1.42;
        matr[3][3] = 7.55;
	matr[3][4] = value_4;
	
	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH - 1; j++)
			matr[i][5] += matr[i][j];
}

void nullify_matr(double **matr, int HEIGHT, int WIDTH) {

	for(int i = 0; i < HEIGHT; i++)
		for(int j = 0; j < WIDTH; j++)
			if(matr[i][j] != (double)0)
				matr[i][j] = (double)0;
}

void nullify_array(double *array, int SIZE) {

	for(int i = 0; i < SIZE; i++)
		if(array[i] != (double)0)
			array[i] = (double)0;
}

void find_xs(double *save_arr, double *out_arr, int *index) {

	save_arr[*index] = out_arr[19] / out_arr[18];
	(*index)++;
        save_arr[*index] = out_arr[14] - out_arr[13] * save_arr[*index - 1];
	(*index)++;
        save_arr[*index] = out_arr[9] - out_arr[8] * save_arr[*index - 2] - out_arr[7] * save_arr[*index - 1];
	(*index)++;
        save_arr[*index] = out_arr[4] - out_arr[3] * save_arr[*index - 3] - out_arr[2] * save_arr[*index - 2] - out_arr[1] * save_arr[*index - 1];
	(*index)++;

        save_arr[*index] = out_arr[20] / out_arr[18];
	(*index)++;
        save_arr[*index] = out_arr[15] - out_arr[13] * save_arr[*index - 1];
	(*index)++;
        save_arr[*index] = out_arr[10] - out_arr[8] * save_arr[*index - 2] - out_arr[7] * save_arr[*index - 1];
	(*index)++;
        save_arr[*index] = out_arr[5] - out_arr[3] * save_arr[*index - 3] - out_arr[2] * save_arr[*index - 2] - out_arr[1] * save_arr[*index - 1];
	(*index)++;
}

void print_matr(double **matr, int HEIGHT, int WIDTH) {
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH; j++) {
			printf("%.3lf ", matr[i][j]);
		}printf("\n");
	}
}

void check_unit_matr(double **start_matr, double **found_matr, int SIZE) {

	double **tmp_matr = malloc(SIZE * sizeof(double*));
        for(int i = 0; i < SIZE; i++)
                tmp_matr[i] = malloc(SIZE * sizeof(double));

        for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                        tmp_matr[i][j] = 0;
                        for(int k = 0; k < SIZE; k++)
                                tmp_matr[i][j] += start_matr[i][k] * found_matr[k][j];
                }
        }

	for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                        printf("%.3lf ", tmp_matr[i][j]);
                }printf("\n");
        }

        for(int i = 0; i < SIZE; i++)
                free(tmp_matr[i]);
        free(tmp_matr);
}

double find_cond_matr(double **start_matr, double **found_matr, int SIZE) {

	double cond = 0.0;
	double tmp_cond = 0.0;

	double cond_1 = 0.0;
	double tmp_cond_1 = 0.0;

	double cond_2 = 0.0;
	double tmp_cond_2 = 0.0;

	double cond_3 = 0.0;
	double tmp_cond_3 = 0.0;

	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			if(start_matr[j][i] < (double)0)
				start_matr[j][i] = start_matr[j][i] * (double)(-1);
			tmp_cond += start_matr[j][i];
		}
		if(cond < tmp_cond)
			cond = tmp_cond;
		tmp_cond = 0.0;
	}

	for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                        if(found_matr[j][i] < (double)0)
                                found_matr[j][i] = found_matr[j][i] * (double)(-1);
                        tmp_cond_1 += found_matr[j][i];
                }
                if(cond_1 < tmp_cond_1)
                        cond_1 = tmp_cond_1;
                tmp_cond_1 = 0.0;
        }

	for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                        if(start_matr[i][j] < (double)0)
                                start_matr[i][j] = start_matr[i][j] * (double)(-1);
                        tmp_cond_2 += start_matr[i][j];
                }
                if(cond_2 < tmp_cond_2)
                        cond_2 = tmp_cond_2;
                tmp_cond_2 = 0.0;
        }

        for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                        if(found_matr[i][j] < (double)0)
                                found_matr[i][j] = found_matr[i][j] * (double)(-1);
                        tmp_cond_3 += found_matr[i][j];
                }
                if(cond_3 < tmp_cond_3)
                        cond_3 = tmp_cond_3;
                tmp_cond_3 = 0.0;
        }

	return cond_2 * cond_3;
}

int main()
{

	int tmp_index = 0;
	
	double **begin_matr = malloc(HEIGHT * sizeof(double*));
	double **temp_matr = malloc(HEIGHT * sizeof(double*));
	double **found_matr = malloc(4 * sizeof(double*));
	double *out_arr = malloc(SIZE * sizeof(double));
	double *arr_b = malloc(WIDTH * sizeof(double));
	double *arr_xs = malloc(SIZE_XS * sizeof(double));

	for(int i = 0; i < HEIGHT; i++)
		begin_matr[i] = malloc(WIDTH * sizeof(double));
	start_matr(begin_matr, HEIGHT, WIDTH, 1, 0, 0, 0);

	for(int i = 0; i < HEIGHT; i++)
		temp_matr[i] = malloc(WIDTH * sizeof(double));

	for(int i = 0; i < 4; i++)
		found_matr[i] = malloc(4 * sizeof(double));

	printf("\nTable1\n");
	print_matr(begin_matr, HEIGHT, WIDTH);

	trans_matr(begin_matr, temp_matr, arr_b, WIDTH, HEIGHT, 4, 0, out_arr, 0);
	find_xs(arr_xs, out_arr, &tmp_index); 


	nullify_matr(temp_matr, HEIGHT, WIDTH);
	start_matr(begin_matr, HEIGHT, WIDTH, 0, 1, 0, 0);	
	printf("\nTable2\n");
	print_matr(begin_matr, HEIGHT, WIDTH);
	nullify_array(out_arr, SIZE);
	trans_matr(begin_matr, temp_matr, arr_b, WIDTH, HEIGHT, 4, 0, out_arr, 0);
        find_xs(arr_xs, out_arr, &tmp_index);

	nullify_matr(temp_matr, HEIGHT, WIDTH);
        start_matr(begin_matr, HEIGHT, WIDTH, 0, 0, 1, 0);
	printf("\nTable3\n");
	print_matr(begin_matr, HEIGHT, WIDTH);
        nullify_array(out_arr, SIZE);
        trans_matr(begin_matr, temp_matr, arr_b, WIDTH, HEIGHT, 4, 0, out_arr, 0);
        find_xs(arr_xs, out_arr, &tmp_index);

	nullify_matr(temp_matr, HEIGHT, WIDTH);
        start_matr(begin_matr, HEIGHT, WIDTH, 0, 0, 0, 1);
	printf("\nTable4\n");
	print_matr(begin_matr, HEIGHT, WIDTH);
        nullify_array(out_arr, SIZE);
        trans_matr(begin_matr, temp_matr, arr_b, WIDTH, HEIGHT, 4, 0, out_arr, 0);
        find_xs(arr_xs, out_arr, &tmp_index);


	for(int i = 0; i < SIZE_XS; i++) {
		if(i % 4 == 0)
			printf("\n");
		printf("%.3lf ", arr_xs[i]);
	}
	printf("\n");

	int k = 3, l = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			found_matr[j][i] = arr_xs[k + l];
			k--;
		}
		k = 3;
		l += 8;
	}
	printf("\n");
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			printf("%.3lf ", found_matr[i][j]);

		}printf("\n");
	}

	double **first_matr = malloc(4 * sizeof(double*));
	for(int i = 0; i < 4; i++)
		first_matr[i] = malloc(4 * sizeof(double));

	first_matr[0][0] = 7.22;
        first_matr[0][1] = 1.42;
        first_matr[0][2] = -1.72;
        first_matr[0][3] = 1.91;
        
        first_matr[1][0] = 1.44;
        first_matr[1][1] = 6.33;
        first_matr[1][2] = 1.11;
        first_matr[1][3] = -1.82;
        
        first_matr[2][0] = -1.72;
        first_matr[2][1] = 1.11;
        first_matr[2][2] = 6.24;
        first_matr[2][3] = 1.42;
        
        first_matr[3][0] = 1.91;
        first_matr[3][1] = -1.82;
        first_matr[3][2] = 1.42;
        first_matr[3][3] = 7.55;


	printf("\n");
        for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 4; j++) {
                        printf("%f ", first_matr[i][j]);

                }printf("\n");
        }

	check_unit_matr(first_matr, found_matr, 4);
	printf("%.3lf\n" ,find_cond_matr(first_matr, found_matr, 4));


        for(int i = 0; i < 4; i++)
		free(first_matr[i]);
	free(first_matr);

	free(arr_xs);

	free(arr_b);

	free(out_arr);

	for(int i = 0; i < 4; i++)
                free(found_matr[i]);
        free(found_matr);
	
	for(int i = 0; i < HEIGHT; i++)
                free(temp_matr[i]);
        free(temp_matr);

	for(int i = 0; i < HEIGHT; i++)
		free(begin_matr[i]);
	free(begin_matr);

        return 0;
}

void trans_matr(double **matrix_one, double** matrix_two, double *array_b, int SIZE_WIDTH, int SIZE_HEIGHT, int STEP, int value, double* out_arr, int index) {

	if(STEP != 1){
		STEP--;
		for(int i = 0; i < SIZE_WIDTH; i++)
			array_b[i] = matrix_one[value][i + value] / matrix_one[value][value];

		for(int i = 0; i < SIZE_WIDTH; i++) {
			out_arr[index] = array_b[i];
			index++;
		}

		for(int i = value; i < SIZE_HEIGHT; i++) {
			for(int j = value; j < SIZE_WIDTH; j++) { 
				matrix_two[i][j] = matrix_one[i][j] - matrix_one[i][value] * array_b[j - value];
			}
		}

		value++;

		for(int i = 0; i < SIZE_WIDTH; i++)
                       printf("%.3lf ", array_b[i]);

		printf("\n\n");

		for(int i = 0; i < SIZE_HEIGHT; i++) {
			for(int j = 0; j < SIZE_WIDTH; j++) {
				printf("%.3lf ", matrix_two[i][j]);
			};
			printf("\n");
		};		

		for(int i = 0; i < SIZE_HEIGHT; i++)
			for(int j = 0; j < SIZE_WIDTH; j++)
				if(matrix_one[i][j] != (double)0) 
					matrix_one[i][j] = 0;

		for(int i = 0; i < SIZE_WIDTH; i++)
			if(array_b[i] != (double)0)
				array_b[i] = 0;
		if(STEP == 1) {
			out_arr[18] = matrix_two[3][3];
			out_arr[19] = matrix_two[3][4];
			out_arr[20] = matrix_two[3][5];
		}

		trans_matr(matrix_two, matrix_one, array_b, SIZE_WIDTH, SIZE_HEIGHT, STEP, value, out_arr, index);
	}
	else {
		return;
	}
}
