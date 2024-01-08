#include "fdf.h"

float   max1(float a, float b)
{
    if(a < b)
        return (a);
    else
        return (b);
}

float mod(float a)
{
    if (a < 0)
        return (-a);
    else
        return (a);
}

void    bresenham(float x, float y, float x1, float y1, fdf *data)
{
    float x_step;
    float y_step;
    int max;

    // // zoom:
    // x *= data->zoom;
    // y *= data->zoom;
    // x1 *= data->zoom;
    // y1 *= data->zoom;

    x_step = x1 - x;
    y_step = y1 - y;
    max = max1(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(x - x1) || (int)(y - y1))
    {
        mlx_put_pixel(data->img, x, y, 0xFFFFFF);
        x += x_step;
        y += y_step;
    }
}

void draw(fdf *data)
{
    int x;
    int y;

    y=0;
    while (y < data->row)
    {
        x = 0;
        while (x < data->collumn)
        {
            bresenham(x, y, x, y + 1, data);
            bresenham(x, y, x + 1, y, data);
            x++;
        }
        y++;
    }
}
