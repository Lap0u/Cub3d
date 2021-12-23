/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:28:31 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/09/22 11:47:02 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*start;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	start = *alst;
	while (start->next)
		start = start->next;
	start->next = new;
}
