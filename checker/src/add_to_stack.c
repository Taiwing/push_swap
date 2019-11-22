/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:33:17 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 14:32:11 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	int_cmp(void *ptr1, void *ptr2)
{
	return (*(int *)ptr1 - *(int *)ptr2);
}

int			add_to_stack(t_list **stack, const char *nptr)
{
	int			reg_nb;
	int			sign;
	uintmax_t	nb;

	nb = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign = *nptr++ == '-' ? -1 : sign;
	while (*nptr > 47 && *nptr < 58)
	{
		if ((nb = (nb * 10) + ((*nptr++) - 48)) > (uintmax_t)INT_MAX + 1
			|| (sign == 1 && nb > (uintmax_t)INT_MAX))
			return (1);
	}
	if (*nptr)
		return (1);
	reg_nb = nb == (uintmax_t)INT_MAX + 1 ? INT_MIN : (int)nb * sign;
	if (ft_lst_find(*stack, &reg_nb, int_cmp))
		return (1);
	ft_lst_push_back(stack, &reg_nb, sizeof(int));
	return (0);
}
