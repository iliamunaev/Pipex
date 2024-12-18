NAME = libft.a

CC = cc

# The CFLAGS variable sets compile flags for cc:
# -Wall   : Give verbose compiler warnings
# -Wextra : Enables extra warning flags that are not enabled by -Wall
# -Werror : Make all warnings into errors
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = ft_atoi.c \
      ft_bzero.c \
      ft_calloc.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_itoa.c\
      ft_memchr.c \
      ft_memcmp.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memset.c \
      ft_putchar_fd.c\
      ft_putendl_fd.c\
      ft_putnbr_fd.c\
      ft_putstr_fd.c\
      ft_substr.c\
      ft_split.c\
      ft_strchr.c \
      ft_striteri.c\
      ft_strjoin.c\
      ft_strdup.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strmapi.c\
      ft_strncmp.c \
      ft_strnstr.c \
      ft_strrchr.c \
      ft_strtrim.c\
      ft_tolower.c \
      ft_toupper.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Header file
HEADER = libft.h

# Default rule to create the library
all: $(NAME)

# Main target to create the library
#  - 'r': Replace or add files into the archive
#  - 'c': Create the archive if it does not exist
#  - 's': Write an index (symbol table) into the archive for faster linking
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Rule to compile source files into object files in the obj directory
$(OBJ_DIR)/%.o: %.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Ensure the obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Phony targets to prevent make from thinking these are files
.PHONY: all clean fclean re

# Clean object files and directory
clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

# Clean all generated files (including the library)
fclean: clean
	rm -f $(NAME)

# Clean and rebuild the project
re: fclean all
