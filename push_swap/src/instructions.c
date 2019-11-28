/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:39:52 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 16:19:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_psdata.h"

const char	*g_instructions[11] = {
	"sa",
	"sb",
	"ss",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr"
};

void		inst_swap(t_psdata *psda, char arg)
{
	if ((arg == 'a' || arg == 's') && psda->stack_a)
		ft_lst_move_front(&psda->stack_a, psda->stack_a->next);
	if ((arg == 'b' || arg == 's') && psda->stack_b)
		ft_lst_move_front(&psda->stack_b, psda->stack_b->next);
}

void		inst_push(t_psdata *psda, char arg)
{
	t_list	*to_move;

	if (arg == 'a' && (to_move = ft_lst_pop(&psda->stack_b, 0)))
	{
		to_move->next = psda->stack_a;
		psda->stack_a = to_move;
		++psda->size_a;
		--psda->size_b;
	}
	else if (arg == 'b' && (to_move = ft_lst_pop(&psda->stack_a, 0)))
	{
		to_move->next = psda->stack_b;
		psda->stack_b = to_move;
		++psda->size_b;
		--psda->size_a;
	}
}

void		inst_rotate(t_psdata *psda, char arg)
{
	if ((arg == 'a' || arg == 'r') && psda->stack_a)
		ft_lst_move_back(&psda->stack_a, psda->stack_a);
	if ((arg == 'b' || arg == 'r') && psda->stack_b)
		ft_lst_move_back(&psda->stack_b, psda->stack_b);
}

void		inst_reverse_rotate(t_psdata *psda, char arg)
{
	if ((arg == 'a' || arg == 'r') && psda->stack_a)
		ft_lst_move_front(&psda->stack_a, ft_lst_last(psda->stack_a));
	if ((arg == 'b' || arg == 'r') && psda->stack_b)
		ft_lst_move_front(&psda->stack_b, ft_lst_last(psda->stack_b));
}

void		add_instruction(t_list **inst, const char *str)
{
	ft_lst_push_back(inst, NULL, 0)->content = (void *)str;
}
