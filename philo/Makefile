HEADER = ./inc/philo.h

SRC_DIR = ./src/

SRCS_NAME =	main.c\
			ft_utils.c\
		
SRCS = 	$(addprefix ${SRC_DIR}, ${SRCS_NAME})

OBJS =	${SRCS:.c=.o}

NAME =	philo	

CC =	cc

CFLAGSDEV =	-Wall -Wextra -Werror -g3

CFLAGS =	-Wall -Wextra -Werror

.c.o:	
		@echo "\033[32m\c"
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		@echo "\033[0m\c"

all:	${NAME}

${NAME}:	${OBJS} ${HEADER}
			@echo "\033[32m\c"
			${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "Link complete for exec --> \033[4;36;1m${NAME}\033[0m"

clean:
		@rm -rf ${OBJS}
		@echo "\033[32m${NAME} obj cleaned"

fclean:		clean
		@rm -rf ${NAME}
		@echo "\033[32m${NAME} fcleaned"

re:		fclean all

.PHONY:	all clean re