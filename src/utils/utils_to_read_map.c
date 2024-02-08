/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_read_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:38:22 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/07 21:17:25 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void	set_dist_to_map(char *file_name, t_fetch data, t_enum dist)
{
	if (data.rows >= 1000 || data.columns >= 1000)
		mount_matrix(data, file_name, data.matrix, dist.case_1);
	else if (data.rows >= 500 || data.columns >= 500)
		mount_matrix(data, file_name, data.matrix, dist.case_2);
	else if (data.rows >= 300 || data.columns >= 300)
		mount_matrix(data, file_name, data.matrix, dist.case_3);
	else if (data.rows > 150 || data.columns > 150)
		mount_matrix(data, file_name, data.matrix, dist.case_4);
	else if (data.rows >= 100 || data.columns >= 100)
		mount_matrix(data, file_name, data.matrix, dist.case_5);
	else if (data.rows >= 30 || data.columns >= 30)
		mount_matrix(data, file_name, data.matrix, dist.case_6);
	else if (data.rows <= 30 || data.columns <= 30)
		mount_matrix(data, file_name, data.matrix, dist.case_7);
}

uint32_t	ft_atoi_base(char *str, uint32_t base)
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
