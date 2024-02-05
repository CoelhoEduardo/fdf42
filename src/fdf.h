#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_enum
{
	float		case_1;
	float		case_2;
	float		case_3;
	float		case_4;
	float		case_5;
	float		case_6;
	float		case_7;
}				t_enum;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
	int32_t		color;

}				t_pixel;

typedef struct s_params
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	x1;
	uint32_t	y1;
	uint32_t	dx;
	uint32_t	dy;
	uint32_t	z;
	uint32_t	z1;
	uint32_t	i;
	uint32_t	j;
	uint32_t	p;
	int32_t		color;
	int			zoom;

}				t_params;

typedef struct
{
	uint32_t	row;
	uint32_t	column;
	int			zoom;
	int			z_scale;
	char		**hex;
	char		**split;
	t_pixel		**matrix;

	mlx_image_t	*img;
	mlx_t		*mlx;
}				fdf;

int				get_rows(char *file_name);
int				get_column(char *file_name);
t_pixel			**read_map(char *file_name, int row, int column);
void			set_pixel(fdf *data);
#endif
