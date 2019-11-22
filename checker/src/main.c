/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:37:50 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 14:37:15 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_to_stack.h"
#include "check_instructions.h"

int			main(int argc, char **argv)
{
	t_list	*stack;

	if (argc > 1)
	{
		stack = NULL;
		while (*++argv && !add_to_stack(&stack, *argv))
			;
		if (*argv || check_instructions(&stack))
			ft_exit("Error", 1);
	}
	return (0);
}
