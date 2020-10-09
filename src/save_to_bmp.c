/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:29:35 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/08 18:44:04 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minirt.h"


char	*build_str_name(char *radical, int f_no, int cam_no)
{
	char	*ret;
	char	*tmp;
	int		cur;
	size_t	size;

	size = sizeof(char) * (10 + ft_strlen(radical) + (int)(log10(f_no * cam_no + 1) + 2));
	if (!(ret = (char*)malloc(size)))
		clean_exit(1, "Malloc failed lmao");
	ft_strlcpy(ret, radical, size);
	cur = ft_indexof('.', ret) > -1 ? ft_indexof('.', ret) : ft_strlen(ret);
	ret[cur] = '\0';

	ft_strlcpy(ret + cur, "_", size - cur);	
	cur = ft_strlen(ret);
	
	if (!(tmp = ft_itoa(f_no)))
		clean_exit(1, "Malloc failed lmao");
	ft_strlcpy(ret + cur, tmp, size - cur);	
	cur = ft_strlen(ret);
	free(tmp);

	ft_strlcpy(ret + cur, "_cam", size - cur);		
	cur = ft_strlen(ret);

	if (!(tmp = ft_itoa(cam_no)))
		clean_exit(1, "Malloc failed lmao");
	ft_strlcpy(ret + cur, tmp, size - cur);	
	cur = ft_strlen(ret);
	free(tmp);

	ft_strlcpy(ret + cur, ".bmp", size - cur);		
	cur = ft_strlen(ret);
	ret[cur] = '\0';
	return (ret);
}

int		find_suffix(t_scene scene)
{
	int		s;
	int		fd;
	char	*tmp;

	s = -1;
	while (++s < 500)
	{
		tmp = build_str_name(scene.scene_name, s, 0);
		if ((fd = open(tmp, O_RDONLY)) == -1)
		{
				free(tmp);
				return (s);
		}
		free(tmp);
		close(fd);
	}
	clean_exit(1, "Failed to find a name for the save file (500 tries)");
	return (-1);
}

int		save_to_bmp(t_scene scene)
{
	int suffix;
	int cam_no;
	int fd;
	char *tmp;

	suffix = find_suffix(scene);
	cam_no = 0;
	while (cam_no < scene.camera_count)
	{
		tmp = build_str_name(scene.scene_name, suffix, cam_no);
		if ((fd = open(tmp, O_CREAT, S_IRWXU)) == -1)
			clean_exit(1, "Failed to generate file");
		free(tmp);
		close(fd);
		cam_no++;
	}	
	return (0);
}
