/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:48:17 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/14 14:36:38 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static int	rainbow(double v, int r_number)
{
	int		size;
	int		rainbowsize;
	t_color	rainbow;
	int		position;

	size = 60;
	rainbowsize = size * 6;
	while (v < 0)
		v += rainbowsize;
	v *= rainbowsize * r_number;
	position = (int)v % rainbowsize;
	if (position < size)
		rainbow = new_color((position) * 255 / size, 255, 0);
	else if (position < size * 2)
		rainbow = new_color(255, (size - position % size) * 255 / size, 0);
	else if (position < size * 3)
		rainbow = new_color(255, 0, (position % size) * 255 / size);
	else if (position < size * 4)
		rainbow = new_color((size - position % size) * 255 / size, 0, 255);
	else if (position < size * 5)
		rainbow = new_color(0, (position % size) * 255 / size, 255);
	else
		rainbow = new_color(0, 255, (size - position % size) * 255 / size);
	return (color_to_int(rainbow));
}

static int	checker_pattern(int color, double u, double v)
{
	u *= 10;
	v *= 100;
	if (((int)u % 2 == 0 && (int)v % 2 == 0)
	|| (((int)u % 2 != 0 && (int)v % 2 != 0)))
		color = 0xFFFFFF - color;
	return (color);
}

static int	get_texture_color(double u, double v, t_shape s)
{
	double	modi;

	modi = s.textunit.texture_width;
	u = u * modi / (s.textunit.x_scale);
	v = v * modi / (s.textunit.y_scale);
	if (s.textunit.x_scale < 1)
		u -= (modi - modi * s.textunit.x_scale) / (2 * s.textunit.x_scale);
	else
		u += (modi * s.textunit.x_scale - modi) / (2 * s.textunit.x_scale);
	if (s.textunit.y_scale < 1)
		v -= (modi - modi * s.textunit.y_scale) / (2 * s.textunit.y_scale);
	else
		v += (modi * s.textunit.y_scale - modi) / (2 * s.textunit.y_scale);
	u += s.textunit.x_offset;
	v += s.textunit.y_offset;
	while (v < 0)
		v += modi;
	while (u < 0)
		u += modi;
	u = (int)u % (int)modi;
	v = (int)v % (int)modi;
	return (s.textunit.texture[(int)u + (int)((int)v * modi)]);
}

int			texture(int color, t_intersect i, t_shape s)
{
	double u;
	double v;

	get_uv_mapping_coord(&u, &v, i, s);
	if (s.textunit.has_texture)
		color = get_texture_color(u, v, s);
	if (s.textunit.has_rainbow)
		color = interpolate(color, rainbow(v, 2), s.textunit.has_rainbow);
	if (s.textunit.has_checker)
		color = interpolate(color, checker_pattern(color, u, v),
											s.textunit.has_checker);
	return (color);
}
