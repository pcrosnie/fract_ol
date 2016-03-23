/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:25:31 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/23 13:51:41 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

typedef struct s_data
{
	int param;
	void *mlx;
	void *win;
	void *pict;
	float x;
	float y;
	float cx;
	float cy;
	double centerx;
	double centery;
	char *data_adrr;
	int blue;
	int red;
	int green;
	int bits_per_pixel;
	int size_line;
	int endian;
	int n;
	double scale;
}				t_data;

void	ft_julia_fract(t_data *ptr);
void	ft_mandelbrot_fract(t_data *ptr);
int		ft_key_hook(int button, t_data *ptr);
void	ft_set_mandelbrot_window(t_data *ptr);
void	ft_draw(t_data *ptr, float x, float y);
double	ft_module(double x, double y, float cx, float cy);
double	ft_set_suit(float x, float y, float cx, float cy, int lim);

#endif
