/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rows_columns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:31:01 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/15 20:39:07 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fd < 0)
		ft_error("error \n");
	row = 0;
	gnl = get_next_line(fd);
	free(gnl);
	while (gnl)
	{
		row++;
		gnl = get_next_line(fd);
		free(gnl);
	}
	if (row <= 1)
		ft_error("Nothing to read \n");
	close(fd);
	return (row);
}

int	get_columns(char *file_name)
{
	int		column;
	int		fd;
	char	*gnl;

	fd = open(file_name, O_RDONLY);
	gnl = get_next_line(fd);
	column = ft_getwords(gnl, ' ');
	while (gnl != NULL)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	return (column);
}
