NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make bonus

SRCDIR = pipex_files
BONUSDIR = bonus_files
LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a
SRCS = 	$(SRCDIR)/ft_pipex_split.c \
		$(SRCDIR)/ft_pipex.c \
		$(SRCDIR)/ft_pipex_utils.c

all: $(NAME)
$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
clean:
	make clean -C $(LIBFTDIR)
fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re