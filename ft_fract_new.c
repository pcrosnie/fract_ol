/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fract_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 11:44:49 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/19 13:08:23 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		motion_notify2(int x, int y, t_data *ptr)
{
	x = y;
	if (ptr->param == 0)
	{
		ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
		free(ptr->data_adrr);
		ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
				, &(ptr->len), &(ptr->endian));
		ft_set_color(ptr);
		ft_mandelbrot_fract(ptr);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	}
	return (0);
}

double	ft_set_newton_suit(double x, double y, int lim)
{
	int		n;
	double	tmpx;
	double	retx;
	double	rety;

	n = 0;
	retx = x;
	rety = y;
	while (n < lim)
	{
		tmpx = retx;
		retx = (retx * retx * retx) - (rety * rety * retx)
			- (2 * retx * rety * rety) + 1;
		rety = (3 * tmpx * tmpx * rety) - (rety * rety * rety);
		n++;
	}
	return (hypot(retx, rety));
}

void	ft_set_num(t_data *ptr, double x, double y, int n)
{
	double	mod;

	ptr->green = 200;
	mod = ft_set_newton_suit(x, y, n);
	if (mod <= 1)
	{
		ptr->green -= mod * 300;
		ft_draw(ptr, ptr->gx + (x * ptr->sc), ptr->gy + (y * ptr->sc));
	}
}

void	ft_reset3(t_data *ptr)
{
	ptr->tmp_scale = 100;
	ptr->sc = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 4;
	ptr->gx = 250;
	ptr->gy = 250;
	ptr->exp = 0;
	ptr->param = 0;
}
