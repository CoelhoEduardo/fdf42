#include "fdf.h"

static int	base(char *str, int base)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '-')
	{
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

int	set_color(char *split, fdf *data)
{
	int	color;

	data->hex = ft_split(split, ',');
	if (data->hex[1])
		color = (base(data->hex[1], 16) << 8);
	else
		color = 0xFFFFFF;
	free(data->hex[0]);
	free(data->hex);
	return (color);
}

void	mount_matrix(fdf *data, char *file_name, t_pixel **matrix)
{
	int			fd;
	char		*line;
	t_params	node;

	node.i = 0;
	fd = open(file_name, O_RDONLY);
	while (node.i < data->row)
	{
		line = get_next_line(fd);
		data->split = ft_split(line, ' ');
		node.j = 0;
		while (node.j < data->column)
		{
			matrix[node.i][node.j].z = ft_atoi(data->split[node.j]);
			free(data->split[node.j]);
			node.j++;
		}
		node.i++;
		free(line);
		free(data->split);
	}
	close(fd);
}

t_pixel	**malloc_matrix(int rows, int columns)
{
	int		i;
	t_pixel	**matrix;

	matrix = ft_calloc((rows + 1), sizeof(t_pixel *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		matrix[i] = ft_calloc((columns + 1), sizeof(t_pixel));
		if (!matrix[i])
			return (NULL);
		i++;
	}
	if (!matrix)
		return (NULL);
	return (matrix);
	free(matrix);
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

t_pixel	**read_map(char *file_name, int rows, int columns)
{
	fdf	data;

	data.row = rows;
	data.column = columns;
	data.matrix = malloc_matrix(data.row, data.column);
	mount_matrix(&data, file_name, data.matrix);
	return (data.matrix);
}
