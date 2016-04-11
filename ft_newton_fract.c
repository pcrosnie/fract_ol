/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newton_fract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:22:49 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/11 11:21:57 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_set_newton_suit(double x, double y, int lim)
{
	int n;
	double tmpx;
	double retx;
	double rety;

	n = 0;
	retx = x;
	rety = y;
	while (n < lim)
	{
		tmpx = retx;
		retx = (retx * retx * retx) - (rety * rety * retx) - (2 * retx * rety * rety) + 1;
		rety = (3 * tmpx * tmpx * rety) - (rety * rety * rety);
		n++;
	}
	return (hypot(retx, rety));
}

void	ft_newton_fract(t_data *ptr)
{
	double x;
	double y;
	double mod;
	int n;

	n = 1;
	x = -2;
	y = -2;
	while (n <= ptr->n)
	{
		x = -2;
		while (ptr->centerx + (x * ptr->scale) < 0)
			x += (1 / ptr->scale);
		while (ptr->centerx + (x * ptr->scale) >= 0 && ptr->centerx + (x * ptr->scale) < 500)
		{
			y = -2;
			while (ptr->centery + (y * ptr->scale) < 0)
				y += (1 / ptr->scale);
			while (ptr->centery + (y * ptr->scale) >= 0 && ptr->centery + (y * ptr->scale) < 500)
			{
				ptr->green = 200;
				mod = ft_set_newton_suit(x, y, n);
				if (mod <= 1)
				{
					ptr->green -= mod * 300;
					ft_draw(ptr, ptr->centerx + (x * ptr->scale), ptr->centery + (y * ptr->scale));
				}
				y = y + (1 / ptr->scale);
			}
			x = x + (1 / ptr->scale);
		}
		n++;
	}
}

void	ft_reset3(t_data *ptr)
{
	ptr->tmp_scale = 100;
	ptr->scale = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 4;
	ptr->centerx = 250;
	ptr->centery = 250;
	ptr->exp = 0;
	ptr->param = 0;
}

int             ft_key_hook2(int button, t_data *ptr)
{
	if (button == 126)
		ptr->centery += 30;
	if (button == 125)
		ptr->centery -= 30;
	if (button == 124)
		ptr->centerx -= 30;
	if (button == 123)
		ptr->centerx += 30;
	if (button == 78)
		ptr->n--;
	if (button == 69)
		ptr->n++;
	if (button == 34)
	{
		ptr->scale += 30;
	}
	if (button == 31)
	{
		ptr->scale -= 30;
	}
	if (button == 53)
		exit(0);
	(button == 15) ? ft_reset3(ptr) : 0;
	(button == 78) ? ptr->n-- : 0;
	(button == 69) ? ptr->n++ : 0;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int             motion_notify3(int x, int y, t_data *ptr)
{
	x = y;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_set_color(ptr);
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int        ft_set_mouse3(int button, int a, int b, t_data *ptr)
{
	float x;
	float y;

	x = a;
	y = b;
	if (button == 4 || button == 7)
	{
		ptr->tmp_scale = ptr->scale;
		ptr->scale -= (50 + ptr->exp);
		ptr->exp -= 50 + ptr->exp2;
		ptr->exp2 -= 30;
//		if (ptr->n < 40 && ptr->scale / 30 > 15)
//			ptr->n = ptr->scale / 30;
	}
	if (button == 5 || button == 6)
	{
		ptr->tmp_scale = ptr->scale;
		ptr->scale += (50 + ptr->exp);
		ptr->exp += 50 + ptr->exp2;
		ptr->exp2 += 30;
//		if (ptr->n < 50 && ptr->scale / 30 > 15)
//			ptr->n = ptr->scale / 30;
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	//      ft_set_color(ptr);
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void    ft_set_newton_window(t_data *ptr)
{
	ptr->tmp_scale = 100;
	ptr->scale = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 4;
	ptr->centerx = 250;
	ptr->centery = 250;
	ptr->exp = 0;
	ptr->exp2 = 0;
	ptr->param = 0;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_set_color(ptr);
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_key_hook2, ptr);
	mlx_hook(ptr->win, 6, (1L >> 0), motion_notify3, ptr);
	mlx_mouse_hook(ptr->win, ft_set_mouse3, ptr);
	mlx_loop(ptr->mlx);
}
