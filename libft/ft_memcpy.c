/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:16:06 by agoodwin          #+#    #+#             */
/*   Updated: 2019/11/10 19:13:57 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (char*)dest;
	s = (char*)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
