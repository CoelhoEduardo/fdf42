#include "fdf.h"

void	set_zoom(t_params point, int x2, int y2, fdf *data)
{
	point.x *= 20;
	point.y *= 20;
	x2 *= data->zoom;
	y2 *= data->zoom;
}

void	bresenham(t_params point, int x2, int y2, fdf *data)
{
	int	color;

	color = 0xBBFAFF;
	point.x = point.j;
	point.y = point.i;
	point.z = data->matrix[point.y][point.x].z;
	point.z1 = data->matrix[y2][x2].z;
	point.dx = x2 - point.x;
	point.dy = y2 - point.y;
	point.p = point.dy - point.dx;
	color = point.z || point.z1 ? 0xFFFFFF : 0xBBFAFF;
	color = point.z != point.z1 ? 0xFFFFFF : color;
	while ((point.x - x2) || (point.y - y2))
	{
		mlx_put_pixel(data->img, point.x, point.y, color);
		point.x += point.dx;
		point.y += point.dy;
		if (point.p >= 0)
			point.p += 2 * point.dy;
		else
			point.p += 2 * (point.dy - (2 * point.dx));
	}
}

void	set_pixel(fdf *data)
{
	t_params	point;

	point.i = 0;
	while (point.i < data->row)
	{
		point.j = 0;
		while (point.j < data->collumn)
		{
			if (point.i + 1 < data->row)
				bresenham(point, point.j, point.i + 1, data);
			if (point.j + 1 < data->collumn)
				bresenham(point, point.j + 1, point.i, data);
			point.j++;
		}
		point.i++;
	}
}
