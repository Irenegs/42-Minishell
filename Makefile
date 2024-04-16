NAME        := minishell

LIBS        := ft
LIBS_TARGET := libft/libft.a 
INCS        := include libft/include

SRCS        := main.c

OBJS        := $(SRCS:%.c=%.o)
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror

RM          := rm -f
MAKEFLAGS   += --no-print-directory


all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) -L $(dir $(LIBS_TARGET)) $(OBJS) -lreadline -l$(LIBS) -o $(NAME)

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

clean:
	$(MAKE) fclean -C $(dir $(LIBS_TARGET))
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all



.PHONY: clean fclean re
#.SILENT:
