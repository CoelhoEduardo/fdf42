#include "fdf.h"

static int	ft_getwords(char *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

int	get_rows(char *file_name)
{
	int		row;
	int		fd;
	char	*gnl;

	fd = open(file_name, O_RDONLY);
	row = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		row++;
		gnl = get_next_line(fd);
		free(gnl);
	}
	close(fd);
	free(gnl);
	return (row);
}

int	get_collumn(char *file_name)
{
	int		collumn;
	int		fd;
	char	*gnl;

	fd = open(file_name, O_RDONLY);
	gnl = get_next_line(fd);
	collumn = ft_getwords(gnl, ' ');
	close(fd);
	free(gnl);
	return (collumn);
}
