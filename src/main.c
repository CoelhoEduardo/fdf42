
#include "fdf.h"

#define WIDTH 512
#define HEIGHT 512

#define BPP sizeof(int32_t)

static void ft_error(void)
{
  fprintf(stderr, "%s", mlx_strerror(mlx_errno));
  exit(EXIT_FAILURE);
}

int32_t main(int argc, char **argv)
{
	fdf *data;

	(void)argc;
	data = (fdf *)malloc(sizeof(fdf));
	data->matrix = read_map(argv[1], data);
  	data->mlx = mlx_init(WIDTH, HEIGHT, "42balls", true);
  	if (!data->mlx)
    	ft_error();

  	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
  	if(!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
	// bresenham(10, 10, 600, 300, data);
	data->zoom = 20;
	draw(data);
  	mlx_loop(data->mlx);
  	mlx_terminate(data->mlx);
  	return (EXIT_SUCCESS);
}

// int	main(int argc, char **argv)
// {
// 	fdf *data;

// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;

// 	(void)argc;
// 	data = (fdf *)malloc(sizeof(fdf));
// 	data->matrix = read_map(argv[1], data);
// 	data->zoom = 20;
// 	draw(data);
// 	printf("%p", draw);
// 	while (i < data->row){
//         while (j < data->collumn)
// 		{ 
// 			printf("%3d", data->matrix[i][j].value);
// 			j++;
// 		}
// 		j = 0;
// 		printf("\n");
//         i++;
//     }
// 	return(0);
// }
