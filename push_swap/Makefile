############################## COMPILE VAR #####################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-g
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	../libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
LIBS		=	$(SUB1D)/libft.a
NAME		=	push_swap

############################## SOURCES #########################################

SRCC			=	add_to_stack.c\
					inst_stack.c\
					instructions.c\
					is_sorted.c\
					main.c\
					sort_chunks.c\
					sort_stack.c\
					stack_moves.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(SRCC))

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	make -C $(SUB1D)

add_to_stack.o: t_psdata.h libft.h
inst_stack.o: libft.h instructions.h t_psdata.h
instructions.o: t_psdata.h libft.h
is_sorted.o: libft.h
main.o: add_to_stack.h t_psdata.h libft.h sort_stack.h
sort_chunks.o: instructions.h t_psdata.h libft.h stack_moves.h add_to_stack.h\
	is_sorted.h
sort_stack.o: add_to_stack.h t_psdata.h libft.h stack_moves.h inst_stack.h\
	instructions.h is_sorted.h sort_chunks.h
stack_moves.o: instructions.h t_psdata.h libft.h add_to_stack.h
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	rm -rf $(ODIR)
	make -C $(SUB1D) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
