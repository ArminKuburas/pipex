NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make bonus

LIBFTDIR = libft
OBJDIR = object_files

LIBFT = $(LIBFTDIR)/libft.a

SRCS = 	ft_pipex_split.c \
		ft_pipex_utils.c \
		ft_pipex.c \
		ft_message_handler.c \
		ft_path_make.c

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -rf $(NAME)
libft_clean:
	make clean -C $(LIBFTDIR)
libft_fclean:
	make fclean -C $(LIBFTDIR)

re: fclean all
.PHONY: all clean fclean re libft_clean libft_fclean