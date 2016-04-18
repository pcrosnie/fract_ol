/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:40:03 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/18 11:27:04 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		motion_notify2(int x, int y, t_data *ptr)
{
	x = y;
	if (ptr->param == 0)
	{
		ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
		free(ptr->data_adrr);
		ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
		ft_set_color(ptr);
		ft_mandelbrot_fract(ptr);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	}
	return (0);
}

int             ft_set_mouse2(int button, int a, int b, t_data *ptr)
{
	float x;
	float y;

	x = a;
	y = b;
	if (button == 4 || button == 7)
	{
		ptr->scale /= ptr->tmp_scale;
		if (ptr->n < 40 && ptr->scale / 30 > 15)
			ptr->n = ptr->scale / 30;
	}
	if (button == 5 || button == 6)
	{
		ptr->scale *= ptr->tmp_scale;
		if (ptr->n < 50 && ptr->scale / 30 > 15)
			ptr->n = ptr->scale / 30;
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	//      ft_set_color(ptr);
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int		ft_key_hook(int button, t_data *ptr)
{
	if (button == 126)
		ptr->centery += (ptr->scale / 8);
	if (button == 125)
		ptr->centery -= (ptr->scale / 8);
	if (button == 124)
		ptr->centerx -= (ptr->scale / 8);
	if (button == 123)
		ptr->centerx += (ptr->scale / 8);
	if (button == 78)
		ptr->n--;
	if (button == 69)
		ptr->n++;
	if (button == 34)
	{
		ptr->scale += 30;
		ptr->n = ptr->scale / 10;
	}
	if (button == 31)
	{
		ptr->scale -= 30;
		ptr->n = ptr->scale / 10;
	}
	if (button == 53)
		exit(0);
	if (button == 49)
	{
		if (ptr->param == 0)
			ptr->param = 1;
		else
			ptr->param = 0;
	}
	//mlx_clear_window(ptr->mlx, ptr->win);
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_mandelbrot_fract(t_data *ptr)
{
	double cx;
	double cy;
	double mod;

	cx = -2;
	cy = -2;
	while (ptr->centerx + (cx * ptr->scale) < 0)
		cx += (1 / ptr->scale);
	while (ptr->centerx + (cx * ptr->scale) >= 0 && ptr->centerx + (cx * ptr->scale) <= 500)
	{
		cy = -2;
		while (ptr->centery + (cy * ptr->scale) < 0)
			cy += (1 / ptr->scale);
		while (ptr->centery + (cy * ptr->scale) >= 0 && ptr->centery + (cy * ptr->scale) < 500)
		{
			ptr->green = 200;
			mod = ft_set_suit(ptr->x, ptr->y, cx, cy, ptr->n);
			if (mod <= 4)
			{
				ptr->green -= mod * 300;
				ft_draw(ptr, ptr->centerx + (cx * ptr->scale), ptr->centery + (cy * ptr->scale));
			}
			cy = cy + (1 / ptr->scale);
		}
		cx = cx + (1 / ptr->scale);
	}
}

void	ft_set_mandelbrot_window(t_data *ptr)
{
	ptr->x = 0;
	ptr->y = 0;
	ptr->scale = 100;
	ptr->centerx = 250;
	ptr->centery = 250;
	ptr->red = 255;
	ptr->tmp_scale = 2;
	ptr->blue = 0;
	ptr->green = 0;
	ptr->n = 10;
	ptr->param = 0;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_key_hook, ptr);
	mlx_hook(ptr->win, 6, (1L >> 0),motion_notify2, ptr);
	mlx_mouse_hook(ptr->win, ft_set_mouse2, ptr);
	mlx_loop(ptr->mlx);
}
