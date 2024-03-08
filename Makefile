# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 13:59:33 by cfidalgo          #+#    #+#              #
#    Updated: 2024/03/08 19:24:46 by cfidalgo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==========# COLORS #==========#
DEF_COLOR = \033[0m
WHITE_BOLD = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m
#==============================#


#===========# NAME #===========#
NAME = pipex
#==============================#


#=========# COMMANDS #=========#
CC = GCC
CFLAGS = -Wall -Wextra -Werror

RMRF = rm -rf
MKDIR = mkdir -p
#==============================#


#===========# DIRS #===========#
INC = ./
BINC = ./
LIBFT_DIR = libft/
OBJS_DIR = bin/
SRC_DIR = ./
BSRC_DIR = ./
TEST_DIR = .testing/
TEST_BACKUP = tests_backup/
PROGRAM = pipex
#==============================#


#===========# FILE #===========#
FILES = pipex.c \
		state_helpers.c \
		commands_helpers.c \
		fd_helpers.c \
		error_handlers.c

BONUS_FILES = pipex_bonus.c \
				state_helpers_bonus.c \
				commands_helpers_bonus.c \
				fd_helpers_bonus.c \
				error_handlers_bonus.c \
				here_doc_helpers_bonus.c

#==============================#


#===========# SRCS #===========#
SRC = $(addprefix $(SRC_DIR), $(FILES))

BONUSSRC = $(addprefix $(BSRC_DIR), $(BONUS_FILES))
#==============================#


#===========# OBJS #===========#
OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

BONUSOBJS = $(addprefix $(OBJS_DIR), $(BONUS_FILES:.c=.o))
#==============================#


#===========# DEPS #===========#
DEPS = $(OBJS:.o=.d)

BONUSDEPS = $(BONUSOBJS:.o=.d)
#==============================#


#=========== LIBFTs ===========#
LIBFT = libft
LIBFTA = $(LIBFT_DIR)libft.a
#==============================#


#============ TEST ============#
TEST_PREFIX = test_

TEST_MAND = $(TEST_DIR)$(TEST_PREFIX)printf.c
TEST_BONUS = $(TEST_DIR)$(TEST_PREFIX)bonus_printf.c

TEST_MAND_BIN = $(TEST_DIR)test
TEST_BONUS_BIN = $(TEST_DIR)testB
#==============================#


#============ RULE ============#
all: 
	@echo "$(CIAN)Compiling library $(PINK)\"libft.a\"$(CIAN)...$(YELLOW)" 
	@$(MAKE) make_libft --no-print-directory
	@echo "$(GREEN)Library compiled.$(DEF_COLOR)"
	@echo "$(CIAN)Compiling program $(PINK)\"$(NAME)\"$(CIAN)...$(YELLOW)"
	@$(MAKE) $(NAME) --no-print-directory 
	@echo "$(GREEN)Program compiled and ready to use.$(DEF_COLOR)"


ifndef BFLAG
$(NAME):: $(OBJS)
	@$(RMRF) $(BONUSOBJS) $(BONUSDEPS)
	@$(CC) $(CFLAGS) $(LIBFTA) $(OBJS) -o $(NAME)
else
$(NAME):: $(BONUSOBJS)
	@$(RMRF) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(LIBFTA) $(BONUSOBJS) -o $(NAME)
endif


$(OBJS_DIR)%.o: $(SRC_DIR)%.c Makefile
	@$(MKDIR) $(OBJS_DIR)
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP -I $(INC) -c $< -o $@
	@echo "$(YELLOW)Compiling object $(PINK)$<$(YELLOW)...$(DEF_COLOR)"


$(OBJS_DIR)%.o: $(BSRC_DIR)%.c Makefile
	@$(MKDIR) $(OBJS_DIR)
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP -I $(BINC) -c $< -o $@
	@echo "$(YELLOW)Compiling object $(PINK)$<$(YELLOW)...$(DEF_COLOR)"


make_libft: 
	@make bonus -C $(LIBFT) --no-print-directory


clean:
	@$(MAKE) clean --no-print-directory -C $(LIBFT)
	@$(RMRF) $(OBJS_DIR)
	@echo "$(RED)Objects and dependencies for $(YELLOW)'$(NAME)'$(RED) and $(YELLOW)'$(LIBFT)' $(RED)removed.$(DEF_COLOR)"


fclean:
	@$(MAKE) --no-print-directory clean
	@$(RMRF) $(LIBFTA) $(NAME)
	@echo "$(RED)Removed program $(YELLOW)'$(NAME)' $(RED)and library $(YELLOW)'$(LIBFT)'$(RED).$(DEF_COLOR)"


re: fclean all
	@echo "$(BLUE)Program remaked$(DEF_COLOR)"


bonus:
	@$(MAKE) --no-print-directory BFLAG=1

test: all
	@$(MKDIR) $(TEST_DIR)
	@echo "\n$(BLUE)Compiling tests...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(TFLAGS) -I inc/ $(NAME) $(TEST_MAND) -o $(TEST_MAND_BIN)
	@echo "$(PINK)Executing tests...$(WHITE_BOLD)"
	@echo "$(WHITE_BOLD)------------------------------------------------------------"
	@./$(TEST_MAND_BIN)
	@echo "\n------------------------------------------------------------$(DEF_COLOR)"

testB: bonus
	@$(MKDIR) $(TEST_DIR)
	@echo "\n$(BLUE)Compiling tests...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(TFLAGS) -I inc_bonus $(NAME) $(TEST_BONUS) -o $(TEST_BONUS_BIN)
	@echo "$(PINK)Executing tests...$(DEF_COLOR)"
	@echo "$(WHITE_BOLD)------------------------------------------------------------"
	@./$(TEST_BONUS_BIN)
	@echo "\n------------------------------------------------------------$(DEF_COLOR)"

test_clean:
	@echo "$(YELLOW)Creating backup for \"../$(TEST_BACKUP)$(PROGRAM)\"$(DEF_COLOR)"
	@$(MKDIR) ../$(TEST_BACKUP)$(PROGRAM)
	@cp -rf $(TEST_DIR) ../$(TEST_BACKUP)$(PROGRAM)
	@echo "$(RED)Removing tests...$(DEF_COLOR)"
	@$(RMRF) $(TEST_DIR)
#==============================#



#=========== EXTRAS ===========#
.PHONY: all clean fclean re bonus make_libft test testsB test_clean

-include $(DEPS)
-include $(BONUSDEPS)
#==============================#
