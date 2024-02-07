/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:40:26 by eduardocoel       #+#    #+#             */
/*   Updated: 2024/02/07 09:54:01 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_bre(t_params *node, int i, int j, t_pixel **matrix)
{
	node->x1 = node->x;
	node->y1 = node->y;
	node->x2 = matrix[i][j].x;
	node->y2 = matrix[i][j].y;
	node->dx = abs(node->x2 - node->x1);
	node->dy = abs(node->y2 - node->y1);
	if (node->x1 < node->x2)
		node->sx = 1;
	else
		node->sx = -1;
	if (node->y1 < node->y2)
		node->sy = 1;
	else
		node->sy = -1;
	if (node->dx > node->dy)
		node->slo_error = node->dx / 2;
	else
		node->slo_error = -node->dy / 2;
}

void	put_pixel(t_params node, fdf *data, uint32_t color)
{
	while ((node.x1 - node.x2) || (node.y1 - node.y2))
	{
		if (node.x1 >= 0 && node.y1 >= 0 && node.x1 < 1920 && node.y1 < 1080)
			mlx_put_pixel(data->img, node.x1, node.y1, color);
		node.err = node.slo_error;
		if (node.err > -node.dx)
		{
			node.slo_error -= node.dy;
			node.x1 += node.sx;
		}
		if (node.err < node.dy)
		{
			node.slo_error += node.dx;
			node.y1 += node.sy;
		}
	}
}

void	set_pixel(fdf data, t_pixel **matrix)
{
	t_params	node;

	node.i = 0;
	while (node.i < data.rows)
	{
		node.j = 0;
		while (node.j < data.columns)
		{
			node.x = matrix[node.i][node.j].x;
			node.y = matrix[node.i][node.j].y;
			if (node.j + 1 < data.columns)
			{
				calc_bre(&node, node.i, node.j + 1, matrix);
				put_pixel(node, &data, matrix[node.i][node.j].color);
			}
			if (node.i + 1 < data.rows)
			{
				calc_bre(&node, node.i + 1, node.j, matrix);
				put_pixel(node, &data, matrix[node.i][node.j].color);
			}
			printf("this is the color = %d \n", matrix[node.i][node.j].color);
			node.j++;
		}
		node.i++;
	}
	
}
