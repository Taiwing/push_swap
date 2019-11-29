/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comb_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:20:06 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 14:06:31 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

static int	is_unique(int *comb, int i, int val)
{
	while (i-- > 0)
	{
		if (comb[i] == val)
			return (0);
	}
	return (1);
}

static void	generate_comb(int *arr, int n, int i)
{
	static int	*comb = NULL;
	int			j;

	comb = !comb ? ft_memalloc(n * sizeof(int)) : comb;
	if (i == n)
		ft_printf("%#*t%d \n", n, comb);
	else
	{
		j = -1;
		while (++j < n)
		{
			if (is_unique(comb, i, arr[j]))
			{
				comb[i] = arr[j];
				generate_comb(arr, n, i + 1);
			}
		}
	}
	if (!i)
		ft_memdel((void **)&comb);
}

static void	fill_array(int *arr, int n)
{
	while (n-- > 0)
		arr[n] = n + 1;
}

int			main(int argc, char **argv)
{
	int	n;
	int	*arr;

	if (argc < 2 || !(n = ft_atoi(argv[1])))
	{
		ft_dprintf(2, "usage: %s size\n", argv[0]);
		return (1);
	}
	arr = (int *)ft_memalloc(n * sizeof(int));
	fill_array(arr, n);
	generate_comb(arr, n, 0);
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
