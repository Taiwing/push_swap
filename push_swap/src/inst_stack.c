/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:14 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 21:42:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "instructions.h"

void	print_inst_stack(t_list *inst)
{
	while (inst)
	{
		ft_printf("%s\n", (char *)inst->content);
		inst = inst->next;
	}
}

static void		replace_superfluous_inst(t_list *start, int c_a, int c_b)
{
	t_list	*prev;
	int		replace;
	void	*new_inst;

	replace = c_a > c_b ? c_b : c_a;
	new_inst = start->content == (void *)g_instructions[5]
		|| start->content == (void *)g_instructions[6] ?
		(void *)g_instructions[7] : (void *)g_instructions[10];
	while (c_a-- > replace)
		start = start->next;
	c_a = replace;
	while (c_a--)
	{
		start->content = new_inst;
		prev = start;
		start = start->next;
	}
	while (replace--)
	{
		start = ft_lst_pop(&prev, 1);
		ft_memdel((void **)&start);
	}
}

static t_list	*count_elem(t_list *lst, void *elem, int *size)
{
	*size = 0;
	while (lst && lst->content == elem)
	{
		++(*size);
		lst = lst->next;
	}
	return (lst);
}

static void	optimize_couple_of_inst(t_list **inst, void *inst_a, void *inst_b)
{
	t_list	*start;
	t_list	*ptr;
	int		c_a;
	int		c_b;

	ptr = *inst;
	while (ptr)
	{
		start = NULL;
		if ((start = ptr->content == inst_a ? ptr : NULL)
			&& (ptr = count_elem(ptr, inst_a, &c_a))
			&& ptr->content == inst_b)
		{
			ptr = count_elem(ptr, inst_b, &c_b);
			replace_superfluous_inst(start, c_a, c_b);
		}
		if (ptr)
			ptr = ptr->next;
	}
}

void		optimize_inst_stack(t_list **inst)
{
	optimize_couple_of_inst(inst, (void *)g_instructions[5],
		(void *)g_instructions[6]);
	optimize_couple_of_inst(inst, (void *)g_instructions[6],
		(void *)g_instructions[5]);
	optimize_couple_of_inst(inst, (void *)g_instructions[8],
		(void *)g_instructions[9]);
	optimize_couple_of_inst(inst, (void *)g_instructions[9],
		(void *)g_instructions[8]);
}
