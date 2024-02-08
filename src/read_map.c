/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:11:06 by eduardocoel       #+#    #+#             */
/*   Updated: 2024/02/07 21:43:35 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set(t_pixel *matrix, int value, uint32_t color, t_fetch *data)
{
	matrix->x = data->y;
	matrix->y = data->x;
	matrix->z = value;
	matrix->color = color;
	free(data->split[data->j]);
	if (data->hex[1])
		free(data->hex[1]);
	free(data->hex[0]);
	free(data->hex);
}

void	aux_matrix(t_fetch data, t_pixel **matrix, float dist)
{
	data.hex = ft_split(data.split[data.j], ',');
	if (data.hex[1])
		set(&matrix[data.i][data.j], ft_atoi(data.split[data.j]) * dist / 4,
			(ft_atoi_base(data.hex[1], 16) << 8) | 0xff, &data);
	else
		set(&matrix[data.i][data.j], ft_atoi(data.split[data.j]) * dist / 4,
			0xFFFFFFFF, &data);
}

void	mount_matrix(t_fetch data, char *file_name, t_pixel **matrix,
		float dist)
{
	data.fd = open(file_name, O_RDONLY);
	data.x = 0;
	data.i = 0;
	while (data.i < data.rows)
	{
		data.line = get_next_line(data.fd);
		data.j = 0;
		data.split = ft_split(data.line, ' ');
		data.y = 0;
		while (data.j < data.columns)
		{
			aux_matrix(data, matrix, dist);
			data.y += dist;
			data.j++;
		}
		data.x += dist;
		data.i++;
		free(data.line);
		free(data.split);
	}
	close(data.fd);
}

t_pixel	**read_map(char *file_name, int rows, int columns, t_enum dist)
{
	t_fetch	data;

	data.rows = rows;
	data.columns = columns;
	data.matrix = malloc_matrix(data.rows, data.columns);
	if (!data.matrix)
		return (NULL);
	set_dist_to_map(file_name, data, dist);
	move_to_center(data.matrix, rows, columns, (rows + columns) / 4);
	return (data.matrix);
}
