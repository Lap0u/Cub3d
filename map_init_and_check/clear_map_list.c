#include "../cub3d.h"
#include "../libft/libft.h"

void	ft_lstdelone(t_map *lst)
{
	if (lst == (void *)0)
		return ;
	free(lst->line);
	free(lst);
}

void	ft_lstclear(t_map **lst)
{
	t_map	*tmp_c;
	t_map	*tmp_n;

	tmp_c = *lst;
	while (tmp_c != (void *)0)
	{
		tmp_n = tmp_c->next;
		ft_lstdelone(tmp_c);
		tmp_c = tmp_n;
	}
	*lst = (void *)0;
}
