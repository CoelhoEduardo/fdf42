#include "fdf.h"

int	ft_mod(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

int	ft_max_value(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.9);
	*y = (*x + *y) * sin(0.9) - z;
}

void	set_zoom(t_params *point, fdf *data)
{
	point->x1 *= data->zoom;
	point->y1 *= data->zoom;
	point->x2 *= data->zoom;
	point->x2 *= data->zoom;
}

void	set_params(t_params *point, fdf *data)
{
	set_zoom(point, data);
	isometric(&point->x1, &point->y1, point->z);
	isometric(&point->x2, &point->y2, point->z1);
	point->x1 += 600;
	point->y1 += 300;
	point->x2 += 600;
	point->x2 += 300;
}

void	calc_d(t_params *point, t_pixel **matrix, int i, int j)
{
	point->x1 = point->x;
	point->y1 = point->y;
	point->x2 = matrix[i][j].x;
	point->y2 = matrix[i][j].y;
	point->x_step = abs((int)point->x2 - (int)point->x1);
	point->y_step = abs((int)point->y2 - (int)point->y1);
	// point->max = ft_max_value(ft_mod(point->x_step), ft_mod(point->y_step));
	// point->x_step /= point->max;
	// point->y_step /= point->max;
}

void	conditioner(t_params *p)
{
	if (p->x_step > p->y_step)
		p->err = p->x_step / 2;
	else
		p->err = -p->y_step / 2;
}

void	put_pixel(t_params *point, fdf *data)
{
	point->z = data->matrix[(int)point->y1][(int)point->x1].z;
	point->z1 = data->matrix[(int)point->y2][(int)point->x2].z;
	// set_params(point, data);
	point->color = (point->z1 || point->z) ? 0xFFFFFF : 0xBBFAFF;
	point->color = (point->z1 != point->z) ? 0xFFFFFF : point->color;
	while ((int)(point->x1 - point->x2) || (int)(point->y1 - point->y2))
	{
		if ((point->x1 > 0 && point->x1 < WIDTH) && (point->y1 > 0 && point->y1 < HEIGHT))
			mlx_put_pixel(data->img, point->x1, point->y1, point->color);
		point->x1 += point->x_step;
		point->y1 += point->y_step;
	}

}

void	connect_line(t_pixel **matrix, t_params point, fdf *data)
{	
	if (point.j + 1 < data->collumn)
	{
		calc_d(&point, matrix, point.i, point.j + 1);
		conditioner(&point);
		put_pixel(&point, data);
	}
	if (point.i + 1 < data->row)
	{	
		calc_d(&point, matrix, point.i + 1, point.j);
		conditioner(&point);
		put_pixel(&point, data);
	}
}

void	set_pixel(fdf *data)
{
	t_params	p;

	p.i = 0;
	while (p.i < data->row)
	{
		p.j = 0;
		while (p.j < data->collumn)
		{
			p.x = data->matrix[p.i][p.j].x;
			p.y = data->matrix[p.i][p.j].y;
			connect_line(data->matrix, p, data);
			p.j++;
		}
		p.i++;
	}
}
