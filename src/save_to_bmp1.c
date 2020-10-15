/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@42.edu.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:09:22 by ede-thom          #+#    #+#             */
/*   Updated: 2020/10/15 14:31:20 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	write_headers(unsigned char bmpfileheader[],
					unsigned char bmpinfoheader[], int w, int h)
{
	int filesize;

	filesize = w * h + 54;
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);
}

static void	write_data(t_poubelle p, unsigned char bmpfileheader[],
					unsigned char bmpinfoheader[], unsigned char bmppad[])
{
	int i;

	i = -1;
	if (!(p.img =
		(unsigned char*)malloc(sizeof(unsigned char) * 3 * p.w * p.h)))
		clean_exit(1, "Malloc failed");
	while (++i < p.w * p.h)
	{
		p.color = int_to_rgb(p.scene.camera_list[p.cam_no].buf[i]);
		p.img[3 * i] = (unsigned char)p.color.blue;
		p.img[3 * i + 1] = (unsigned char)p.color.green;
		p.img[3 * i + 2] = (unsigned char)p.color.red;
	}
	write(p.fd, bmpfileheader, 14);
	write(p.fd, bmpinfoheader, 40);
	i = -1;
	while (++i < p.h)
	{
		write(p.fd, p.img + (p.w * (p.h - i - 1) * 3), 3 * p.w);
		write(p.fd, bmppad, (4 - (p.w * 3) % 4) % 4);
	}
	free(p.img);
	write(p.fd, p.scene.camera_list[p.cam_no].buf, p.w * p.h);
}

void		write_img(t_scene scene, int cam_no, int fd)
{
	static unsigned char	bmpfileheader[14] = {'B',
						'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	static unsigned char	bmpinfoheader[40] = {40,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	static unsigned char	bmppad[3] = {0, 0, 0};
	t_poubelle				p;

	write_headers(bmpfileheader, bmpinfoheader,
			scene.resolution.x, scene.resolution.y);
	p.w = (int)scene.resolution.x;
	p.h = (int)scene.resolution.y;
	p.scene = scene;
	p.fd = fd;
	p.cam_no = cam_no;
	write_data(p, bmpfileheader, bmpinfoheader, bmppad);
}
