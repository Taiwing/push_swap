/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:35:38 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/25 18:40:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instructions.h"
#include "checker_options.h"
#include <limits.h>
#define MAX_SPACE	"           "
#define MAX_UNDER	"___________"

static int	get_field_width(t_list *stack_a)
{
	int	i;
	int	big;
	int	small;

	big = 0;
	small = 0;
	while (stack_a)
	{
		if ((i = *(int *)stack_a->content) > big)
			big = i;
		else if (i < small)
			small = i;
		stack_a = stack_a->next;
	}
	small = small ? ft_intlen(small) + 1 : 1;
	big = big ? ft_intlen(big) : 1;
	return (small > big ? small : big);
}

static void	print_instruction(t_list *stack_a, t_list *stack_b,
				char *inst, int fw)
{
	if (inst)
		ft_printf("Exec %s:\n", inst);
	else
		ft_printf("_______________________\nInit a and b:\n");
	while (stack_a || stack_b)
	{
		if (stack_a && stack_b)
			ft_printf("%-*d %*d\n", fw, *(int *)stack_a->content,
				fw, *(int *)stack_b->content);
		else if (stack_a)
			ft_printf("%-*d %.*s\n", fw, *(int *)stack_a->content,
				fw, MAX_SPACE);
		else if (stack_b)
			ft_printf("%.*s %*d\n", fw, MAX_SPACE,
				fw, *(int *)stack_b->content);
		if (stack_a)
			stack_a = stack_a->next;
		if (stack_b)
			stack_b = stack_b->next;
	}
	ft_printf("%.*s %.*s\n", fw, MAX_UNDER, fw, MAX_UNDER);
	ft_printf("%-*s %*s\n", fw, "a", fw, "b");
	ft_printf("_______________________\n");
}

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

int			check_instructions(t_list **stack_a, int options)
{
	int		fw;
	char	*line;
	t_list	*stack_b;
	void	(*f_inst)(t_list **, t_list **, char);

	stack_b = NULL;
	fw = get_field_width(*stack_a);
	if (options & O_VERBOSE)
		print_instruction(*stack_a, stack_b, NULL, fw);
	while (get_next_line(0, &line) > 0)
	{
		if (!(f_inst = parse_instruction(line)))
			return (1);
		f_inst(stack_a, &stack_b, line[ft_strlen(line) - 1]);
		if (options & O_VERBOSE)
			print_instruction(*stack_a, stack_b, line, fw);
	}
	if (!stack_b && is_sorted(*stack_a))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	return (0);
}
