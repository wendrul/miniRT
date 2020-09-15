/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:57:40 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 22:02:10 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_set(char const *str, char const *set)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (ft_indexof(str[++i], set) != -1)
		count++;
	i = -1;
	if (count < (int)ft_strlen(str))
		while (ft_indexof(str[ft_strlen(str) - 1 - ++i], set) != -1)
			count++;
	return (count);
}

char		*ft_strtrim(char const *str, char const *set)
{
	char	*ret;
	int		i;
	int		start;
	int		end;

	if (str == NULL)
		return ((char*)NULL);
	if ((ret = (char*)malloc((ft_strlen(str)
		- count_set(str, set) + 1) * sizeof(*str))) == NULL)
		return (NULL);
	start = 0;
	while (ft_indexof(str[start], set) != -1)
		start++;
	end = ft_strlen(str) - 1;
	while (end >= 0 && ft_indexof(str[end], set) != -1)
		end--;
	i = 0;
	while (i <= end - start)
	{
		ret[i] = str[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
