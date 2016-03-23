/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:24:58 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/23 15:47:43 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>


void	ft_draw(t_data *ptr, float x, float y)
{
//	ft_putnbr((x * ptr->bits_per_pixel) / 8 + (y * (ptr->size_line)));
//	ft_putnbr(ptr->green);
//	ft_putchar('\n');
	int nb;
/*
	float xi;
	float yi;

	xi = 500 + (x / 10000 * ptr->scale);
	yi = 500 + (y / 10000 * ptr->scale);*/
	nb = (x * ptr->bits_per_pixel) / 8 + (y * ptr->size_line);
	if (nb > 0 && x > 0 && y > 0 && x < 1000 && y < 1000)
	{
	ptr->data_adrr[nb] = ptr->red;
	ptr->data_adrr[nb + 1] = ptr->green;
	ptr->data_adrr[nb + 2] = ptr->blue;
	}
}

double		ft_module(double x, double y, float cx, float cy)
{
	double nb;

	nb = ((x * x) - (y * y) + cx) * ((x * x) - (y * y) + cx) + ((2 * x * y + cy) * (2 * x * y + cy));
	return (nb);
}

double	ft_set_suit(float x, float y, float cx, float cy, int lim)
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
		retx = (retx * retx) - (rety * rety) + cx;
		rety = (2 * tmpx * rety + cy);
		n++;
	}
	return (hypot((retx * retx) - (rety * rety) + cx, 2 * retx * rety + cy));
}
/*
void	ft_julia_fract(t_data *ptr)
{
	int x;
	int y;
	float *ret;
	int n;

	ptr->red = 0;
	ptr->green = 255;
	ptr->blue = 255;
	n = 11;
	x = -20000;
	y = -20000;
	while (n < 41)
	{
		x = -20000;
		while (x < 20000)
		{
			y = -20000;
			while (y < 20000)
			{
			ret = ft_set_suit((float)x, (float)y, ptr->cx, ptr->cy, n);
			if (ft_module(ret[0], ret[1], ptr->cx, ptr->cy) <= 4)
				ft_draw(ptr, x, y);
			y += 50;
			}
			x += 50;
		}
		n += 10;
	}
}

void	ft_julia_fract(t_data *ptr)
{
	float x;
	float y;
	float *ret;
	int n;

	ft_putnbr(ptr->scale);
	ft_putchar('\n');
	n = 11;
	x = -2;
	y = -2;
	ptr->red = 0;
	ptr->green = 255;
	ptr->blue = 255;
	while (x <= 2)
	{
		y = -2;
		while (y <= 2)
		{
			ret = ft_set_suit(x, y, ptr->cx, ptr->cy, n);
//			ft_putnbr(ret[0]);
//			ft_putchar('\n');
//			ft_putnbr(ret[1]);
//			ft_putchar('\n');
			if (ft_module(ret[0], ret[1], ptr->cx, ptr->cy) <= 4)
			{
//				ft_putstr("HERE\n");
				ft_draw(ptr, 500 + (x * ptr->scale), 500 + (y * ptr->scale));
//				ft_putstr("IN\n");
			}
			ret = ft_set_suit(x, y, ptr->cx, ptr->cy, n + 10);
			if (ft_module(ret[0], ret[1], ptr->cx, ptr->cy) <= 4)
				ft_draw(ptr, 500 + (x * ptr->scale), 500 + (y * ptr->scale));
			y = y + (1 / ptr->scale);
		}
		x = x + (1 / ptr->scale);
	}
	if (n == 0)
		n = 1;
	else
	n += 10;
	ptr->blue = 0;
	ptr->green = 0;
	ptr->red = 0;
}
*/

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

int		ft_mouse_hook(int button, t_data *ptr)
{
	ft_putnbr(button);
	ft_putchar('\n');
	if (button == 49)
	{
		if (ptr->param == 0)
			ptr->param = 1;
		else
			ptr->param = 0;
	}
	if (button == 126)
	ptr->n = ptr->n + 1;
	if (button == 125)
	ptr->n = ptr->n - 1;
	if (button == 124)
		ptr->cy = ptr->cy + 0.01;
	if (button == 123)
		ptr->cy = ptr->cy - 0.01;
	if (button == 34)
	{
		ptr->scale += 50;
		if (ptr->n < 40)
		ptr->n += 1;
	}
	if (button == 31)
	{
		ptr->scale -= 50;
		ptr->n -= 1;
	}
	if (button == 53)
		exit(0);
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
//	ft_set_color(ptr);
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

int		motion_notify(int x, int y, t_data *ptr)
{
	float xi;
	float yi;

	xi = (float)x;
	yi = (float)y;
	if (ptr->param == 0)
	{
	ptr->cx = xi / 1000;
	ptr->cy = yi / 1000;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_set_color(ptr);
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	}
	return (0);
}

int		ft_set_mouse(int button, int x, int y, t_data *ptr)
{
	if (button == 4 || button == 7)
	{
		ptr->scale -= 30;
		if (ptr->n < 30)
		ptr->n = ptr->scale / 10;
		if (x < 500 && x > 0 && y < 500 && y > 0)
		{
//		ptr->centerx += (x) / (ptr->n / 3);
//		ptr->centery += (y) / (ptr->n / 3);
		}
	}
	if (button == 5 || button == 6)
	{
		ptr->scale += 30;
		ptr->n = ptr->scale / 10;
		if (x < 500 && x > 0 && y < 500 && y > 0)
		{
//		ptr->centerx -= (x) / (ptr->n / 3);
//		ptr->centery -= (y) / (ptr->n / 3);
		}
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
//	ft_set_color(ptr);
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_set_julia_window(t_data *ptr)
{
	ptr->cx = -1;
	ptr->cy = 0;
	ptr->scale = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 15;
	ptr->centerx = 250;
	ptr->centery = 250;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_set_color(ptr);
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_mouse_hook, ptr);
	mlx_hook(ptr->win, 6, (1L >> 0), motion_notify, ptr);
	mlx_mouse_hook(ptr->win, ft_set_mouse, ptr);
	mlx_loop(ptr->mlx);
}

int		main(int argc, char **argv)
{
	t_data *ptr;

	ptr = (t_data *)malloc(sizeof(t_data));
	if (argc == 2 && argv[1][0] == '1') 
		ft_set_julia_window(ptr);
	else if (argc == 2 && argv[1][0] == '2')
		ft_set_mandelbrot_window(ptr);
	return (0);
}
