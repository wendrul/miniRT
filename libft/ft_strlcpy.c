/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:30:06 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 02:56:22 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	n;

	if (src == NULL)
		return (0);
	srclen = ft_strlen(src);
	n = -1;
	if (dstsize == 0)
		return (srclen);
	if (dstsize > srclen)
	{
		while (src[++n])
			dest[n] = src[n];
		dest[n] = '\0';
	}
	else
	{
		while (++n < dstsize - 1 && dstsize > 0)
			dest[n] = src[n];
		dest[n] = '\0';
	}
	return (srclen);
}
