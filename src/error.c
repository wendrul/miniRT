/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:35 by ede-thom          #+#    #+#             */
/*   Updated: 2019/12/08 15:22:53 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

void    clean_exit(int status, char *str)
{
    if (status != 0)
        ft_putstr_fd("Error\n", 1);
    ft_putstr_fd("Exiting program...\nstatus = ", 1);
    ft_putnbr_fd(status, 1);
    ft_putstr_fd(": ", 1); 
    if  (str)
        ft_putstr_fd(str, 1);
    else
        ft_putstr_fd("(null)", 1);
    ft_putchar_fd('\n', 1);
    exit(status);
}