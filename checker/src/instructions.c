/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:39:52 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 14:45:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	inst_swap(t_list **stack_a, t_list **stack_b, char arg)
{
	if ((arg == 'a' || arg == 's') && *stack_a)
		ft_lst_move_front(stack_a, (*stack_a)->next);
	if ((arg == 'b' || arg == 's') && *stack_b)
		ft_lst_move_front(stack_b, (*stack_b)->next);
}

void	inst_push(t_list **stack_a, t_list **stack_b, char arg)
{
	t_list	*to_move;

	if (arg == 'b')
		ft_swap_p((uintptr_t *)&stack_a, (uintptr_t *)&stack_b);
	if ((to_move = ft_lst_pop(stack_b, 0)))
	{
		to_move->next = *stack_a;
		*stack_a = to_move;
	}
}

void	inst_rotate(t_list **stack_a, t_list **stack_b, char arg)
{
	if ((arg == 'a' || arg == 'r') && *stack_a)
		ft_lst_move_back(stack_a, *stack_a);
	if ((arg == 'b' || arg == 'r') && *stack_b)
		ft_lst_move_back(stack_b, *stack_b);
}

void	inst_reverse_rotate(t_list **stack_a, t_list **stack_b, char arg)
{
	if ((arg == 'a' || arg == 'r') && *stack_a)
		ft_lst_move_front(stack_a, ft_lst_last(*stack_a));
	if ((arg == 'b' || arg == 'r') && *stack_b)
		ft_lst_move_front(stack_b, ft_lst_last(*stack_b));
}
