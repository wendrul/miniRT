/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:11:29 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/11 17:14:04 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		word_count(char *str, char *charset)
{
	int n;
	int i;

	n = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_indexof(str[i], charset) == -1)
		{
			while (ft_indexof(str[i], charset) == -1 && str[i])
			{
				i++;
			}
			n++;
			if (!str[i])
				return (n);
		}
	}
	return (n);
}

static int		word_length(char *start, char *charset)
{
	int i;

	i = 0;
	while (start[i] && ft_indexof(start[i], charset) == -1)
		i++;
	return (i);
}

static char		**init(int *word, int *i, char *s, char *cs)
{
	char **splut;

	if (s == NULL || cs == NULL)
		return ((char**)NULL);
	*word = -1;
	*i = 0;
	if (!(splut = (char**)malloc(sizeof(char*) * (word_count(s, cs) + 1))))
		return (0);
	return (splut);
}

char			**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		word;
	int		len;
	char	**splut;
	int		j;

	if (!(splut = init(&word, &i, str, charset)))
		return (NULL);
	while (++word < word_count(str, charset))
	{
		while (ft_indexof(str[i], charset) != -1)
			i++;
		len = word_length(&str[i], charset);
		if ((j = -1) && len >= 0)
		{
			if (!(splut[word] = (char*)malloc(sizeof(char) * (len + 1))))
				return (NULL);
			while (++j < len)
				splut[word][j] = str[i + j];
			splut[word][j] = '\0';
		}
		i += len;
	}
	splut[word_count(str, charset)] = 0;
	return (splut);
}
