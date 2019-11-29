/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:14 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 14:24:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_inst_stack(t_list *inst)
{
	while (inst)
	{
		ft_printf("%s\n", (char *)inst->content);
		inst = inst->next;
	}
}
