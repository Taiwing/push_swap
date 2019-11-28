#ifndef STACK_MOVES_H
# define STACK_MOVES_H
# include "t_psdata.h"

void	repeat_instruction(t_psdata *psda, void (*f)(t_psdata *psda, char arg),
			unsigned int n, char *cmd);

#endif
