NAME = server
FLAGS = -Wall -Wextra -Werror
SERVER_SRC = server.c
CLIENT_SRC = client.c
FT_PRINTF_SRC = ft_printf.c
CLIENT= client

all: $(CLIENT) $(NAME) 

$(NAME): $(SERVER_SRC)
	@cc $(FLAGS) $(SERVER_SRC) $(FT_PRINTF_SRC) -o $(NAME)

$(CLIENT): $(CLIENT_SRC)
	@cc $(FLAGS) $(CLIENT_SRC) $(FT_PRINTF_SRC) -o $(CLIENT)

clean:
	@rm -f $(NAME) $(CLIENT)

fclean: clean

re: clean all
