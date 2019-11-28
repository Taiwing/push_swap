/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:15:05 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/27 16:19:41 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H
# include "t_psdata.h"

extern const char	*g_instructions[11];
void				inst_swap(t_psdata *psda, char arg);
void				inst_push(t_psdata *psda, char arg);
void				inst_rotate(t_psdata *psda, char arg);
void				inst_reverse_rotate(t_psdata *psda, char arg);
void				add_instruction(t_list **inst, const char *str);

#endif
