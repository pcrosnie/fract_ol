/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:25:31 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/04/18 16:24:48 by pcrosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

typedef struct		s_data
{
	float	coeff_dir;
	int		exp;
	int		param;
	void	*mlx;
	void	*win;
	void	*pict;
	double	x;
	double	y;
	float	cx;
	float	cy;
	double	gx;
	double	gy;
	char	*data_adrr;
	int		blue;
	int		red;
	int		green;
	int		bits;
	int		len;
	int		endian;
	int		exp2;
	int		n;
	int		q;
	double	tmp_scale;
	double	sc;
}					t_data;

int					ft_mouse_hook(int button, t_data *ptr);
int					ft_set_mouse2(int button, int a, int b, t_data *ptr);
int					motion_notify2(int x, int y, t_data *ptr);
void				ft_julia_fract(t_data *ptr);
void				ft_mandelbrot_fract(t_data *ptr);
int					ft_key_hook(int button, t_data *ptr);
void				ft_set_mandelbrot_window(t_data *ptr);
void				ft_draw(t_data *ptr, float x, float y);
double				ft_module(double x, double y, float cx, float cy);
double				ft_set_suit(t_data *ptr, int lim);
int					ft_set_mouse(int button, int a, int b, t_data *ptr);
void				ft_set_color(t_data *ptr);
void				ft_set_newton_window(t_data *ptr);

#endif
