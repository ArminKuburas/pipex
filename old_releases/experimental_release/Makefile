NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make bonus

SRCDIR = pipex_files
BONUSDIR = bonus_files
LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a
SRCS = 	$(SRCDIR)/ft_pipex_split.c \
		$(SRCDIR)/ft_pipex_utils.c
BONUS_SRCS = 	$(BONUSDIR)/ft_pipex_bonus.c \
				$(BONUSDIR)/ft_pipex_utils_bonus.c \
				$(BONUSDIR)/here_doc_handler_bonus.c

all: $(NAME)
$(NAME): $(SRCS) $(LIBFT) $(SRCDIR)/ft_pipex.c
	$(CC) $(CFLAGS) $(SRCS) $(SRCDIR)/ft_pipex.c $(LIBFT) -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

bonus: .bonus

.bonus: $(SRCS) $(BONUS_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(BONUS_SRCS) $(LIBFT) -o $(NAME)
	@touch .bonus
clean:
	make clean -C $(LIBFTDIR)
fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re bonus