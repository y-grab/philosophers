NAME	=	philo

SRC		=	main.c \
			init.c \
			utils.c \
			threads.c \
			monitoring.c \

INC		=	-I inc

OBJDIR	=	obj

OBJ	=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CFLAGS	=	-Werror -Wall -Wextra -pthread

.PHONY: all clean fclean re bonus

all : $(OBJDIR) $(NAME)

$(OBJ): $(OBJDIR)/%.o: %.c
	gcc -c $(CFLAGS) $(INC) $< -o $@

$(OBJDIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $^ -o $@ 

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all