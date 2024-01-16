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

static void	set_color(char *split, fdf *data)
{
	data->hex = ft_split(split, ',');
	if (data->hex[1])
		data->color = base(data->hex[1], 16);
	else
		data->color = 0xFFFFFF;
	free(data->hex);
}

void	fill_matrix(int *matrix, char *line, fdf *data)
{
	int	i;

	data->split = ft_split(line, ' ');
	i = 0;
	while (i < data->collumn)
	{
		matrix[i] = ft_atoi(data->split[i]);
		set_color(data->split[i], data);
		i++;
	}
	free(data->split);
}

int	**malloc_matrix(int rows, int collumns)
{
	int	i;
	int	**matrix;

	matrix = (int **)malloc(sizeof(int *) * (rows + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		matrix[i] = (int *)malloc(sizeof(int) * (collumns + 1));
		if (!matrix[i])
			return (NULL);
		i++;
	}
	if (!matrix)
		return (NULL);
	return (matrix);
}

void	read_map(char *file_name, fdf *data)
{
	int		fd;
	char	*line;
	int		i;

	data->row = get_rows(file_name);
	data->collumn = get_collumn(file_name);
	data->matrix = malloc_matrix(data->row, data->collumn);
	fd = open(file_name, O_RDONLY, 0);
	i = 0;
	while (i < data->row)
	{
		line = get_next_line(fd);
		fill_matrix(data->matrix[i], line, data);
		i++;
	}
	close(fd);
	data->matrix[i] = NULL;
}
