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
    int z;
    int color;

}   t_pixel;

typedef struct
{
    int row;
    int collumn;
    int zoom;
    char **hex;
    char **split;
    t_pixel **matrix;

    mlx_image_t *img;
    mlx_t *mlx;
}   fdf;

int get_rows(char *file_name);
int get_collumn(char *file_name);
t_pixel	**read_map(char *file_name, int row, int column);
void set_pixel(fdf *data);
#endif

