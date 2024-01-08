#ifndef FDF_H
#define FDF_H

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct t_pixel
{
    int color;
    int value;
    int position_x;
    int position_y;

}   t_pixel;

typedef struct
{
    int row;
    int collumn;
    int fd;
    int i;
    int x;
    char *line;
    char **split;
    int y;
    int j;
    char **hex;
    int zoom;
    mlx_t *mlx;
    mlx_image_t *img;
    t_pixel **matrix;

}   fdf;

int get_rows(char *file_name);
int get_collumn(char *file_name);
t_pixel **read_map(char *file_name, fdf *data);
void    bresenham(float x, float y, float x1, float y1, fdf *data);
void draw(fdf *data);

#endif