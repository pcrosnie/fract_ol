/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/22 11:23:36 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_julia_fract(t_data *ptr)
{
	double x;
	double y;
	int n;
	
	n = 50;
	x = -2;
	y = -2;
	while (250 + (x * ptr->scale) < 0)
	 x += (1 / ptr->scale);
	while (250 + (x * ptr->scale) < 500 && 250 + (x * ptr->scale) >= 0)
	{
		y = -2;
		while (250 + (y * ptr->scale) < 0)
			y += (1 / ptr->scale);
		while (250 + (y * ptr->scale) < 500 && 250 + (y * ptr->scale) >= 0)
		{
			ptr->red = 200;
			ptr->blue = 200;
			if (ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n) <= 4)
				ft_draw(ptr, 250 + (x * ptr->scale), 250 + (y * ptr->scale));
			ptr->red = 0;
			ptr->blue = 0;
			if (ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n + 20) <= 4)
				ft_draw(ptr, 250 + (x * ptr->scale), 250 + (y * ptr->scale));
//			printf("%f\n", ptr->scale);
			y = y + (1 / ptr->scale);
		}
		x = x + (1 / ptr->scale);
	}
}
		
