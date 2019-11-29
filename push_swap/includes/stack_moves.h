/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_moves.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:59 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 14:25:00 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_MOVES_H
# define STACK_MOVES_H
# include "t_psdata.h"

void	repeat_instruction(t_psdata *psda, void (*f)(t_psdata *psda, char arg),
			unsigned int n, char *cmd);

#endif
