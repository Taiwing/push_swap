/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_stack.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:47 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 19:34:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INST_STACK_H
# define INST_STACK_H
# include "libft.h"

void	print_inst_stack(t_list *inst);
void	optimize_inst_stack(t_list **inst);

#endif
