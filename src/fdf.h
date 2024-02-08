/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:47:19 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/08 12:29:05 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080

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
	uint32_t	color;

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

typedef struct s_fetch
{
	int			i;
	int			j;
	int			x;
	int			y;
	int			fd;
	int			rows;
	int			columns;
	char		*line;
	char		**hex;
	char		**split;
	t_pixel		**matrix;

	mlx_image_t	*img;
	mlx_t		*mlx;
}				t_fetch;

// main
void			ft_error(char *str);
void			free_matrix(t_pixel **matrix, int rows);
t_enum			set_enum_struct(void);

// count_rows_collumns
int				get_rows(char *file_name);
int				get_column(char *file_name);

// read_map
t_pixel			**malloc_matrix(int rows, int columns);
void			move_to_center(t_pixel **map, int rows, int columns, int dist);
void			set_dist_to_map(char *file_name, t_fetch data, t_enum dist);
uint32_t		ft_atoi_base(char *str, uint32_t base);
void			mount_matrix(t_fetch data, char *file_name, t_pixel **matrix,
					float dist);
t_pixel			**read_map(char *file_name, int rows, int columns, t_enum dist);

// set_pixel
void			set_pixel(t_fetch data, t_pixel **matrix);
void			isometric(t_pixel **matrix, int rows, int columns);

#endif
