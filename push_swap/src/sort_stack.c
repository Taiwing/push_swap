/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:50:35 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 17:05:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_to_stack.h"
#include "stack_moves.h"
#include "inst_stack.h"
#include "instructions.h"
#include "is_sorted.h"
#include "sort_chunks.h"

const int	g_sort_five[10][6] = {
	{3, 3, -1, -1, -1, -1},
	{5, 3, 8, 3, -1, -1},
	{8, 3, 5, 5, 3, -1},
	{3, 5, 3, -1, -1, -1},
	{5, 3, 3, 8, -1, -1},
	{8, 3, 8, 3, 8, -1},
	{7, 3, 8, 3, 5, -1},
	{8, 3, 3, 8, 8, -1},
	{3, 8, 3, 8, 8, -1},
	{3, 3, 5, 5, -1, -1}
};

const int	g_pairs[10][2] = {
	{1, 0},
	{2, 0},
	{3, 0},
	{4, 0},
	{2, 1},
	{3, 1},
	{4, 1},
	{3, 2},
	{4, 2},
	{4, 3}
};

static void	push_pair_back(t_psdata *psda, int push, int reverse)
{
	int	i;

	i = -1;
	while (g_sort_five[push][++i] != -1)
	{
		if (!i && reverse)
		{
			if (g_sort_five[push][i] == 3)
			{
				add_instruction(&psda->inst, g_instructions[1]);
				add_instruction(&psda->inst, g_instructions[3]);
			}
			else if (g_sort_five[push][i] == 7)
				add_instruction(&psda->inst, g_instructions[5]);
			else
				add_instruction(&psda->inst,
					g_instructions[g_sort_five[push][i] + 2]);
		}
		else
			add_instruction(&psda->inst,
				g_instructions[g_sort_five[push][i]]);
	}
}

static void	sort_three(t_psdata *psda)
{
	inst_rotate(psda, 'a');
	if (is_sorted(psda->stack_a))
		return (add_instruction(&psda->inst, g_instructions[5]));
	inst_reverse_rotate(psda, 'a');
	inst_reverse_rotate(psda, 'a');
	if (is_sorted(psda->stack_a))
		return (add_instruction(&psda->inst, g_instructions[8]));
	inst_rotate(psda, 'a');
	inst_swap(psda, 'a');
	add_instruction(&psda->inst, g_instructions[0]);
	if (!is_sorted(psda->stack_a))
	{
		inst_rotate(psda, 'a');
		if (is_sorted(psda->stack_a))
			return (add_instruction(&psda->inst, g_instructions[5]));
		inst_reverse_rotate(psda, 'a');
		inst_reverse_rotate(psda, 'a');
		add_instruction(&psda->inst, g_instructions[8]);
	}
}

static void	sort_four(t_psdata *psda)
{
	int	ind;

	inst_push(psda, 'b');
	add_instruction(&psda->inst, g_instructions[4]);
	if (!is_sorted(psda->stack_a))
		sort_three(psda);
	ind = ft_lst_find_index(psda->sorted_stack, psda->stack_b->content, int_cmp);
	if (!ind || ind == 3)
	{
		inst_push(psda, 'a');
		add_instruction(&psda->inst, g_instructions[3]);
	}
	else
	{
		repeat_instruction(psda, inst_rotate, ind, g_instructions[5]);
		inst_push(psda, 'a');
		add_instruction(&psda->inst, g_instructions[3]);
		repeat_instruction(psda, inst_reverse_rotate,
			ind, g_instructions[8]);
	}
	if (ind == 3)
	{
		inst_rotate(psda, 'a');
		add_instruction(&psda->inst, g_instructions[5]);
	}
}

static void	sort_five(t_psdata *psda)
{
	int		reverse;
	int		pair[2];
	int		i;

	inst_push(psda, 'b');
	add_instruction(&psda->inst, g_instructions[4]);
	inst_push(psda, 'b');
	add_instruction(&psda->inst, g_instructions[4]);
	if (!is_sorted(psda->stack_a))
		sort_three(psda);
	pair[0] = ft_lst_find_index(psda->sorted_stack,
				psda->stack_b->content, int_cmp);
	pair[1] = ft_lst_find_index(psda->sorted_stack,
				psda->stack_b->next->content, int_cmp);
	if ((reverse = pair[0] < pair[1]))
	{
		i = pair[0];
		pair[0] = pair[1];
		pair[1] = i;
	}
	i = -1;
	while (++i < 10 && !(pair[0] == g_pairs[i][0] && pair[1] == g_pairs[i][1]))
		;
	push_pair_back(psda, i, reverse);
}

void		sort_stack(t_psdata *psda)
{
	if (is_sorted(psda->stack_a))
		return ;
	else if (psda->size_a == 2)
		add_instruction(&psda->inst, g_instructions[0]);
	else if (psda->size_a == 3)
		sort_three(psda);
	else if (psda->size_a == 4)
		sort_four(psda);
	else if (psda->size_a == 5)
		sort_five(psda);
	else
		sort_chunks(psda);
//	optimize_inst_stack(&psda->inst);
	print_inst_stack(psda->inst);
}
