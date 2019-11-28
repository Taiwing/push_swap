/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_stack.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:34:12 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/26 18:10:09 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_TO_STACK_H
# define ADD_TO_STACK_H
# include "t_psdata.h"

int	int_cmp(void *ptr1, void *ptr2);
int	add_to_stack(t_psdata *psda, const char *nptr);

#endif
