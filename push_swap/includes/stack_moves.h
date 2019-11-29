/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 17:26:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_MOVES_H
# define STACK_MOVES_H
# include "t_psdata.h"

void	repeat_instruction(t_psdata *psda, void (*f)(t_psdata *psda, char arg),
			unsigned int n, const char *cmd);
void	get_elem_on_top(t_psdata *psda, t_list *elem, t_list *stack);
t_list	*find_max(t_list *stack);
t_list	*find_min(t_list *stack);

#endif
