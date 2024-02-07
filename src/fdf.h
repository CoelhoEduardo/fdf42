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
	int			x;
	int			y;
	int			z;
	uint32_t			color;

}				t_pixel;

typedef struct s_params
{
	int			x;
	int			y;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			i;
	int			j;
	int			slo_error;
	int			err;

}				t_params;

typedef struct
{
	int			i;
	int			j;
	int			x;
	int			y;
	int			fd;
	int			rows;
	int			columns;
	char		*line;
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
t_pixel			**read_map(char *file_name, int rows, int columns, t_enum dist);
void			set_pixel(fdf data, t_pixel **matrix);
void			isometric(t_pixel **matrix, int rows, int columns);
#endif
