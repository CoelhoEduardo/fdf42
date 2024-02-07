/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:11:06 by eduardocoel       #+#    #+#             */
/*   Updated: 2024/02/07 11:11:07 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	base(char *str, uint32_t base)
{
	int			i;
	uint32_t	nbr;
	uint32_t	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * base + str[i] - 'a' + 10;
		i++;
	}
	return (nbr * sign);
}

static void	set_values(t_pixel *matrix, int value, uint32_t color, fdf *data)
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

void	mount_matrix(fdf data, char *file_name, t_pixel **matrix, float dist)
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
			data.hex = ft_split(data.split[data.j], ',');
			if (data.hex[1])
				set_values(&matrix[data.i][data.j], ft_atoi(data.split[data.j])
					* dist / 4, (base(data.hex[1], 16) << 8) | 0xff, &data);
			else
				set_values(&matrix[data.i][data.j], ft_atoi(data.split[data.j])
					* dist / 4, 0xffffffff, &data);
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

t_pixel	**malloc_matrix(int rows, int columns)
{
	int		i;
	t_pixel	**matrix;

	matrix = (t_pixel **)malloc(sizeof(t_pixel *) * rows);
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		matrix[i] = (t_pixel *)malloc(sizeof(t_pixel) * columns);
		if (!matrix[i])
			return (NULL);
		i++;
	}
	if (!matrix)
		return (NULL);
	return (matrix);
}

void	move_to_center(t_pixel **map, int rows, int columns, int dist)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			map[i][j].x += dist;
			map[i][j].y -= dist;
			j++;
		}
		i++;
	}
}

t_pixel	**read_map(char *file_name, int rows, int columns, t_enum dist)
{
	fdf	data;

	data.rows = rows;
	data.columns = columns;
	data.matrix = malloc_matrix(data.rows, data.columns);
	if (!data.matrix)
		return (NULL);
	if (rows >= 1000 || columns >= 1000)
		mount_matrix(data, file_name, data.matrix, dist.case_1);
	else if (rows >= 500 || columns >= 500)
		mount_matrix(data, file_name, data.matrix, dist.case_2);
	else if (rows >= 300 || columns >= 300)
		mount_matrix(data, file_name, data.matrix, dist.case_3);
	else if (rows > 150 || columns > 150)
		mount_matrix(data, file_name, data.matrix, dist.case_4);
	else if (rows >= 100 || columns >= 100)
		mount_matrix(data, file_name, data.matrix, dist.case_5);
	else if (rows >= 30 || columns >= 30)
		mount_matrix(data, file_name, data.matrix, dist.case_6);
	else if (rows <= 30 || columns <= 30)
		mount_matrix(data, file_name, data.matrix, dist.case_7);
	move_to_center(data.matrix, rows, columns, (rows + columns) / 4);
	return (data.matrix);
}
