NAME = ft_container

SRCS = main.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

HEADER = enable_if.hpp equal.hpp is_integral.hpp iterators_traits.hpp \
			lexicographical_compare.hpp make_pair.hpp reverse_iterator.hpp \
			conditional.hpp vector.hpp Red_Black_Tree_Iterator.hpp \
			Red_Black_Tree.hpp map.hpp set.hpp

FLAGS = -Wall -Wextra -Werror -g -std=c++98

CC = clang++

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
