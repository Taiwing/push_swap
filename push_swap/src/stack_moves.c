/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:55:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 17:26:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"
#include "add_to_stack.h"

void	repeat_instruction(t_psdata *psda, void (*f)(t_psdata *psda, char arg),
			unsigned int n, const char *cmd)
{
	char	arg;

	arg = cmd[ft_strlen(cmd) - 1];
	while (n--)
	{
		f(psda, arg);
		add_instruction(&psda->inst, cmd);
	}
}

/*
void	insert_elem(t_psdata *psda, t_list *elem, t_list **target);
{
	t_list	*from;

	from = *target == psda->stack_a ? psda->stack_b : psda->stack_a;
	if (int_cmp(elem->content, from->content))
		get_elem_on_top(psda, elem, from);
}
*/

void	get_elem_on_top(t_psdata *psda, t_list *elem, t_list *stack)
{
	int		cmd;
	int		len;
	int		i_elem;
	int		nb_moves;
	void	(*f)(t_psdata *psda, char arg);
	
	if (!(i_elem = ft_lst_find_index(stack, elem->content, int_cmp)))
		return ;
	len = stack == psda->stack_a ? psda->size_a : psda->size_b;
	nb_moves = i_elem > len - i_elem ? i_elem - len : i_elem;
	f = nb_moves < 0 ? inst_reverse_rotate : inst_rotate;
	cmd = (nb_moves < 0 ? 8 : 5) + (stack == psda->stack_b);
	repeat_instruction(psda, f, nb_moves < 0 ? -nb_moves : nb_moves,
		g_instructions[cmd]);
}

t_list	*find_max(t_list *stack)
{
	t_list	*max;

	max = stack;
	while ((stack = stack->next))
		max = *(int *)stack->content > *(int *)max->content ? stack : max;
	return (max);
}

t_list	*find_min(t_list *stack)
{
	t_list	*min;

	min = stack;
	while ((stack = stack->next))
		min = *(int *)stack->content < *(int *)min->content ? stack : min;
	return (min);
}
