NAME = philo
SOURCES = 	add_mutaxes.c\
			addition_checking_input.c\
			addition_routine.c\
			addition_freeing.c\
			addition_freeing_pt2.c\
			addition_printing.c\
			check_for_input.c\
			observer.c\
			philosophers.c\
			routines.c\
			threads.c\

OBJS = $(SOURCES:.c=.o)
CC = cc
CFLAGS =  -Wall -Werror -Wextra
LDLIBS =  -lpthread

all:$(NAME)

$(NAME):$(OBJS)
	cc $(CFLAGS) $(LDLIBS) -o $(NAME) $(OBJS) 

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
