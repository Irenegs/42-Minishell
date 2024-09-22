NAME        := minishell

LIBS        := ft
LIBS_TARGET := libft/libft.a 
INCS        := include libft/include

SRCS        := built_in_check.c built_in.c built_in_env_exit.c built_in_echo.c\
				built_in_utils1.c built_in_utils2.c built_in_utils3.c \
				command.c command_utils.c \
				error.c \
				expander.c expander_variables.c expander_quotes.c expander_utils.c\
				execute.c execute_simple.c \
				extract_command.c extract_element.c  extract_file.c extract_pipe.c \
				extract_utils.c extract_utils2.c \
				heredoc_delimiter.c heredoc_files.c heredoc_files_utils.c heredoc_text.c heredoc_expand.c\
				pipe_utils.c \
				parser.c super_split.c split_utils.c \
				struct.c signals.c signals_hd.c\
				main.c \
				split_element.c \
				utils_arrays.c utils_char.c utils_variable.c \
			

OBJS        := $(SRCS:%.c=%.o)
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror

RM          := rm -f
MAKEFLAGS   += --no-print-directory


all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(CFLAGS) -L $(dir $(LIBS_TARGET)) $(OBJS) -lreadline -l$(LIBS) -o $(NAME)

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
