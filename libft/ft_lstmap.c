/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:44:16 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/15 14:37:24 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*cur;
	t_list	*new;
	int		start_flag;

	if (!lst)
		return (NULL);
	start_flag = 1;
	cur = lst;
	while (cur)
	{
		if (!(new = (t_list*)malloc(sizeof(t_list))))
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		if (start_flag)
		{
			start = new;
			start_flag = 0;
		}
		else
			ft_lstadd_back(&start, new);
		new->content = (f)(cur->content);
		cur = cur->next;
	}
	return (start);
}
