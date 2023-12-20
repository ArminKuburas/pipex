NAME = pipex

SRCDIR = pipex_source_files
INCDIR = header_file
OBJDIR = object_files
LIBFTDIR = libft
LIBFT =  $(LIBFTDIR)/libft.a
AR = ar rcs
LIB = ranlib

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES =	$(SRCDIR)/ft_pipex_split.c \
			$(SRCDIR)/ft_pipex.c \
			$(SRCDIR)/ft_strcmp.c \
			$(SRCDIR)/ft_strndup.c \
			$(SRCDIR)/pipex_utils.c \

SRC_OBJS =	$(addprefix $(OBJDIR)/,$(notdir $(SRC_FILES:.c=.o)))

all: $(LIBFT) $(NAME)
	chmod +x $(NAME)

$(NAME): $(SRC_OBJS) $(LIBFT) 
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(SRC_OBJS)
	$(LIB) $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR) bonus 

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
clean:
	make -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)
fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re