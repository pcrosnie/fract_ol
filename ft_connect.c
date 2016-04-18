/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:12:36 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/11 13:44:23 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_draw_line3(float *x, float *y, t_data *ptr)
{
	float i;
	float j;
	float coeff_dir;
	float tmp;

	coeff_dir = (x[1] - x[0]) / (y[1] - y[0]);
	j = -1;
	i = 1;
	while (x[0] + j > x[1] || y[0] + i < y[1])
	{
		tmp = j / i;
		if (tmp >= coeff_dir)
			ft_draw(ptr, x[0] + j--, y[0] + i);
		else
			ft_draw(ptr, x[0] + j, y[0] + i++);
	}
}

void	ft_draw_line2(float *x, float *y, t_data *ptr)
{
	float i;
	float j;
	float coeff_dir;
	float tmp;

	j = -1;
	i = 1;
	coeff_dir = (x[1] - x[0]) / (y[1] - y[0]);
	while (x[1] + j > x[0] || y[1] + i < y[0])
	{
		tmp = j / i;
		if (tmp >= coeff_dir)
			ft_draw(ptr, x[1] + j--, y[1] + i);
		else
			ft_draw(ptr, x[1] + j, y[1] + i++);
	}
}

void	ft_draw_line1(float *x, float *y, t_data *ptr)
{
	float i;
	float j;
	float coeff_dir;
	float tmp;

	i = 1;
	j = 1;
	coeff_dir = (x[1] - x[0]) / (y[1] - y[0]);
	while (x[0] + j < x[1] || y[0] + i < y[1])
	{
		tmp = j / i;
		if (tmp >= coeff_dir)
			ft_draw(ptr, x[0] + j, y[0] + i++);
		else
			ft_draw(ptr, x[0] + j++, y[0] + i);
	}
}

void	ft_draw_line4(float *x, float *y, t_data *ptr)
{
	float i;
	float j;
	float coeff_dir;
	float tmp;

	i = 1;
	j = 1;
	coeff_dir = (x[1] - x[0]) / (y[1] - y[0]);
	while (x[1] + j < x[0] || y[1] + i < y[0])
	{
		tmp = j / i;
		if (tmp >= coeff_dir)
			ft_draw(ptr, x[1] + j, y[1] + i++);
		else
			ft_draw(ptr, x[1] + j++, y[1] + i);
	}
}

void	ft_connect(float *x, float *y, t_data *ptr)
{
	int i;

	i = 0;
	if (y[1] - y[0] != 0)
		ptr->coeff_dir = (x[1] - x[0]) / (y[1] - y[0]);
	if (ptr->coeff_dir == 0 && x[1] > x[0])
		while (i < x[1] - x[0])
			ft_draw(ptr, x[0] + i++, y[0]);
	else if (ptr->coeff_dir == 0 && x[1] < x[0])
		while (i < x[0] - x[1])
			ft_draw(ptr, x[1] + i++, y[1]);
	else if (ptr->coeff_dir < 0)
	{
		if (x[1] - x[0] < 0)
			ft_draw_line3(x, y, ptr);
		else
			ft_draw_line2(x, y, ptr);
	}
	else
	{
		if (x[1] - x[0] < 0 && y[1] - y[0] < 0)
			ft_draw_line4(x, y, ptr);
		else
			ft_draw_line1(x, y, ptr);
	}
}
