/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcrosnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:25:31 by pcrosnie          #+#    #+#             */
/*   Updated: 2016/03/19 13:46:25 by pcrosnie         ###   ########.fr       */
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
}			t_data;

#endif
