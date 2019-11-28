#include "libft.h"

void	print_inst_stack(t_list *inst)
{
	while (inst)
	{
		ft_printf("%s\n", (char *)inst->content);
		inst = inst->next;
	}
}
