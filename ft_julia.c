/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/18 16:44:42 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
