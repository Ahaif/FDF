/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaifoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:54:01 by ahaifoul          #+#    #+#             */
/*   Updated: 2022/01/01 16:47:53 by ahaifoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_movement(int keycode, t_fdf **matrix)
{
	if (keycode == 123)
		matrix[0][0].move_x -= 50;
	if (keycode == 126)
		matrix[0][0].move_y -= 50;
	if (keycode == 124)
		matrix[0][0].move_x += 50;
	if (keycode == 125)
		matrix[0][0].move_y += 50;
	if (keycode == 69)
		matrix[0][0].zoom += 1;
	if (keycode == 78)
		matrix[0][0].zoom -= 1;
}

int	handle_key(int keycode, t_fdf **matrix)
{
	int	i;

	i = 0;
	mlx_clear_window(matrix[0][0].mlx, matrix[0][0].win);
	handle_movement(keycode, matrix);
	if (keycode == 49)
	{
		if (matrix[0][0].is_iso == 1)
			matrix[0][0].is_iso = 0;
		else
			matrix[0][0].is_iso = 1;
	}
	if (keycode == 0)
		matrix[0][0].angle = matrix[0][0].angle - 0.10;
	if (keycode == 11)
		matrix[0][0].angle = matrix[0][0].angle + 0.10;
	handle_matrix(matrix);
	if (keycode == 53)
		free_everything(matrix);
	return (1);
}

void	set_param(t_fdf *a, t_fdf *b, t_fdf *param)
{
	a->x = a->x * param->zoom;
	a->y = a->y * param->zoom;
	b->x = b->x * param->zoom;
	b->y = b->y * param->zoom;
	if (param->is_iso == 1)
	{
		isometric(a, param->angle);
		isometric(b, param->angle);
	}
	a->x = a->x + param->move_x;
	a->y = a->y + param->move_y;
	b->x = b->x + param->move_x;
	b->y = b->y + param->move_y;
}

float	ft_abs(float dx, float dy)
{
	float	max;

	if (dx > dy)
		max = dx;
	else
		max = dy;
	return (max);
}

float	fmodule(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
