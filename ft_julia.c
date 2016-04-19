/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/19 10:30:54 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_draw(t_data *ptr, float x, float y)
{
	int nb;

	nb = (x * ptr->bits) / 8 + (y * ptr->len);
	ptr->data_adrr[nb] = ptr->red;
	ptr->data_adrr[nb + 1] = ptr->green;
	ptr->data_adrr[nb + 2] = ptr->blue;
}

double	ft_module(double x, double y, float cx, float cy)
{
	double nb;

	nb = ((x * x) - (y * y) + cx) * ((x * x) - (y * y) + cx)
		+ ((2 * x * y + cy) * (2 * x * y + cy));
	return (nb);
}

double	ft_set_suit(t_data *ptr, int lim)
{
	int		n;
	double	tmpx;
	double	retx;
	double	rety;

	n = 0;
	retx = ptr->x;
	rety = ptr->y;
	while (n < lim)
	{
		tmpx = retx;
		retx = (retx * retx) - (rety * rety) + ptr->cx;
		rety = (2 * tmpx * rety + ptr->cy);
		n++;
	}
	return (hypot((retx * retx) - (rety * rety) + ptr->cx
				, 2 * retx * rety + ptr->cy));
}

void	ft_cpy2(t_data *ptr, double x, double y)
{
	ptr->x = x;
	ptr->y = y;
	ptr->green = 200;
}

void	ft_julia_fract(t_data *ptr)
{
	double x;
	double y;
	double mod;

	x = -2;
	while (ptr->gx + (x * ptr->sc) < 0)
		x += (1 / ptr->sc);
	while (ptr->gx + (x * ptr->sc) < 499 && ptr->gx + (x * ptr->sc) >= 0)
	{
		y = -2;
		while (ptr->gy + (y * ptr->sc) < 0)
			y += (1 / ptr->sc);
		while (ptr->gy + (y * ptr->sc) < 499 && ptr->gy + (y * ptr->sc) >= 0)
		{
			ft_cpy2(ptr, x, y);
			mod = ft_set_suit(ptr, ptr->n);
			if (mod <= 4)
			{
				ptr->green -= mod * 300;
				ft_draw(ptr, ptr->gx + (x * ptr->sc), ptr->gy + (y * ptr->sc));
			}
			y = y + (1 / ptr->sc);
		}
		x = x + (1 / ptr->sc);
	}
}
