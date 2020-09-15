/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:21:44 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/14 18:06:47 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (s == NULL)
		return ((char*)NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	size = ft_min(len, ft_strlen(s) - start);
	if ((str = (char*)malloc((len + 1) * sizeof(*str))) == NULL)
		return (NULL);
	ft_memcpy(str, &s[start], size + 1);
	str[size] = '\0';
	return (str);
}
