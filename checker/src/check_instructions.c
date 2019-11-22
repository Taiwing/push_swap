/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:35:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 14:47:48 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"
#include <limits.h>

static int	is_sorted(t_list *stack)
{
	int	last;
	int	cur;

	last = INT_MIN;
	while (stack)
	{
		cur = *(int *)stack->content;
		if (cur >= last)
			last = cur;
		else
			break ;
		stack = stack->next;
	}
	return (!stack);
}

static void	(*parse_instruction(char *str))(t_list **, t_list **, char)
{
	void	(*instruction)(t_list **, t_list **, char);

	instruction = NULL;
	if (ft_strlen(str) < 4)
	{
		if (str[0] == 's' && str[1] && ft_strchr("abs", str[1]) && !str[2])
			instruction = inst_swap;
		else if (str[0] == 'p' && str[1] && ft_strchr("ab", str[1]) && !str[2])
			instruction = inst_push;
		else if (str[0] == 'r' && str[1] && ft_strchr("abr", str[1]) && !str[2])
			instruction = inst_rotate;
		else if (!ft_strncmp(str, "rr", 2)
			&& ft_strchr("abr", str[2]) && !str[3])
			instruction = inst_reverse_rotate;
	}
	return (instruction);
}

int			check_instructions(t_list **stack_a)
{
	char	*line;
	t_list	*stack_b;
	void	(*f_inst)(t_list **, t_list **, char);

	stack_b = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!(f_inst = parse_instruction(line)))
			break ;
		f_inst(stack_a, &stack_b, line[ft_strlen(line) - 1]);
		if (!stack_b && is_sorted(*stack_a))
			return (0);
	}
	return (1);
}
