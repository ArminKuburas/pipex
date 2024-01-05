NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make bonus

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a
SRCS = 	ft_pipex_split.c \
		ft_pipex_utils.c \
		ft_pipex.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFTDIR)
	rm -rf $(OBJS)
fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re