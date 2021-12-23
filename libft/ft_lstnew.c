/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:29:24 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:43:44 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newt;

	newt = malloc(sizeof(t_list));
	if (newt == NULL)
		return (NULL);
	newt->content = content;
	newt->next = NULL;
	return (newt);
}
