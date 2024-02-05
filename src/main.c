#include "fdf.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	ft_hook(void *param)
{
	fdf	data;

	data.mlx = param;
	if (mlx_is_key_down(data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data.mlx);
}

int	main(int argc, char **argv)
{
	fdf	data;

	(void)argc;
	data.mlx = mlx_init(WIDTH, HEIGHT, "FDF42", true);
	if (!data.mlx)
		ft_error();
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		ft_error();
	data.row = get_rows(argv[1]);
	data.column = get_column(argv[1]);
	data.matrix = read_map(argv[1], data.row, data.column);
	set_pixel(&data);
	mlx_loop_hook(data.mlx, ft_hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
