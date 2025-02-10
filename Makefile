#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

SRCS = 

OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))

NAME = 

BUILD_PATH = .build
LIBFT_ARC = ../libft/libft.a

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: deps $(LIBFT_ARC) $(NAME)

$(BUILD_PATH):
	@mkdir $(BUILD_PATH)

$(NAME): $(BUILD_PATH) $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(LIBFT_ARC) -o $(NAME)
	@echo "$(GRN)[ successfully compiled]$(D)"
	
$(BUILD_PATH)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $<

$(LIBFT_ARC): $(LIBFT_PATH)
	@$(MAKEE) -C $(LIBFT_PATH)

deps:
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GRN)[Libft folder found]$(D)"; fi

get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	git clone git@github.com:rfpoliveira/42_Libft.git $(LIBFT_PATH)
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

clean: 
	@$(RM) $(BUILD_PATH)
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BCYA)[fclean] Archive removed$(D)"

re: fclean extra

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
