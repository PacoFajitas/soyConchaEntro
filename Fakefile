# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlopez-i <mlopez-i@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 19:27:08 by mlopez-i          #+#    #+#              #
#    Updated: 2024/02/05 19:37:45 by mlopez-i         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PARSER_PATH = ./src/parser
INC_PATH = ./inc

PRINTF = inc/PRINTF/libftprintf.a
PRINTF_MAKE = inc/PRINTF
LIBFT = inc/libft/libft.a
LIBFT_MAKE = inc/LIBFT
READLINE_MAKE = inc/READLINE

HEADER = inc/minishell.h

SRCS = ./src/main.c

SRCS += $(addprefix $(PARSER_PATH)/, parser.c \
	   parser_utils.c \
	   msh_words.c \
	   msh_words_utils.c \
	   check_errors.c)

EXPANDER_PATH = ./src/expander

SRCS += $(addprefix $(EXPANDER_PATH)/, expander.c \
		expand_utils.c \
		expand_utils2.c \
		expand_dots.c) 

BUILTINS_PATH = ./src/builtins

SRCS += $(addprefix $(BUILTINS_PATH)/, blt_exit.c \
		blt_echo.c \
		blt_cd.c \
		blt_pwd.c \
		blt_env_utils.c \
		blt_env_utils2.c \
		blt_env_utils3.c \
		blt_export.c \
		blt_env.c \
		blt_unset.c \
		blt_export_utils.c)

EXECUTOR_PATH = ./src/executor

SRCS += $(addprefix $(EXECUTOR_PATH)/, executor.c \
		exe_redirects.c \
		heredoc.c \
		blt_checks.c \
		exe_cmd.c \
		exe_utils.c)

SIGNALS_PATH = ./src/signals

SRCS += $(addprefix $(SIGNALS_PATH)/, signals.c \
		) 


CC = cc 
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I ./INC

RDLFL = -lreadline -ltermcap #-lhistory -lft 
READL = INC/readline/libreadline.a 
HISTORY = INC/readline/libhistory.a

%.o: %.c ${HEADER} Makefile
		@${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all:
		@$(MAKE) -C $(LIBFT_MAKE) --no-print-directory
		@$(MAKE) -C $(PRINTF_MAKE) --no-print-directory
		@cd inc/readline && ./configure &>/dev/null
		@$(MAKE) -C $(READLINE_MAKE) --no-print-directory
		@$(MAKE) ${NAME} --no-print-directory

${NAME}:: ${OBJS} $(LIBFT) $(PRINTF)
	@${CC} $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(HISTORY) $(READL) $(RDLFL) -o ${NAME}
	@echo "EVERYTHING DONE✌️   "

clean:
			@$(MAKE) clean -C $(LIBFT_MAKE) --no-print-directory
			@$(MAKE) clean -C $(PRINTF_MAKE) --no-print-directory
			@$(MAKE) clean -C $(READLINE_MAKE) --no-print-directory
			@${RM} ${OBJS} 
			@echo "OBJECTS REMOVED😭   "

fclean: clean 
			@$(MAKE) fclean -C $(LIBFT_MAKE) --no-print-directory
			@$(MAKE) fclean -C $(PRINTF_MAKE) --no-print-directory
			@${RM} ${OBJS} ${NAME}
			@echo "EVERYTHING REMOVED😭 "

re: 
			@$(MAKE) fclean --no-print-directory
			@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re