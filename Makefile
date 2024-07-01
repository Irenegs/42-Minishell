NAME        := minishell

LIBS        := ft
LIBS_TARGET := libft/libft.a 
INCS        := include libft/include

SRCS        := command.c command_utils.c \
				execute.c execute_simple.c pipe_utils.c \
				extract_command.c extract_element.c  extract_file.c extract_pipe.c extract_utils.c \
				parser.c super_split.c split_utils.c \
				built_in.c built_in2.c built_in3.c built_in4.c \
				struct.c signals.c \
				heredocs.c heredocs_utils.c heredoc_text.c heredoc_expand.c gnl.c\
				main.c \
			

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
