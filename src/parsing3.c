/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:45:02 by agoodwin          #+#    #+#             */
/*   Updated: 2020/10/15 18:12:17 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		count_cameras(char **lines)
{
	int count;

	count = 0;
	while (*lines)
	{
		if ((*lines)[0] == 'c' && ft_indexof((*lines)[1], " \t") > -1)
			count++;
		lines++;
	}
	if (count == 0)
		clean_exit(1, "No cameras found in the scene.");
	return (count);
}

int		count_lights(char **lines)
{
	int count;

	count = 0;
	while (*lines)
	{
		if ((*lines)[0] == 'l' && ft_indexof((*lines)[1], " \t") > -1)
			count++;
		lines++;
	}
	return (count);
}
