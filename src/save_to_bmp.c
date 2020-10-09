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

void	write_img(t_scene scene, int cam_no, int fd)
{
	int filesize;
	int w;
	int h;

	w = (int)scene.resolution.x;
	h = (int)scene.resolution.y;
	filesize = 54 + w*h;
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};
	unsigned char *img;


	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	int i = -1;
	t_color color;
	if (!(img = (unsigned char*)malloc(sizeof(unsigned char) * 3 * w * h)))
		clean_exit(1, "Malloc stop");
	while (++i < w*h)
	{
		color = int_to_rgb(scene.camera_list[cam_no].buf[i]);
		img[3 * i]     = (unsigned char)color.blue;
		img[3 * i + 1] = (unsigned char)color.green;
		img[3 * i + 2] = (unsigned char)color.red;
	}
	write(fd, bmpfileheader, 14);
	write(fd, bmpinfoheader, 40);
	i = -1;
	while (++i < h)
	{
    	write(fd, img + (w*(h-i-1)*3), 3 * w);
    	write(fd, bmppad, (4-(w*3)%4)%4);
	}
	free(img);
	write(fd, scene.camera_list[cam_no].buf, w*h);
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
		if ((fd = open(tmp, O_RDWR | O_CREAT, S_IRWXU)) == -1)
			clean_exit(1, "Failed to generate file");
		write_img(scene, cam_no, fd);
		close(fd);
		free(tmp);
		cam_no++;
	}	
	return (0);
}
