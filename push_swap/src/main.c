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

	if (argc > 1)
	{
		ft_bzero((void *)&psda, sizeof(t_psdata));
		while (*++argv && !add_to_stack(&psda, *argv))
			++psda.size;
		if (*argv)
			ft_exit("Error", 1);
		psda.size_a = psda.size;
		sort_stack(&psda);
	}
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
