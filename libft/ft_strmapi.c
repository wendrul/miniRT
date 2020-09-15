/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 03:16:32 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 17:14:39 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ret;

	if (s == NULL || f == NULL)
		return ((char*)NULL);
	if (!(ret = (char*)malloc((ft_strlen(s) + 1) * sizeof(*ret))))
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = (f)(i, s[i]);
	ret[i] = '\0';
	return (ret);
}
