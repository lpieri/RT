/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:26:19 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/17 10:54:37 by bspindle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	perlin_permutation(t_perlin_stuff *per)
{
	static int	tab[] = {
		131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
		8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197,
		62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56,
		87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27,
		166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105,
		92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80,
		73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188,
		159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124,
		123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47,
		16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
		154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19,
		98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
		251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145,
		235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84,
		204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222,
		114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180, 151,
		160, 137, 91, 90, 15};

	per->permutation = tab;
}

static void	perlin_grad_tab(t_perlin_stuff *per)
{
	double		unit;
	t_vector2d	tab[8];

	unit = 0.5 * sqrt(2);
	tab[0] = new_vector_2d(1, 0);
	tab[1] = new_vector_2d(-1, 0);
	tab[2] = new_vector_2d(0, 1);
	tab[3] = new_vector_2d(0, -1);
	tab[4] = new_vector_2d(unit, unit);
	tab[5] = new_vector_2d(-unit, unit);
	tab[6] = new_vector_2d(-unit, -unit);
	tab[7] = new_vector_2d(unit, -unit);
	per->grad_tab = tab;
}

static void	random_tab(t_perlin_stuff *per)
{
	int	ret[512];
	int	i;

	i = 0;
	while (i < 512)
	{
		ret[i] = per->permutation[i % 256];
		i++;
	}
	per->permutation = ret;
}

void		perlin_init(t_perlin_stuff *perlin)
{
	perlin_permutation(perlin);
	perlin_grad_tab(perlin);
	random_tab(perlin);
}

int			**perlin_tab_init(void)
{
	int	i;
	int	**tab;

	i = 0;
	tab = (int**)malloc(sizeof(int) * 256);
	if (!tab)
	{
		ft_putstr("malloc failed in perlin_tab_init()\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 256)
	{
		tab[i] = (int*)malloc(sizeof(int) * 256);
		if (!tab[i])
		{
			ft_putstr("malloc failed in perlin_tab_init()\n");
			exit(EXIT_FAILURE);
		}
	}
	return (tab);
}