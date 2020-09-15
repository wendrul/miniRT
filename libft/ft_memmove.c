/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:16:16 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/06 13:12:44 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*desert;
	char	*sauce;

	desert = (char*)dest;
	sauce = (char*)src;
	if (desert > sauce)
	{
		while (n--)
			desert[n] = sauce[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
