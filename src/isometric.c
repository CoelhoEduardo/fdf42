/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:32 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/08 12:56:59 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_pixel **matrix, int rows, int columns)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			matrix[i][j].x = (matrix[i][j].x - matrix[i][j].y) * cos(0.98);
			matrix[i][j].y = (matrix[i][j].x + matrix[i][j].y) * sin(0.88)
				- matrix[i][j].z;
			matrix[i][j].x += 600;
			matrix[i][j].y += 300;
			j++;
		}
		i++;
	}
}
