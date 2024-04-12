NAME        := minishell

LIBS        := ft
LIBS_TARGET := libft/libft.a 

INCS        := include    \
    libft/include


SRC			:= main.c

OBJ			:= $(SRC:%.c=%.o)
DEPS        := $(OBJS:.o=.d)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror 
RDFLAGS		:= -lreadline
#-fsanitize=address -g3

CPPFLAGS    := $(addprefix -I,$(INCS))
#-MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

RM          := rm -f

all: $(NAME)
$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(CFLAGS) $(OBJS) $(RDFLAGS) $(LIBS_TARGET) -o $(NAME)

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

%.o: %.c
	$(CC) $(CFLAGS) $< $(RDFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(MAKE) fclean -C $(dir $(LIBS_TARGET)) 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
