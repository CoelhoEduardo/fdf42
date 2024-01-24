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
    float x;
    float y;
    int z;
    uint32_t color;

}   t_pixel;

typedef struct s_params
{
    int   x;
    int   y;
    int   x1;
    int   y1;
    int	dx;
	int	dy;
	int		z;
	int		z1;
    int i;
    int j;
    int p;
	uint32_t		color;

}   t_params;



typedef struct
{
    int row;
    int collumn;
    int zoom;
    int z_scale;
    char **hex;
    char **split;
    t_pixel **matrix;

    mlx_image_t *img;
    mlx_t *mlx;
}   fdf;

int get_rows(char *file_name);
int get_collumn(char *file_name);
t_pixel	**read_map(char *file_name, int row, int column);
void	set_pixel(fdf *data);
#endif

