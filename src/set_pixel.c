/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:40:26 by eduardocoel       #+#    #+#             */
/*   Updated: 2024/02/05 15:37:00 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(uint32_t *x, uint32_t *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	calc_bre(t_params *node, uint32_t x2, uint32_t y2, fdf *data)
{
	node->x = node->j;
	node->y = node->i;
	node->z = data->matrix[node->y][node->x].z;
	node->z1 = data->matrix[y2][x2].z;
	node->dx = x2 - node->x;
	node->dy = y2 - node->y;
	node->p = node->dy - node->dx;
	if (node->z || node->z1)
		node->color = 0x33ff33;
	else
		node->color = 0xffffff;
}

void	put_pixel(t_params *node, uint32_t x2, uint32_t y2, fdf *data)
{
	while ((node->x - x2) || (node->y - y2))
	{
		mlx_put_pixel(data->img, node->x, node->y, node->color);
		node->x += node->dx;
		node->y += node->dy;
		if (node->dx < node->dy)
			node->p += 2 * node->dy;
		else
			node->p += 2 * (node->dy - (2 * node->dx));
	}
}

void	bresenham(t_params node, uint32_t x2, uint32_t y2, fdf *data)
{
	calc_bre(&node, x2, y2, data);
	node.zoom = 25;
	node.x *= node.zoom;
	node.y *= node.zoom;
	x2 *= node.zoom;
	y2 *= node.zoom;
	node.x += 250;
	node.y += 250;
	x2 += 250;
	y2 += 250;
	put_pixel(&node, x2, y2, data);
}

void	set_pixel(fdf *data)
{
	t_params	node;

	node.i = 0;
	while (node.i < data->row)
	{
		node.j = 0;
		while (node.j < data->column)
		{
			if (node.i + 1 < data->row)
			bresenham(node, node.j, node.i + 1, data);
			if (node.j + 1 < data->column)
			bresenham(node, node.j + 1, node.i, data);
			node.j++;
		}
		node.i++;
	}
}
