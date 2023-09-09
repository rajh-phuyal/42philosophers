# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rphuyal <rphuyal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 02:00:58 by rphuyal           #+#    #+#              #
#    Updated: 2023/09/09 18:51:31 by rphuyal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo

CC    = @cc

FLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread

SRC = src/core/main.c \
		src/core/validation.c \
		src/core/initialization.c \
		src/thread/philos.c \
		src/thread/host.c \
		src/thread/single.c \
		src/thread/utils.c \
		src/helpers/time.c \
		src/helpers/ft_atoi.c \
		src/helpers/nodes.c \
		src/helpers/debug.c \
		src/helpers/liberation.c \

OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

# COLORS
CBOLD   = \033[0;1m
RED     = \033[0;41m
GREEN   = \033[0;42m
BLUE   = \033[0;44m
YELLOW  = \033[0;43m
RESET   = \033[0m

all: obj $(NAME)

$(NAME): $(OBJ)
	@echo "$(CBOLD)$(YELLOW)    Compiling $(NAME)   $(RESET)"
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(CBOLD)$(GREEN)      $(NAME) ready!    $(RESET)"

obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ) obj
	@echo "$(CBOLD)$(BLUE)    Objects removed!  $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CBOLD)$(BLUE)    Binaries removed! $(RESET)\n"

re: fclean all

.PHONY: all