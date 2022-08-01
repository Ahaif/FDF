/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:51:08 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/01 16:51:30 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handle(int flag)
{
	if (flag == 1)
		write(1, "File Name Does Not Exist !!", 28);
	exit(-1);
}

void	free_everything(t_fdf **matrix)
{
	int	i;

	i = 0;
	mlx_clear_window(matrix[0][0].mlx, matrix[0][0].win);
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	exit (-1);
}

void	isometric(t_fdf *dot, double angle)
{
	dot->x = (dot->x - dot->y) * cos(angle);
	if (dot->z <= 10)
		dot->y = (dot->x + dot->y) * sin(angle) - dot->z * 10;
	else
		dot->y = (dot->x + dot->y) * sin(angle) - dot->z * 2;
}

int	get_width(int fd)
{
	int		i;
	int		count;
	char	*s;

	s = get_next_line(fd);
	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && i == 0)
			|| ((s[i] != ' ' && s[i] != '\n') && (s[i - 1] == ' ')))
			count++;
		i++;
	}
	free (s);
	return (count);
}

int	get_height(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free (line);
		line = get_next_line(fd);
	}
	free (line);
	return (count);
}
