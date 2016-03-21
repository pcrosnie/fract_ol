/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 11:14:21 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/21 15:00:31 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//double	*ft_suit

void	ft_julia_fract(t_data *ptr)
{
	double x;
	double y;
	double *ret;
	int n;

	n = 20;
	x = -2;
	y = -2;
	while (x <= 2)
	{
		y = -2;
		while (y <= 2)
		{
			ret = ft_set_suit(x, y, ptr->cx, ptr->cy, n);
			if (ft_module(ret[0], ret[1], ptr->cx, ptr->cy) <= 1)
				ft_draw(ptr, 500 + (x * ptr->scale), 500 + (y * ptr->scale));
			y = y + 0.01;
		}
		x = x + 0.01;
	}
}
		
