/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newton_fract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:22:49 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/18 14:57:54 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	double mod;

	ptr->green = 200;
	mod = ft_set_newton_suit(x, y, n);
	if (mod <= 1)
	{
		ptr->green -= mod * 300;
		ft_draw(ptr, ptr->gx + (x * ptr->sc), ptr->gy + (y * ptr->sc));
	}
}

void	ft_newton_fract(t_data *ptr)
{
	double	x;
	double	y;
	int		n;

	n = 1;
	while (n <= ptr->n)
	{
		x = -2;
		while (ptr->gx + (x * ptr->sc) < 0)
			x += (1 / ptr->sc);
		while (ptr->gx + (x * ptr->sc) >= 0 && ptr->gx + (x * ptr->sc) < 499)
		{
			y = -2;
			while (ptr->gy + (y * ptr->sc) < 0)
				y += (1 / ptr->sc);
			while (ptr->gy + (y * ptr->sc) >= 0
					&& ptr->gy + (y * ptr->sc) < 500)
			{
				ft_set_num(ptr, x, y, n);
				y = y + (1 / ptr->sc);
			}
			x = x + (1 / ptr->sc);
		}
		n++;
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

int		ft_key_hook2(int button, t_data *ptr)
{
	(button == 126) ? ptr->gy += (ptr->sc / 4) : 0;
	(button == 125) ? ptr->gy -= (ptr->sc / 4) : 0;
	(button == 124) ? ptr->gx -= (ptr->sc / 4) : 0;
	(button == 123) ? ptr->gx += (ptr->sc / 4) : 0;
	(button == 78) ? ptr->n-- : 0;
	(button == 69) ? ptr->n++ : 0;
	(button == 34) ? ptr->sc += 30 : 0;
	(button == 31) ? ptr->sc -= 30 : 0;
	(button == 53) ? exit(0) : 0;
	(button == 15) ? ft_reset3(ptr) : 0;
	(button == 78) ? ptr->n-- : 0;
	(button == 69) ? ptr->n++ : 0;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int		motion_notify3(int x, int y, t_data *ptr)
{
	x = y;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_set_color(ptr);
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int		ft_set_mouse3(int button, int a, int b, t_data *ptr)
{
	float x;
	float y;

	x = a;
	y = b;
	if (button == 4 || button == 7)
	{
		ptr->sc /= ptr->tmp_scale;
	}
	if (button == 5 || button == 6)
	{
		ptr->sc *= ptr->tmp_scale;
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_set_newton_window(t_data *ptr)
{
	ptr->tmp_scale = 100;
	ptr->sc = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 4;
	ptr->gx = 250;
	ptr->gy = 250;
	ptr->tmp_scale = 2;
	ptr->param = 0;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_set_color(ptr);
	ft_newton_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_key_hook2, ptr);
	mlx_hook(ptr->win, 6, (1L >> 0), motion_notify3, ptr);
	mlx_mouse_hook(ptr->win, ft_set_mouse3, ptr);
	mlx_loop(ptr->mlx);
}
