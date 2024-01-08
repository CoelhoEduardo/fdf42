#include "fdf.h"

static void set(t_pixel *matrix, int value, int color, fdf *data)
{
    matrix->position_x = matrix->position_y;
    matrix->position_y = matrix->position_x;
    matrix->value = value;
    matrix->color = color;
    free(data->split[data->j]);
    if (data->hex[1])
        free(data->hex[1]);
    free(data->hex[0]);
    free(data->hex);
}

static void reader(char *file_name, t_pixel **matrix, fdf *data)
{
    data->fd = open(file_name, O_RDONLY);
    data->i = 0;
    data->x = 0;
    while (data->i < data->row)
    {
        data->line = get_next_line(data->fd);
        data->j = 0;
        data->split = ft_split(data->line, ' ');
        data->y = 0;
        while (data->j < data->collumn)
        {
            data->hex = ft_split(data->split[data->j], ',');
            if (data->hex[1])
                set(&matrix[data->i][data->j], ft_atoi(data->split[data->j]) * 5 / 4, 0xFFFFFF, data);
            else
                set(&matrix[data->i][data->j], ft_atoi(data->split[data->j]) * 5 / 4, 0xFF0000FF, data);
            data->j++;
        }
        data->i++;
        free(data->line);
        free(data->split);
    }
    close(data->fd);
}

t_pixel **mallocando(int rows, int collumns)
{
    int i;
    t_pixel **matrix;

    matrix = (t_pixel **)malloc(sizeof(t_pixel *) * (rows + 1));
    if (!matrix)
        return (NULL);
    i = 0;
    while (i < rows){
        matrix[i] = (t_pixel *)malloc(sizeof(t_pixel) * (collumns + 1));
        if (!matrix[i])
            return (NULL);
        i++;
    }
    if (!matrix)
        return (NULL);
    return (matrix);
}

t_pixel **read_map(char *file_name, fdf *data)
{
    data->row = get_rows(file_name);	
  	data->collumn = get_collumn(file_name);
    data->matrix = mallocando(data->row, data->collumn);
    if (!data->matrix)
        return (NULL);
    reader(file_name, data->matrix, data);
    return (data->matrix);
}
