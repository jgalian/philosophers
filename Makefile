NAME =	philo
CC =	gcc
FLAGS = -c -Wall -Wextra -Werror -g -g3 -fsanitize=address
OBJS =	$(SRCS:.c=.o)
SRCS =	philo.c utils.c setup.c threads.c

philo: $(SRCS)
	$(CC) $(FLAGS) $(SRCS)
	mkdir -p obj
	mv *.o obj/
	gcc -pthread -o $(NAME) obj/*.o -g3 -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f obj/*.o
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
