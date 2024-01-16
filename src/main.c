#include "fdf.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	ft_hook(void *param)
{
	fdf *data;

	data = (fdf *)malloc(sizeof(fdf));
	data->mlx = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	// if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	// 	data->shift_y -= 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	// 	data->shift_y += 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	// 	data->shift_x -= 5;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	// 	data->shift_x += 5;
}

int	main(int argc, char **argv)
{
	fdf	*data;

	(void)argc;
	data = (fdf *)malloc(sizeof(fdf));
	data->mlx = mlx_init(WIDTH, HEIGHT, "FDF42", true);
	if (!data->mlx)
		ft_error();
	read_map(argv[1], data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->zoom = 20;
	set_pixel(data);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
