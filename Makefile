#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

MAIN = $(addprefix $(SRCS_PATH)/, main.c exit.c prompt.c)
PARSING = $(addprefix $(PARSING_PATH)/, parsing.c whitespaces_split.c \
parsing_split.c expander.c)
SIGNAL = srcs/signals/handle_signals.c
UTILS = $(addprefix $(UTILS_PATH)/, main_utils.c expand_utils.c\
split_utils.c parsing_utils.c parsing_utils2.c free_utils.c)

SRCS = $(UTILS) $(MAIN) $(PARSING) $(SIGNAL)
OBJS = $(SRCS:.c=.o)

NAME = minishell

SRCS_PATH = srcs
LIBFT_ARC = ./libft/libft.a
LIBFT_PATH = libft
UTILS_PATH = srcs/utils
PARSING_PATH = srcs/parsing

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -g -Wall -Werror -Wextra
LEAKS = -fsanitize=leak
SILENT_MAKE = make -s extra

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: deps $(LIBFT_ARC) $(NAME)

$(NAME): $(OBJS) 
	@cc $(CFLAGS) $(LEAKS) $(OBJS) $(LIBFT_ARC) -o $(NAME) -lreadline
	@echo "$(GRN)[minishell successfully compiled]$(D)"
	
#==============================================================================#
#                                    dependencies                              #
#==============================================================================#

$(LIBFT_ARC): $(LIBFT_PATH)
	@$(SILENT_MAKE) -C $(LIBFT_PATH)

deps:
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GRN)[Libft folder found]$(D)"; fi

get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	git clone git@github.com:rfpoliveira/42_Libft.git $(LIBFT_PATH)
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

#==============================================================================#
#                                    cleaning rules                            #
#==============================================================================#
clean: 
	@$(RM) $(OBJS)
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_PATH)
	@echo "$(BCYA)[fclean] Archive removed$(D)"

re: fclean all

again: clean all

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
