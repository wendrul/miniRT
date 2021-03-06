/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoodwin <agoodwin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:35 by agoodwin          #+#    #+#             */
/*   Updated: 2019/12/08 15:22:53 by agoodwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

void	clean_exit(int status, char *str)
{
	if (status != 0)
		ft_putstr_fd("Error\n", 1);
	if (str)
		ft_putstr_fd(str, 1);
	ft_putstr_fd("\nExiting program...\n", 1);
	ft_putchar_fd('\n', 1);
	exit(status);
}
