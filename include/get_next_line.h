/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:15:17 by ede-thom          #+#    #+#             */
/*   Updated: 2019/11/23 22:19:21 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>

typedef	struct			s_buf_hist
{
	int					fd;
	char				buf[BUFFER_SIZE + 1];
	struct s_buf_hist	*next;
}					*	t_buf_hist;

int						ft_strjoin_endl(char **line, char *s2, int *error_no);
void					*ft_memmove(void *dest, const void *src, size_t n);
char					*get_last_from_fd(int fd, t_buf_hist *hist);
t_buf_hist				remove_fd_from_hist(int fd, t_buf_hist element);
int						get_next_line(int fd, char **line);

#endif
