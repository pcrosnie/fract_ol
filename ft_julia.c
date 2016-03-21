/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/21 16:29:14 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_julia_fract(t_data *ptr)
{
	double x;
	double y;
	double *ret;
	int n;
	
	n = 50;
	x = -2 - (1000 / ptr->scale);
	y = -2 - (1000 / ptr->scale);
	while (x <= 2 - (0.002 * ptr->scale))
	{
		y = -2 - (0.002 * ptr->scale);
		while (y <= 2 - (0.002 * ptr->scale))
		{
			ptr->red = 200;
			ret = ft_set_suit(x, y, ptr->cx, ptr->cy, ptr->n);
			if (hypot((ret[0] * ret[0]) - (ret[1] * ret[1]) + ptr->cx, 2 * ret[0] * ret[1] + ptr->cy) <= 4)
				ft_draw(ptr, 500 + (x * ptr->scale), 500 + (y * ptr->scale));
/*			ptr->red = 0;
			ret = ft_set_suit(x, y, ptr->cx, ptr->cy, n + 30);
			if (ft_module(ret[0], ret[1], ptr->cx, ptr->cy) <= 4)
				ft_draw(ptr, 500 + (x * ptr->scale), 500 + (y * ptr->scale));*/
			y = y + (1 / ptr->scale * 2);
		}
		x = x + (1 / ptr->scale * 2);
	}
}
		
