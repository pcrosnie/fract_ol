/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_n_rest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 10:44:03 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/19 13:01:03 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_set_hook(t_data *ptr, int button)
{
	(button == 126) ? ptr->gy += 250 : 0;
	(button == 125) ? ptr->gy -= 250 : 0;
	(button == 124) ? ptr->gx -= 250 : 0;
	(button == 123) ? ptr->gx += 250 : 0;
	if (button == 34)
	{
		ptr->sc += 50;
		(ptr->n < 50) ? ptr->n += 1 : 0;
	}
	if (button == 31)
	{
		ptr->sc -= 50;
		ptr->n -= 1;
	}
}

void	ft_reset2(t_data *ptr)
{
	ptr->x = 0;
	ptr->y = 0;
	ptr->sc = 100;
	ptr->gx = 250;
	ptr->gy = 250;
	ptr->red = 255;
	ptr->tmp_scale = 2;
	ptr->blue = 0;
	ptr->green = 0;
	ptr->n = 10;
	ptr->param = 0;
}

void	ft_set_color(t_data *ptr)
{
	if (ptr->blue > 230)
		ptr->blue = 0;
	else
		ptr->blue += 20;
	if (ptr->red > 230)
		ptr->red = 0;
	else
		ptr->red += 20;
}

void	ft_reset(t_data *ptr)
{
	ptr->cx = -1;
	ptr->cy = 0;
	ptr->tmp_scale = 100;
	ptr->sc = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 15;
	ptr->gx = 250;
	ptr->gy = 250;
	ptr->exp = 0;
}
