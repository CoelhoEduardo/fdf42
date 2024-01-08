NAME	:= FDF.a
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42
LIBFT	:= ./libft

HEADERS	:= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS := $(shell find ./src -iname "*.c")
OBJS := ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS) && printf "Compiling $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) fclean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re:	clean all

.PHONY: all, clean, fclean, re, libmlx, libft

