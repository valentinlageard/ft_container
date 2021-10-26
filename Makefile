NAME_FT		=	test
SRC			=	main.cpp

OBJS		=	$(SRC:.cpp=.o)

FLAGS		=	-Wall -Wextra -Werror -std=c++98 -g
CC			=	clang++ $(FLAGS)

$(NAME_FT):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME_FT)

all:		$(NAME_FT)

%.o: %.cpp
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:
			make clean
			rm -f $(NAME_FT)

re:			fclean all

.PHONY: 	all clean fclean re
