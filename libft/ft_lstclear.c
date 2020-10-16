/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 07:32:09 by agoodwin          #+#    #+#             */
/*   Updated: 2019/11/11 21:24:47 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *cur;
	t_list *last;

	if (lst == NULL || del == NULL)
		return ;
	if (!*lst)
		return ;
	cur = *lst;
	while (cur)
	{
		last = cur;
		cur = cur->next;
		ft_lstdelone(last, del);
	}
	*lst = NULL;
}
