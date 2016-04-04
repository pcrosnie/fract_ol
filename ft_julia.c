/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/04 13:14:37 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_julia_fract(t_data *ptr)
{
	double x;
	double y;
	double mod;
	
	x = -2;
	y = -2;
	while (ptr->centerx + (x * ptr->scale) < 0)
	 x += (1 / ptr->scale);
	while (ptr->centerx + (x * ptr->scale) < 500 && ptr->centerx + (x * ptr->scale) >= 0)
	{
		y = -2;
		while (ptr->centery + (y * ptr->scale) < 0)
			y += (1 / ptr->scale);
		while (ptr->centery + (y * ptr->scale) < 500 && ptr->centery + (y * ptr->scale) >= 0)
		{
//			ptr->red = 100;
//			ptr->blue = 100;
			ptr->green = 200;
			mod = ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n);
			if (mod <= 4)
			{
				ptr->green -= mod * 300;
				ft_draw(ptr, ptr->centerx + (x * ptr->scale), ptr->centery + (y * ptr->scale));
			}
//			ptr->red = 200;
//			ptr->blue = 200;
//			if (ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n + 10) <= 4)
//				ft_draw(ptr, 250 + (x * ptr->scale), 250 + (y * ptr->scale));
//			ptr->red = 0;
//			ptr->blue = 0;
//			ptr->green = 0;
//			if (ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n + 10) <= 4)
//				ft_draw(ptr, 250 + (x * ptr->scale), 250 + (y * ptr->scale));
//			printf("%f\n", ptr->scale);
			y = y + (1 / ptr->scale);
		}
		x = x + (1 / ptr->scale);
	}
}
		
