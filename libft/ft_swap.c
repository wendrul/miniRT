/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 23:14:57 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 22:38:49 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *data1, void *data2, size_t datasize)
{
	unsigned char *s1;
	unsigned char *s2;

	s1 = (unsigned char*)data1;
	s2 = (unsigned char*)data2;
	while (datasize--)
	{
		*s1 = *s1 ^ *s2;
		*s2 = *s1 ^ *s2;
		*s1 = *s1 ^ *s2;
	}
}
