/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:24:58 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/19 11:44:07 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_mouse_hook(int button, t_data *ptr)
{
	(button == 69) ? ptr->n++ : 0;
	(button == 78) ? ptr->n-- : 0;
	if (button == 49)
	{
		if (ptr->param == 0)
			ptr->param = 1;
		else
			ptr->param = 0;
	}
	ft_set_hook(ptr, button);
	(button == 53) ? exit(0) : 0;
	(button == 15) ? ft_reset(ptr) : 0;
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
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
		ptr->cx = xi / (900 + ptr->sc);
		ptr->cy = yi / (900 + ptr->sc);
		ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
		free(ptr->data_adrr);
		ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
				, &(ptr->len), &(ptr->endian));
		ft_set_color(ptr);
		ft_julia_fract(ptr);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	}
	return (0);
}

int		ft_set_mouse(int button, int a, int b, t_data *ptr)
{
	double x;
	double y;

	x = a;
	y = b;
	if (button == 4 || button == 7)
	{
		ptr->sc /= ptr->tmp_scale;
		if (ptr->n < 40 && ptr->sc / 30 > 15)
			ptr->n = ptr->sc / 30;
	}
	if (button == 5 || button == 6)
	{
		ptr->sc *= ptr->tmp_scale;
		if (ptr->n < 50 && ptr->sc / 30 > 15)
			ptr->n = ptr->sc / 30;
	}
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	free(ptr->data_adrr);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
	ft_julia_fract(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->pict, 0, 0);
	return (0);
}

void	ft_set_julia_window(t_data *ptr)
{
	ptr->cx = -1;
	ptr->cy = 0;
	ptr->tmp_scale = 2;
	ptr->sc = 100;
	ptr->red = 200;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->n = 10;
	ptr->gx = 250;
	ptr->gy = 250;
	ptr->exp = 4;
	ptr->exp2 = 0;
	ptr->param = 0;
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 500, 500, "fract'ol");
	ptr->pict = mlx_new_image(ptr->mlx, 500, 500);
	ptr->data_adrr = mlx_get_data_addr(ptr->pict, &(ptr->bits)
			, &(ptr->len), &(ptr->endian));
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
	if (argc == 2 && ft_strcmp(argv[1], "julia") == 0)
		ft_set_julia_window(ptr);
	else if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
		ft_set_mandelbrot_window(ptr);
	else if (argc == 2 && ft_strcmp(argv[1], "third") == 0)
		ft_set_newton_window(ptr);
	else
	{
		ft_putstr("Illegal Option :\n\nOnly one Parameter :\n");
		ft_putstr("julia\nmandelbrot\nthird\n");
	}
	return (0);
}
