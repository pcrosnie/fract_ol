/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:40:03 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/22 10:39:36 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_key_hook(int button, t_data *ptr)
{
	if (button == 126)
		ptr->x = ptr->x + 0.01;
	if (button == 125)
		ptr->x = ptr->x - 0.01;
	if (button == 124)
		ptr->y = ptr->y + 0.01;
	if (button == 123)
		ptr->y = ptr->y - 0.01;
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
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_mandelbrot_fract(t_data *ptr)
{
	float cx;
	float cy;
	int n;

	n = 11;
	cx = -2;
	cy = -2;
	ptr->red = 0;
	ptr->green = 255;
	ptr->blue = 255;
	while (n < 41)
	{
		if (n == 21)
			n = 31;
		cx = -2;
		while (cx <= 2)
		{
			cy = -2;
			while (cy <= 2)
			{
				if (ft_set_suit(ptr->x, ptr->y, cx, cy, n) <= 4)
				{
					ft_draw(ptr, 500 + (cx * ptr->scale), 500 + (cy * ptr->scale));
				}
				cy = cy + (1 / ptr->scale);
			}
			cx = cx + (1 / ptr->scale);
		}
		if (n == 0)
			n = 1;
		else
			n += 10;
		if (ptr->red < 200)
		{
			ptr->red += 200;
			ptr->blue -= 200;
			ptr->green -= 200;
		}
		else
			ptr->blue -= 200;
	}
}

void	ft_set_mandelbrot_window(t_data *ptr)
{
	ptr->x = 0;
	ptr->y = 0;
	ptr->scale = 100;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 1000, 1000, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 1000, 1000);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits_per_pixel), &(ptr->size_line), &(ptr->endian));
	ft_mandelbrot_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	mlx_key_hook(ptr->win, ft_key_hook, ptr);
	mlx_loop(ptr->mlx);
}
