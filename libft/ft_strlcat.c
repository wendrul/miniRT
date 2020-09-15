/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:51:30 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/14 22:17:45 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char * restrict dst, const char * restrict src, size_t maxlen) 
{
	const size_t srclen = ft_strlen(src);
	const size_t dstlen = ft_min(ft_strlen(dst), maxlen);

	if (dstlen == maxlen) return maxlen + srclen;
	if (srclen < maxlen-dstlen) 
	{
		ft_memcpy(dst + dstlen, src, srclen + 1);
	} 
	else 
	{
		ft_memcpy(dst + dstlen, src, maxlen - 1);
		dst[dstlen + maxlen - 1] = '\0';
	}
	return (dstlen + srclen);
}

