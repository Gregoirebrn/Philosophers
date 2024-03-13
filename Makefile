# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 16:52:20 by grebrune          #+#    #+#              #
#    Updated: 2024/03/13 16:55:49 by grebrune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################

SRCS		:=	philo.c\
				philo_utils.c\

SRCS_D		:=	src/

OBJS_D		:=	objs/

OBJS		:=	$(addprefix $(OBJS_D), $(SRCS:%.c=%.o))

HEAD		:=	philo.h

HEAD_D		:=	.

CFLAGS		:=	-Wall -Wextra -Werror# -g3 -fsanitize=address

BIN			:=	philo

########################################################################################################################
#                                                        RULES                                                         #
########################################################################################################################

all			:
				$(MAKE) $(BIN)

$(BIN)		:	$(OBJS_D) $(OBJS) $(HEAD) Makefile
				$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				$(CC) $(CFLAGS) -I/usr/include -c $< -o $@

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

########################################################################################################################
#                                                        COMMANDS                                                      #
########################################################################################################################

clean		:
				$(RM) -r $(OBJS) $(OBJS_D)

fclean		:	clean
				$(RM) $(BIN)

re			:	fclean all

.PHONY: all bonus clean fclean re
