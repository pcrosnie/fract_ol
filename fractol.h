/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:25:31 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/19 19:19:09 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"

typedef struct s_data
{
	void *mlx;
	void *win;
	void *pict;
	float x;
	float y;
	float cx;
	float cy;
	char *data_adrr;
	int blue;
	int red;
	int green;
	int bits_per_pixel;
	int size_line;
	int endian;
	float scale;
}				t_data;

void	ft_mandelbrot_fract(t_data *ptr);
int		ft_key_hook(int button, t_data *ptr);
void	ft_set_mandelbrot_window(t_data *ptr);
void	ft_draw(t_data *ptr, int x, int y);
float	ft_module(float x, float y, float cx, float cy);
float	*ft_set_suit(float x, float y, float cx, float cy, int lim);

#endif
