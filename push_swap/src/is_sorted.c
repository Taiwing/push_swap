/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:49:08 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/26 18:39:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	is_sorted(t_list *stack)
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
