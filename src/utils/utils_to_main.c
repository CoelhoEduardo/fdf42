/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:19:13 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/07 20:28:56 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit(EXIT_FAILURE);
}

void	free_matrix(t_pixel **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

t_enum	set_enum_struct(void)
{
	t_enum	enm;

	enm.case_1 = 0.5;
	enm.case_2 = 1;
	enm.case_3 = 2;
	enm.case_4 = 4;
	enm.case_5 = 7;
	enm.case_6 = 15;
	enm.case_7 = 25;
	return (enm);
}
