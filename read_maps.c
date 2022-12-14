/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 09:50:19 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/03 15:03:40 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_pow(int nb, int power)
{
	int	ret;

	if (power == 0)
		ret = 1;
	else if (power < 0)
		ret = 0;
	else
		ret = nb;
	while (power > 1)
	{
		ret = ret * nb;
		power--;
	}
	return (ret);
}

int	hexadecimal_to_decimal(char *hex)
{
	int	p;
	int	decimal;
	int	r;
	int	i;

	p = 0;
	decimal = 0;
	i = ft_strlen(hex) - 1;
	while (i >= 2)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			r = hex[i] - '0';
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			r = hex[i] - 'A' + 10;
		else
			r = hex[i] - 'a' + 10;
		decimal = decimal + r * ft_pow(16, p);
		++p;
		i--;
	}
	return (decimal);
}

void	fill_the_matrix(char *line, t_fdf **matrix, int y)
{
	char	**m;
	int		x;

	m = ft_split(line, ' ');
	x = 0;
	while (m[x])
	{
		if (ft_strchr(m[x], ','))
		{	
			matrix[y][x].color = hexadecimal_to_decimal(ft_strchr(m[x], ','));
		}
		else
			matrix[y][x].color = 0xFFFFFF;
		matrix[y][x].x = x;
		matrix[y][x].y = y;
		matrix[y][x].z = ft_atoi(m[x]);
		matrix[y][x].is_last = 0;
		free(m[x++]);
	}
	free(m);
	matrix[y][--x].is_last = 1;
}

t_fdf	**allocate_things(char *file)
{
	t_fdf	**matrix;
	int		width;
	int		height;
	int		fd;
	int		i;

	i = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handle(1);
	width = get_width(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	height = get_height(fd);
	matrix = malloc(sizeof(t_fdf *) * (height + 1));
	while (++i < height)
		matrix[i] = malloc(sizeof(t_fdf) * (width + 1));
	close(fd);
	return (matrix);
}

t_fdf	**read_maps(char *file)
{
	t_fdf	**matrix;
	int		y;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handle(1);
	if (get_next_line(fd) == NULL)
		return ((matrix = NULL));
	matrix = allocate_things(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handle(1);
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		fill_the_matrix(line, matrix, y++);
		free (line);
	}
	matrix[y] = 0;
	return (matrix);
}
