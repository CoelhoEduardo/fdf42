/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:17:06 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/08 12:38:46 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_hook(void *param)
{
	t_fetch	data;

	data.mlx = param;
	if (mlx_is_key_down(data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data.mlx);
}

void	config_rend(t_fetch data, char **argv)
{
	t_enum	enm;

	enm = set_enum_struct();
	data.rows = get_rows(argv[1]);
	data.columns = get_column(argv[1]);
	data.matrix = read_map(argv[1], data.rows, data.columns, enm);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		ft_error("Rendering failed (-1)");
	set_pixel(data, data.matrix);
	mlx_loop_hook(data.mlx, ft_hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_matrix(data.matrix, data.rows);
}

int32_t	main(int argc, char **argv)
{
	t_fetch	data;

	if (argc != 2)
	{
		ft_putstr_fd("Invalid numbers of arguments", 1);
		return (2);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!data.mlx)
		ft_error("MLX fails to initialize");
	config_rend(data, argv);
	return (EXIT_SUCCESS);
}
