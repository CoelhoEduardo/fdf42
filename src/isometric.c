/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:03:32 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/06 23:15:15 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    isometric(t_pixel   **matrix, int rows, int columns)
{
    int i;
    int j;

    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < columns)
        {
            matrix[i][j].x = (matrix[i][j].x - matrix[i][j].y * cos(0.8));
            matrix[i][j].y = (matrix[i][j].x + matrix[i][j].y * sin(0.9))  - matrix[i][j].z;
            matrix[i][j].x += 500;
            matrix[i][j].y += 200;
            j++;
        }
        i++;
    }
}