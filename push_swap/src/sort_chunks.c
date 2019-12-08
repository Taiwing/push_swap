/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:38:14 by yforeau           #+#    #+#             */ /*   Updated: 2019/11/29 17:14:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"
#include "stack_moves.h"
#include "add_to_stack.h"
#include "is_sorted.h"

#define SLOPE		0.0225
#define INTERCEPT	4.75

static int	get_chunk_size(int i, int nb_chunks, int stack_size)
{
	static int	intercept = 0;
	static int	slope = 0;
	double		d_slope;
	int			base;
	int			min;

	if (!i)
	{
		base = stack_size / nb_chunks;
		min = base / 2;
		intercept = base + min;
		d_slope = (double)-base / (double)(nb_chunks - 1);
		slope = d_slope < (double)(int)d_slope ? (int)d_slope - 1 : (int)d_slope;
		base = intercept;
		while (i < nb_chunks - 1 && base <= stack_size)
			base += get_chunk_size(++i, nb_chunks, stack_size);
		intercept += (stack_size - base) / nb_chunks;
		return (intercept + ((stack_size - base) % nb_chunks));
	}
	return (slope * i + intercept);
}

static void	init_chunks(t_psdata *psda, t_list *sorted_stack, int stack_size)
{
	int		i;

	psda->nb_chunks = (int)(SLOPE * (double)stack_size + INTERCEPT);
	psda->chunks = (int *)ft_memalloc(psda->nb_chunks * sizeof(int));
	i = -1;
	while (sorted_stack && ++i < psda->nb_chunks)
	{
		sorted_stack = ft_lst_at(sorted_stack,
			get_chunk_size(i, psda->nb_chunks, stack_size) - 1);
		psda->chunks[i] = *(int *)sorted_stack->content;
		sorted_stack = sorted_stack->next;
	}
}

static t_list	*get_chunk_values(t_psdata *psda, int chunk)
{
	t_list	*ptr;
	t_list	*val;

	val = NULL;
	ptr = psda->stack_a;
	while (ptr && *(int *)ptr->content > psda->chunks[chunk])
		ptr = ptr->next;
	val = ptr;
	if ((ptr = ft_lst_last(ptr)))
		val = *(int *)ptr->content < *(int *)val->content ? ptr : val;
	return (val);
}

void			sort_chunks(t_psdata *psda)
{
	t_list	*to_move;
	int		i;

	init_chunks(psda, psda->sorted_stack, psda->size);
	i = 0;
	while (psda->size_a)
	{
		if (!(to_move = get_chunk_values(psda, i)) && ++i)
			continue ;
		get_elem_on_top(psda, to_move, psda->stack_a);
		if (psda->stack_b)
			get_elem_on_top(psda, find_max(psda->stack_b), psda->stack_b);
		repeat_instruction(psda, inst_push, 1, g_instructions[4]);
	}
	while (psda->size_b)
	{
		get_elem_on_top(psda, find_max(psda->stack_b), psda->stack_b);
		repeat_instruction(psda, inst_push, 1, g_instructions[3]);
	}
}
