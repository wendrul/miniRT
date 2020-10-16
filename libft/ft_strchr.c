/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:30:22 by agoodwin          #+#    #+#             */
/*   Updated: 2019/11/10 19:15:11 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *str;

	str = (char*)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}
