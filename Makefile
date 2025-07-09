#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

MAIN = $(addprefix $(SRCS_PATH)/, main.c exit.c prompt.c)

PARSING = $(addprefix $(PARSING_PATH)/, parsing.c whitespaces_split.c \
parsing_split.c expander.c parse_redirect.c handle_empty_args.c)

SIGNAL = srcs/signals/handle_signals.c

EXEC = $(addprefix $(EXEC_PATH)/, commands.c commands_utils.c commands_utils2.c \
	   pipe_handle.c redirects.c heredoc.c redirect_utils.c free_envp.c \
	   exit_code_utils.c exec_utils.c)

BUILTINS = $(addprefix $(BUILTINS_PATH)/, ft_echo.c ft_cd.c ft_export.c export_utils.c \
		   ft_env.c ft_unset.c ft_exit.c)

UTILS = $(addprefix $(UTILS_PATH)/, main_utils.c expand_utils.c\
split_utils.c parsing_utils.c parsing_utils2.c free_utils.c\
count_utils.c redirect_utils.c redirect_file_assign.c reorganize_utils.c \
parsing_utils3.c expand_utils2.c expand_utils3.c parsing_utils4.c tilde.c)

SRCS = $(UTILS) $(MAIN) $(PARSING) $(SIGNAL) $(EXEC) $(BUILTINS)
OBJS = $(SRCS:.c=.o)

NAME = minishell

SRCS_PATH = srcs
LIBFT_ARC = ./libft/libft.a
LIBFT_PATH = libft
UTILS_PATH = srcs/utils
PARSING_PATH = srcs/parsing
EXEC_PATH = srcs/exec
BUILTINS_PATH = srcs/builtins

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -g -Wall -Werror -Wextra
MAKE = make -s
SILENT_MAKE = make -s extra

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: $(LIBFT_ARC) $(NAME)

$(NAME): $(OBJS) 
	@cc $(CFLAGS) $(OBJS) $(LIBFT_ARC) -o $(NAME) -lreadline
	@echo "$(GRN)[minishell successfully compiled]$(D)"
	
#==============================================================================#
#                                    dependencies                              #
#==============================================================================#

$(LIBFT_ARC): $(LIBFT_PATH)
	@$(SILENT_MAKE) -C $(LIBFT_PATH)

#==============================================================================#
#                                    cleaning rules                            #
#==============================================================================#
clean: 
	@$(RM) $(OBJS)
	@cd ./libft && $(MAKE) clean
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(NAME)
	@cd ./libft && $(MAKE) fclean
	@echo "$(BCYA)[fclean] Archive removed$(D)"

re: fclean all

leaks: all readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all -s ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

.PHONY: all clean fclean re

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
