/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:37:50 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/26 18:09:32 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_to_stack.h"
#include "sort_stack.h"

int	main(int argc, char **argv)
{
	t_psdata	psda;
	char		**nb;
	char		**split;

	if (argc > 1)
	{
		ft_bzero((void *)&psda, sizeof(t_psdata));
		while (*++argv)
		{
			split = ft_split_whitespaces(*argv);
			nb = split;
			while (*nb && !add_to_stack(&psda, *nb++))
				++psda.size;
			ft_wtfree(split);
			if (*nb)
				break ;
		}
		if (*argv)
			ft_exit("Error", 1);
		psda.size_a = psda.size;
		sort_stack(&psda);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
