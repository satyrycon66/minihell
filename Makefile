#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re
# 'HIDE = @' will hide all terminal output from Make
HIDE = @


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

# Output file name
NAME	=	minishell

# Sources are all .c files
SRCDIR	=	src/
SRCS	=	$(wildcard $(SRCDIR)*.c) # Wildcard for sources is forbidden by norminette

# Objects are all .o files
OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

# Includes are all .h files
INCDIR	=	include/
RL_DIR	=	Readline/
RLDIR	=	Readline-8.1/
RL 		=	rl
RL_A	=	Readline/libreadline.a
INC		=	$(wildcard $(INCDIR)*.h)
INCRL	=	$(wildcard $(RLDIRDIR)*.h)

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME) $(RLDIR)
	@echo "$(Y)MINISHELL READY$(RT)"
	$(HIDE)stty -echoctl
# Generates output file
$(NAME): $(OBJS)
	$(HIDE)$(MAKE) -C libft
	$(HIDE)$(CC) $(CFLAGS) -lreadline -lncurses $(RL_A) libft/libft.a -o $@ $^

# Compiles sources into objects
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INCRL) $(INC) | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)Compiling : $(notdir $<) $(RT)"

# Creates directory for binaries
$(OBJDIR):
	$(HIDE)mkdir -p $@

$(RLDIR):
	mkdir -p $(RLDIR)
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
	tar -xf readline-8.1.tar.gz
	rm readline-8.1.tar.gz
	cd readline-8.1 && bash configure && make
	mv readline-8.1/libreadline.a $(RL_DIR)
# rm -rf readline-8.1
# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
	$(HIDE)$(MAKE) -C libft clean

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(RM)r $(RL_DIR)
	$(HIDE)$(RM)r $(RLDIR)

# Removes objects and executables and remakes
re: clean all
	$(HIDE)$(MAKE) -C libft clean

test: all
	./minishell

test_l:
	leaks --atExit -- ./minishell


RT	:= \033[0m
BK 	:= \033[90;1m
R 	:= \033[91;1m
G	:= \033[92;1m
Y	:= \033[93;1m
B 	:= \033[94;1m
P	:= \033[95;1m
C	:= \033[96;1m
W	:= \033[97;1m
