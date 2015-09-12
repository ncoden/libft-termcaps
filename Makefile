# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 18:00:49 by ncoden            #+#    #+#              #
#    Updated: 2015/09/12 17:19:00 by ncoden           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DEPENDENCIES
LIBFT_H = libs/libft/include

# **************************************************************************** #

NAME = libft-termcaps.a

# COMPILATION
CC = gcc
CCFLAGS = -Wall -Werror -Wextra

ASM = nasm
ASMFLAGS = -f macho64

LNK = gcc
LNKFLAGS =

# DIRECTORIES
SRCDIR = src
OBJDIR = obj
INCDIR =\
	include\
	$(LIBFT_H)

# SOURCES
SRC =\
	termcaps/ft_putchr_trm.c\
	termcaps/ft_putstr_trm.c\
	termcaps/ft_read_trm.c\
	termcaps/ft_tpskeytrigger.c\
	termcaps/ft_trmclosein.c\
	termcaps/ft_trmcloseout.c\
	termcaps/ft_trmclr.c\
	termcaps/ft_trmgetcmd.c\
	termcaps/ft_trmgetin.c\
	termcaps/ft_trmgetout.c\
	termcaps/ft_trmheight.c\
	termcaps/ft_trmkeycmd.c\
	termcaps/ft_trmkeyhook.c\
	termcaps/ft_trmnew.c\
	termcaps/ft_trmputcmd.c\
	termcaps/ft_trmread.c\
	termcaps/ft_trmrestore.c\
	termcaps/ft_trmset.c\
	termcaps/ft_trmsignalcmd.c\
	termcaps/ft_trmsignalhook.c\
	termcaps/ft_trmstart.c\
	termcaps/ft_trmstop.c\
	termcaps/ft_trmwidth.c

# **************************************************************************** #

# ALLOWED EXTENSIONS
EXTENSIONS = .c .s

# SPECIAL CHARS
LOG_CLEAR		= \033[2K
LOG_UP 			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# **************************************************************************** #

.PHONY: all $(NAME) build clean fclean re
.SILENT:

SRC := $(filter $(addprefix %, $(EXTENSIONS)), $(SRC))
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIRS = $(sort $(dir $(OBJS)))

INCS_DIRS = $(addsuffix /, $(INCDIR))
INCS = $(addprefix -I , $(INCS_DIRS))

all: $(NAME)
$(NAME): build $(OBJS)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_YELLOW)assembling...$(LOG_NOCOLOR)$(LOG_UP)"
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	echo "$(LOG_CLEAR)$(NAME)... compiled $(LOG_GREEN)✓$(LOG_NOCOLOR)"
build:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJS_DIRS)
clean:
	rm -f $(LIBS)
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) -c -o $@ $< $(INCS) $(CCFLAGS)
$(OBJDIR)/%.o: $(SRCDIR)/%.s
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(ASM) -o $@ $< $(INCS) $(ASMFLAGS)
