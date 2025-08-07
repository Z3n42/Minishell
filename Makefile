NAME = minishell

CC=gcc

CFLAGS= -Wall -Wextra -Werror

BUILTIN = ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset

EXECUTOR = ft_executor_utils ft_executor_utils_2 ft_executor ft_input ft_output ft_dup ft_clean_quotes

LEXER = lexer

LIST =  ft_del_node ft_freelist ft_freelist2d ft_get_last_node \
		ft_list_size ft_list_to_char_table \
		ft_lst_new ft_lstadd_back ft_node_position ft_words_to_list

PARSER = ft_parser

SHEL = ft_shell

SYNTAX = ft_syntaxchecker ft_syntax

UTILS = ft_append_ctostr ft_append_tostr ft_atoi ft_getenv ft_isalnum \
		ft_isalpha ft_isdigit ft_isspace ft_itoa ft_split ft_str_to_lower \
		ft_strcat ft_strcontainstext ft_strcpy ft_strcut_toend ft_strequals \
		ft_strisalnum ft_strlen ft_strstartwith ft_substr ft_free_chartable

SRC = $(addsuffix .c, $(addprefix builtin/, $(BUILTIN))) \
	  $(addsuffix .c, $(addprefix executor/, $(EXECUTOR))) \
	  $(addsuffix .c, $(addprefix lexer/, $(LEXER))) \
	  $(addsuffix .c, $(addprefix list/, $(LIST))) \
	  $(addsuffix .c, $(addprefix parser/, $(PARSER))) \
	  $(addsuffix .c, $(addprefix shel/, $(SHEL))) \
	  $(addsuffix .c, $(addprefix syntax/, $(SYNTAX))) \
	  $(addsuffix .c, $(addprefix utils/, $(UTILS))) \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
# /opt/homebrew/Cellar/readline/8.1.1/include
# ~/.brew/opt/readline/lib

%.o: %.c
		@${CC} ${CFLAGS} -I ~/.brew/opt/readline/lib -I ./includes -c $< -o $@ -I ~/.brew/opt/readline/include
#-I ~/.brew/opt/readline/include 

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

sanitize:
	gcc ./shell/ft_shell.c ./parser/ft_parser.c ./utils/*.c ./list/*.c  ./syntax/*.c ./lexer/*.c ./executor/*.c ./builtin/*.c  -o minishell -lreadline  -fsanitize=address -g3 -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
.PHONY: