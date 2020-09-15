/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:17:32 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/10 17:25:50 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char *dup;

	if ((dup = (char*)malloc((ft_strlen(s) + 1) * sizeof(*dup))) == NULL)
		return (NULL);
	ft_memmove(dup, s, ft_strlen(s) + 1);
	return (dup);
}
