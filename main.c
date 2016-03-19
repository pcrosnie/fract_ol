/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:24:58 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/19 15:16:31 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>


void	ft_draw(t_data *ptr, int x, int y)
{
//	ft_putnbr((x * ptr->bits_per_pixel) / 8 + (y * (ptr->size_line)));
//	ft_putnbr(ptr->green);
//	ft_putchar('\n');
	ptr->data_adrr[(x * ptr->bits_per_pixel) / 8 + (y * (ptr->size_line))] = ptr->red;
	ptr->data_adrr[(x * ptr->bits_per_pixel) / 8 + (y * (ptr->size_line)) + 1] = ptr->green;
	ptr->data_adrr[(x * ptr->bits_per_pixel) / 8 + (y * (ptr->size_line)) + 2] = ptr->blue;
}

float		ft_module(float x, float y, float cx, float cy)
{
	float nb;

	nb = ((x * x) - (y * y) + cx) * ((x * x) - (y * y) + cx) + ((2 * x * y + cy) * (2 * x * y + cy));
	return (nb);
}

float	*ft_set_suit(float x, float y, float cx, float cy, int lim)
{
	int n;
	float tmpx;
	float *ret;

	n = 0;
	ret = (float *)malloc(sizeof(float) * 2);
	ret[0] = x;
	ret[1] = y;
	while (n < lim)
	{
		tmpx = ret[0];
		ret[0] = (ret[0] * ret[0]) - (ret[1] * ret[1]) + cx;
		ret[1] = (2 * tmpx * ret[1] + cy);
		n++;
	}
	return (ret);
}

void	ft_julia_fract(t_data *ptr)
{
	float x;
	float y;
	float *ret;
	int n;
	
	n = 0;
	x = -2;
	y = -2;
	ptr->red = 255;
	ptr->green = 0;
	ptr->blue = 0;
	while (n < 51)
	{
		x = -2;
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
			y = y + (1 / ptr->scale);
		}
		x = x + (1 / ptr->scale);
	}
	if (n == 0)
		n = 1;
	else
	n += 10;
	ptr->green += 50;
	ptr->blue += 50;
	ptr->red -= 50;
	}
}

int		ft_mouse_hook(int button, t_data *ptr)
{
//  ft_putnbr(button);
	if (button == 126)
	ptr->cx = ptr->cx + 0.01;
	if (button == 125)
	ptr->cx = ptr->cx - 0.01;
	if (button == 124)
		ptr->cy = ptr->cy + 0.01;
	if (button == 123)
		ptr->cy = ptr->cy - 0.01;
	if (button == 34)
		ptr->scale += 50;
	if (button == 31)
		ptr->scale -= 50;
	if (button == 53)
		exit(0);
	mlx_clear_window(ptr->mlx, ptr->win);
	ptr->pict = mlx_new_image(ptr->mlx, 1000, 1000);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_set_window(t_data *ptr)
{
	ptr->cx = -1;
	ptr->cy = 0;
	ptr->scale = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 1000, 1000, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 1000, 1000);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_mouse_hook, ptr);
	mlx_loop(ptr->mlx);
}

int		main()
{
	t_data *ptr;
	int i;
	int j;

	j = 100;
	i = 0;
	ptr = (t_data *)malloc(sizeof(t_data));
	ft_set_window(ptr);
/*	while (i < a / 4)
	{
		ptr->data_adrr[(i * bits_per_pixel) / 8 + (j * a)] = ptr->blue;
		ptr->data_adrr[(i * bits_per_pixel) / 8 + (j * a) + 1] = ptr->blue;
		ptr->data_adrr[(i * bits_per_pixel) / 8 + (j * a) + 2] = ptr->blue;
		i++;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_loop(ptr->mlx);*/
}
