#ifndef FDF_H
#define FDF_H

#define WIDTH 1920
#define HEIGHT 1080
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
# include <math.h>

typedef struct s_pixel
{
    int x;
    int y;
    int x1;
    int y1;
    int z;
    int z1;

}   t_pixel;

typedef struct
{
    int row;
    int collumn;
    int j;
    int x;
    int y;
    int color;
    int shift_y;
    int shift_x;
    char **hex;
    char **split;
     int zoom;
    int **matrix;

    mlx_image_t *img;
    mlx_t *mlx;
}   fdf;

typedef struct s_params
{
    float x;
    float y;
    float x1;
    float y1;
    int z;
    int z1;
}   t_params;

int get_rows(char *file_name);
int get_collumn(char *file_name);
void read_map(char  *file_name, fdf *data);
void set_pixel(fdf *data);
#endif

