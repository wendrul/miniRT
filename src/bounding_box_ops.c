/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:27:14 by dhorvill          #+#    #+#             */
/*   Updated: 2019/11/16 21:02:57 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_ulf(t_box box, t_point ulf, t_point drc, t_point ray)
{
	if (ray.x < ulf.x || ray.y > ulf.y || ray.z > ulf.z)
	{
		box.to_check = 0;
		return (0);
	}
	if (ray.x > drc.x || ray.y < drc.y || ray.z < drc.z)
		return (0);
	return (1);
}

int	is_in_urf(t_box box, t_point urf, t_point dlc, t_point ray)
{
	if (ray.x > urf.x || ray.y > urf.y || ray.z > urf.z)
	{
		box.to_check = 0;
		return (0);
	}
	if (ray.x < dlc.x || ray.y < dlc.y || ray.z < dlc.z)
		return (0);
	return (1);
}

int	is_in_dlf(t_box box, t_point dlf, t_point urc, t_point ray)
{
	if (ray.x < dlf.x || ray.y < dlf.y || ray.z > dlf.z)
	{
		box.to_check = 0;
		return (0);
	}
	if (ray.x > urc.x || ray.y > urc.y || ray.z < urc.z)
		return (0);
	return (1);
}

int	is_in_drf(t_box box, t_point drf, t_point ulc, t_point ray)
{
	if (ray.x > drf.x || ray.y < drf.y || ray.z > drf.z)
	{
		box.to_check = 0;
		return (0);
	}
	if (ray.x < ulc.x || ray.y > ulc.y || ray.z < ulc.z)
		return (0);
	return (1);
}
