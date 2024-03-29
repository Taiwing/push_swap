/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_psdata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:09 by yforeau           #+#    #+#             */
/*   Updated: 2019/11/29 16:24:38 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PSDATA_H
# define T_PSDATA_H
# include "libft.h"

typedef struct	s_psdata
{
	t_list		*stack_a;
	int			size_a;
	t_list		*stack_b;
	int			size_b;
	t_list		*sorted_stack;
	int			size;
	t_list		*inst;
	int			*chunks;
	int			nb_chunks;
}				t_psdata;

#endif
