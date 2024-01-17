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
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
	*x += 650;
	*y += 50;
}

void	connect_line(float x, float y, float x1, float y1, fdf *data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;
	int	color;

	z = data->matrix[(int)y][(int)x].z;
	z1 = data->matrix[(int)y1][(int)x1].z;
	
    // // zoom:
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	
    isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
	
    x += 100;
	y += 100;
	x1 += 100;
	y1 += 100;
	
    x_step = x1 - x;
	y_step = y1 - y;
	
    max = ft_max_value(ft_mod(x_step), ft_mod(y_step));
	
    x_step /= max;
	y_step /= max;
	
	color = (z1 || z) ? 0xFFFFFF : 0xBBFAFF;
	color = (z1 != z) ? 0xFFFFFF : color;
    
	while ((int)(x - x1) || (int)(y - y1))
	{
		if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
			mlx_put_pixel(data->img, x, y, color);
		x += x_step;
		y += y_step;
	}
}

void	set_pixel(fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->row)
	{
		x = 0;
		while (x < data->collumn)
		{
			if (x < data->collumn - 1)
				connect_line(x, y, x + 1, y, data);
			if (y < data->row - 1)
				connect_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}
