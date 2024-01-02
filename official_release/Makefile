CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make

SRCDIR = pipex_source_files
BONUSDIR = pipex_bonus_files
OBJDIR = object_files
LIBFTDIR = libft
HEADERDIR = header_files

SRCS =	$(SRCDIR)/ft_get_path.c \
		$(SRCDIR)/ft_pipex_split.c \
		$(SRCDIR)/ft_pipex.c \
		$(SRCDIR)/ft_strcmp.c \
		$(SRCDIR)/ft_strndup.c \
		$(SRCDIR)/pipex_utils.c
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

BONUS_SRCS =	$(BONUSDIR)/exit_handler_bonus.c \
				$(BONUSDIR)/ft_handle_file_bonus.c \
				$(BONUSDIR)/here_doc_handler_bonus.c \
				$(BONUSDIR)/pipex_bonus.c
BONUS_OBJS = $(addprefix $(OBJDIR)/, $(notdir $(BONUS_SRCS:.c=.o)))
LIBFT = $(LIBFTDIR)/libft.a
LIB = ranlib
NAME = pipex
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) $(OBJS) -L$(LIBFTDIR) -lft -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
$(OBJDIR):
	mkdir -p $(OBJDIR)

bonus: .bonus
		
.bonus: $(OBJDIR) $(OBJS) $(BONUS_OBJS)
		$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
		@touch .bonus

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)
fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re

