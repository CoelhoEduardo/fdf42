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
	int color;

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
	int	fd;
	char	*line;
	int	i;
	int	j; 

	i = 0;
	fd = open(file_name, O_RDONLY);
	while (i < data->row)
	{
		line = get_next_line(fd);
		free(line);
		data->split = ft_split(line, ' ');
		j = 0;
		while (j < data->collumn)
		{
			matrix[i][j].z = ft_atoi(data->split[j]);
			matrix[i][j].color = set_color(data->split[j], data);
			free(data->split[j]);
			j++;
		}
		free(data->split);
		i++;
	}
	free(matrix);
	close (fd);
}

t_pixel	**malloc_matrix(int rows, int collumns)
{
	int	i;
	t_pixel	**matrix;

	matrix = (t_pixel **)malloc(sizeof(t_pixel *) * (rows + 1));
	i = 0;
	while (i < rows)
	{
		matrix[i] = (t_pixel *)malloc(sizeof(t_pixel) * (collumns + 1));
		free(matrix[i]);
		i++;
	}
	if (!matrix)
		return (NULL);
	return (matrix);
}

t_pixel	 **read_map(char *file_name, int row, int column)
{
	fdf data;

	data.row = row;
	data.collumn = column;
	data.matrix = malloc_matrix(data.row, data.collumn);
	mount_matrix(&data, file_name, data.matrix);

	return (data.matrix);
}
