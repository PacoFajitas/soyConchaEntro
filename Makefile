# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 19:38:11 by mlopez-i          #+#    #+#              #
#    Updated: 2024/03/18 23:46:17 by tfiguero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SIGNALS_PATH = ./src/signals
LEXER_PATH = ./src/lexer
UTILS_PATH = ./src/utils
ENV_PATH = ./src/env
INC_PATH = ./inc
EXPORT_PATH = ./src/export
BUILTINS_PATH = ./src/builtins
EXEC_PATH = ./src/executor
SYNTAX_PATH = ./src/syntax
EXPANSOR_PATH = ./src/expansor
PARSER_PATH = ./src/parser
ERRORS_PATH = ./src/errors

READLINE_MAKE = inc/readline

LIBFT = inc/libft/libft.a

LIBFT_MAKE = inc/libft

HEADER = inc/minishell.h

SRCS =	./src/main.c \
		./src/init_data.c \

SRCS += $(addprefix $(BUILTINS_PATH)/, cd.c \
		echo.c \
		exit.c \
		pwd.c \
		unset.c)
SRCS += $(addprefix $(ENV_PATH)/, env.c \
		env_utils.c \
		env_utils2.c)
SRCS += $(addprefix $(ERRORS_PATH)/, errors.c)
SRCS += $(addprefix $(EXEC_PATH)/, executor.c \
		exec_utils.c)
SRCS += $(addprefix $(EXPANSOR_PATH)/, expansor.c \
		expan_utils.c )
SRCS += $(addprefix $(EXPORT_PATH)/, export.c \
		export_utils.c)
SRCS += $(addprefix $(LEXER_PATH)/, lexer.c \
		lexer_utils.c \
		lexer_merge.c)
SRCS += $(addprefix $(PARSER_PATH)/, parser.c \
		parser_utils.c)
SRCS += $(addprefix $(SIGNALS_PATH)/, signals.c)
SRCS += $(addprefix $(UTILS_PATH)/, fd_utils.c \
		mem_utils.c \
		lst_utils.c \
		fd_utils2.c)





SRCS += $(addprefix $(SYNTAX_PATH)/, syntax.c)



CC = cc 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I ./inc #-g -fsanitize=address 

RDLFL = -lreadline -ltermcap #-lhistory -lft 
READL = inc/readline/libreadline.a 
HISTORY = inc/readline/libhistory.a

%.o: %.c ${HEADER} Makefile
		@${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all:
		@$(MAKE) -C $(LIBFT_MAKE) --no-print-directory
		@cd inc/readline && ./configure &>/dev/null
		@$(MAKE) -C $(READLINE_MAKE) --no-print-directory
		@$(MAKE) ${NAME} --no-print-directory


${NAME}:: ${OBJS} ${HISTORY} ${READL} ${RDLFL} ${LIBFT}
	@${CC} $(CFLAGS) $(OBJS) $(LIBFT) $(HISTORY) $(READL) $(RDLFL) -o ${NAME}
	@echo "everything done"

clean:
			@$(MAKE) clean -C $(READLINE_MAKE) --no-print-directory
			@$(MAKE) clean -C $(LIBFT_MAKE) --no-print-directory
			@${RM} ${OBJS} 
			@echo "objects removed"

fclean: clean 
			@${RM} ${OBJS} ${NAME}
			@$(MAKE) fclean -C $(LIBFT_MAKE) --no-print-directory
			@echo "everything removed"

re: 
			@$(MAKE) fclean --no-print-directory
			@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
