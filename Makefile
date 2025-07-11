NAME	:= FDF.a
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42
LIBFT	:= ./libft

HEADERS	:= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS_PATH	:= ./src/
SRCS := main.c count_rows_columns.c read_map.c set_pixel.c isometric.c \
		/utils/utils_to_main.c /utils/utils_to_read_map.c
OBJS := $(addprefix $(SRCS_PATH), $(SRCS:.c=.o))

all: libmlx libft $(NAME)

# Clone MLX42 if not present, using a stamp file
.MLX42_cloned:
	git clone git@github.com:codam-coding-college/MLX42.git $(LIBMLX)
	touch $@

# Clone libft if not present, using a stamp file
.libft_cloned:
	git clone git@github.com:CoelhoEduardo/libft.git $(LIBFT)

libmlx: .MLX42_cloned
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft: .libft_cloned
	@make -C $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS) && printf "Compiling $(notdir $<) \n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@rm	-rf .MLX42_cloned
	@make -C $(LIBFT) fclean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	@rm	-rf .MLX42_cloned
	@make -C $(LIBFT) fclean
	@rm -rf $(LIBFT)

re:	clean all

valgrind: all
	valgrind --leak-check=full --gen-suppressions=all --show-leak-kinds=all --suppressions=./MLX42_SUPP.supp ./FDF.a test_maps/42.fdf

.PHONY: all clean fclean re libmlx libft