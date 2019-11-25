/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:37:50 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/25 15:10:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_to_stack.h"
#include "check_instructions.h"
#define OPT_COUNT	1
#define O_VERBOSE	0x01
#define OPT_STRING	"v"

t_opt	g_options[OPT_COUNT + 1] = {
		{"verbose", 0, NULL, 'v'},
		{NULL, 0, NULL, 0}
};

static void	set_opt(int c, int *options, t_optdata *oda)
{
	(void)oda;
	if (c == 'v')
		*options |= O_VERBOSE;
	else if (c == '?')
		ft_exit(NULL, 1);
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
		oda.order = PERMUTE;
		while ((c = ft_getopt_long(argc, argv, &oda)) != -1)
			set_opt(c, &options, &oda);
		argv = argv + oda.first_nonopt;
		while (*argv && !add_to_stack(&stack, *argv++))
			;
		if (*argv || check_instructions(&stack))
			ft_exit("Error", 1);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
