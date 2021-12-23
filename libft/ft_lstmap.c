/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:29:20 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:44:30 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*newl;
	t_list	*newe;
	t_list	*temp;

	newl = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst && f)
	{
		temp = f(lst->content);
		newe = ft_lstnew(temp);
		if (newe == NULL)
			free(temp);
		if (newe == NULL)
		{
			ft_lstclear(&newl, del);
			return (NULL);
		}
		ft_lstadd_back(&newl, newe);
		lst = lst->next;
	}
	return (newl);
}
