/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:16:19 by agoodwin          #+#    #+#             */
/*   Updated: 2019/11/10 19:14:54 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	register size_t			len;
	register unsigned char	*data;
	register unsigned char	ch;

	ch = (unsigned char)c;
	data = (unsigned char *)s;
	len = n;
	while (len--)
		*data++ = ch;
	return (s);
}
