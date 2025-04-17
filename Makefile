NAME = philo
SOURCES = addition.c\
			check_for_input.c\
			observer.c\
			philosophers.c\
			routines.c\
			threads.c\


OBJS = $(SOURCES:.c=.o)
CC = cc
CFLAGS =  -Wall -Werror -Wextra
THREADFLAGS = -lpthread

all:$(NAME)

$(NAME):$(OBJS)
	cc $(CFLAGS) $(THREADFLAGS) -o $(NAME) $(OBJS) 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
