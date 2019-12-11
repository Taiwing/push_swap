############################## COMPILE VAR #####################################

SUB1D		=	push_swap
SUB2D		=	checker
SUB3D		=	libft
SUB4D		=	comb_gen

############################## BUILD ###########################################

all: push_swap checker libft comb_gen

push_swap:
	make -C $(SUB1D)

checker:
	make -C $(SUB2D)

libft:
	make -C $(SUB3D)

comb_gen:
	make -C $(SUB4D)

############################## CLEANUP #########################################

clean:
	make -C $(SUB1D) clean
	make -C $(SUB2D) clean
	make -C $(SUB3D) clean
	make -C $(SUB4D) clean

fclean:
	make -C $(SUB1D) fclean
	make -C $(SUB2D) fclean
	make -C $(SUB3D) fclean
	make -C $(SUB4D) fclean

re: fclean all

.PHONY: push_swap checker libft comb_gen all clean fclean re
