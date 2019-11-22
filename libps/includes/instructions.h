/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:49:42 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/22 14:32:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H
# include "libft.h"

void	inst_swap(t_list **stack_a, t_list **stack_b, char arg);
void	inst_push(t_list **stack_a, t_list **stack_b, char arg);
void	inst_rotate(t_list **stack_a, t_list **stack_b, char arg);
void	inst_reverse_rotate(t_list **stack_a, t_list **stack_b, char arg);

#endif
