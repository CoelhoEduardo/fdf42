/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduardocoelho <eduardocoelho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:17:06 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/02/15 17:54:00 by eduardocoel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_hook(void *param)
{
	t_fetch	data;

	data.mlx = param;
	data.img = param;
	mlx_delete_image(data.mlx, data.img);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	if (mlx_is_key_down(data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data.mlx);
}

void	config_rend(t_fetch data, char *argv)
{
	t_enum	enm;

	enm = set_enum_struct();
	data.rows = get_rows(argv);
	data.columns = get_columns(argv);
	data.matrix = read_map(argv, data.rows, data.columns, enm);
	data.mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!data.mlx)
		ft_error("MLX fails to initialize");
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
	check_file(argv[1]);
	config_rend(data, argv[1]);
	return (EXIT_SUCCESS);
}
