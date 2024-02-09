CC=cc
NAME = philo
INCPATH = includes/
SRCPATH = srcs/
SRCS = philo.c utils.c routine.c fork.c
HEADER = philo.h
SRCSINC = $(addprefix $(SRCPATH), $(SRCS))
HEADINC = $(addprefix $(INCPATH), $(HEADER))
OBJS = $(SRCSINC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

all:$(NAME)

$(NAME): $(OBJS)
	@printf "\033[1;37m"
	$(CC) $(OBJS) -o $(NAME) #-fsanitize=thread
	@printf "\033[1;32mCompilation Finished !\n\033[0m"

%.o : %.c $(HEADINC)
	@printf "\033[1;37m"
	$(CC) $(CFLAGS) -I./$(INCPATH)  $< -c -o $@

fclean: clean
	@printf "\033[1;37m"
	rm -f $(NAME)
	@printf "\033[1;31mProgram Deleted !\n\033[0m"

clean:
	@printf "\033[1;37m"
	rm -f $(OBJS)
	@printf "\033[1;31mObjects Deleted !\n\033[0m"

re: fclean all

.PHONY: all fclean clean re
