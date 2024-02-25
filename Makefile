NAME				= philo

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
CFLAGS				+= -I./include
THREADS				= -lpthread
RM					= rm -f

SRCS_DIR			= ./src/
OBJS_PATH			= ./objs/

SRCS				= $(shell find $(SRCS_DIR) -name '*.c')
OBJS				= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_PATH)%.o)

MAKEFLAGS 			+= --no-print-directory
TOTAL_FILES     	= $(words $(SRCS))
CURRENT_INDEX   	= 0


all:				$(NAME)

$(NAME):			$(OBJS)
					@echo "\n$(BOLD)┗▷$(GREEN)『./philo Created』[✅]$(RESET)"
					@$(CC) $(OBJS) -o $(NAME) $(THREADS)

$(OBJS_PATH)%.o:	$(SRCS_DIR)%.c
					@mkdir -p $(@D)
					@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
					@$(eval PERCENT=$(shell echo $$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES)))))
					@printf "\r$(YELLOW)🔧 $(GREEN)%3d%% $(YELLOW)$(BOLD)Compiling: $(RESET)$(BLUE)$(ITALIC)%-50s $(MAGENTA)[%3d/%3d]$(RESET)" $(PERCENT) "$<" $(CURRENT_INDEX) $(TOTAL_FILES)
					@$(CC) $(CFLAGS) -c $< -o $@



clean:
					@echo "$(BOLD) [🗑️ ] $(YELLOW)$(REVERSED)Cleaning up object files$(RESET)"
					@$(RM) $(OBJS)
					@echo "┗▷$(YELLOW)『\".o\" files from $(ITALIC)./Philo/$(RESET)$(YELLOW) cleaned』$(RESET)"

fclean:				clean
					@$(RM) $(NAME)
					@$(RM) -r $(OBJS_PATH)
					@echo "┗▷$(YELLOW)『executables from $(ITALIC)./Philo/$(RESET)$(YELLOW) cleaned』$(RESET)"

re:					fclean all

.PHONY:				all clean fclean re

# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
RESET := \033[0m

# Text Styles
BOLD := \033[1m
UNDERLINE := \033[4m
REVERSED := \033[7m
ITALIC := \033[3m
