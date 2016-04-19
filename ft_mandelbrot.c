/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:40:03 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/19 11:46:02 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_set_mouse2(int button, int a, int b, t_data *ptr)
{
	float x;
	float y;

	x = a;
	y = b;
	if (button == 4 || button == 7)
	{
		ptr->sc /= ptr->tmp_scale;
		if (ptr->n < 40 && ptr->sc / 30 > 15)
			ptr->n = ptr->sc / 50;
	}
	if (button == 5 || button == 6)
	{
		ptr->sc *= ptr->tmp_scale;
		if (ptr->n < 50 && ptr->sc / 30 > 15)
			ptr->n = ptr->sc / 50;
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int		ft_key_hook(int button, t_data *ptr)
{
	(button == 15) ? ft_reset2(ptr) : 0;
	(button == 126) ? ptr->gy += 250 : 0;
	(button == 125) ? ptr->gy -= 250 : 0;
	(button == 124) ? ptr->gx -= 250 : 0;
	(button == 123) ? ptr->gx += 250 : 0;
	(button == 78) ? ptr->n-- : 0;
	(button == 69) ? ptr->n++ : 0;
	(button == 53) ? exit(0) : 0;
	if (button == 49)
		(ptr->param == 0) ? ptr->param = 1 : 0;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_cpy(t_data *ptr, double x, double y)
{
	ptr->cx = x;
	ptr->cy = y;
	ptr->green = 200;
}

void	ft_mandelbrot_fract(t_data *ptr)
{
	double x;
	double y;
	double mod;

	x = -2;
	while (ptr->gx + (x * ptr->sc) < 0)
		x += (1 / ptr->sc);
	while (ptr->gx + (x * ptr->sc) >= 0 && ptr->gx + (x * ptr->sc) <= 500)
	{
		y = -2;
		while (ptr->gy + (y * ptr->sc) < 0)
			y += (1 / ptr->sc);
		while (ptr->gy + (y * ptr->sc) >= 0 && ptr->gy + (y * ptr->sc) < 500)
		{
			ft_cpy(ptr, x, y);
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

void	ft_set_mandelbrot_window(t_data *ptr)
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
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_key_hook, ptr);
	mlx_hook(ptr->win, 6, (1L >> 0), motion_notify2, ptr);
	mlx_mouse_hook(ptr->win, ft_set_mouse2, ptr);
	mlx_loop(ptr->mlx);
}
