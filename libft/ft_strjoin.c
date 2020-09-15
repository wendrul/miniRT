/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 19:16:06 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/10 19:17:28 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *ret;
	char *start;

	if (s1 == NULL || s2 == NULL)
		return ((char*)NULL);
	if (!(ret = (char*)malloc((ft_strlen(s1)
		+ ft_strlen(s2) + 1) * sizeof(*ret))))
		return (NULL);
	start = ret;
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = '\0';
	return (start);
}
