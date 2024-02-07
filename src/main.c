#include "fdf.h"

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

static void	ft_hook(void *param)
{
	fdf	data;

	data.mlx = param;
	if (mlx_is_key_down(data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data.mlx);
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

int32_t	main(int argc, char **argv)
{
	fdf		data;
	t_enum	enm;

	if (argc != 2)
	{
		ft_putstr_fd("Invalid numbers of arguments", 1);
		return(2);
	}
	data.mlx = mlx_init(WIDTH, HEIGHT, "FDF42", true);
	if (!data.mlx)
		ft_error("Oooh something is wrong");
	data.rows = get_rows(argv[1]);
	data.columns = get_column(argv[1]);
	enm = set_enum_struct();
	data.matrix = read_map(argv[1], data.rows, data.columns, enm);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		ft_error("Oooh something is wrong");
	isometric(data.matrix, data.rows, data.columns);
	set_pixel(data, data.matrix);
	mlx_loop_hook(data.mlx, ft_hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_matrix(data.matrix, data.rows);
	return (EXIT_SUCCESS);
}
