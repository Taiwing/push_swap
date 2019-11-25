/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:37:50 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/25 18:18:41 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_to_stack.h"
#include "check_instructions.h"
#include "checker_options.h"

t_opt	g_options[OPT_COUNT + 1] = {
		{"verbose", 0, NULL, 'v'},
		{NULL, 0, NULL, 0}
};

static void	set_opt(int c, int *options, t_optdata *oda)
{
	(void)oda;
	if (c == 'v')
		*options |= O_VERBOSE;
}

int			main(int argc, char **argv)
{
	int			c;
	t_optdata	oda;
	t_list		*stack;
	int			options;

	if (argc > 1)
	{
		options = 0;
		stack = NULL;
		init_getopt(&oda, OPT_STRING, g_options, 0);
		oda.opterr = 0;
		while ((c = ft_getopt_long(argc, argv, &oda)) != -1 && c != '?')
			set_opt(c, &options, &oda);
		argv = argv + oda.optind;
		while (*argv && !add_to_stack(&stack, *argv++))
			;
		if (*argv || check_instructions(&stack, options))
			ft_exit("Error", 1);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
