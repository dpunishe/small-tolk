.PHONY		: all clean fclean re

GREEN_COL	:= \033[38;2;0;145;15;1m
UNSET		:= \033[m

CLIENT		:= client
CLIENT_SRC	:= client.c
CLIENT_OBJ	:= $(addprefix obj/, $(CLIENT_SRC:.c=.o))

SERVER		:= server
SERVER_SRC	:= server.c
SERVER_OBJ	:= $(addprefix obj/, $(SERVER_SRC:.c=.o))

FLAGS		:= -Wall -Wextra -Werror -O2

all			: obj/ $(CLIENT) $(SERVER)

obj/ :
	@mkdir obj/

$(CLIENT)	: $(CLIENT_OBJ)
	@gcc $(FLAGS) $(CLIENT_OBJ) -o $(CLIENT)
	@echo "$(GREEN_COL)THE CLIENT IS READY$(UNSET)"

$(SERVER)	: $(SERVER_OBJ) 
	@gcc $(FLAGS) $(SERVER_OBJ) -o $(SERVER)
	@echo "$(GREEN_COL)THE SERVER IS READY$(UNSET)"

obj/%.o		: %.c 
	@gcc $(FLAGS) -c $< -o $@

clean		:
	@rm -rf obj/

fclean		: clean
	@rm -rf $(CLIENT) $(SERVER)

re			: fclean all