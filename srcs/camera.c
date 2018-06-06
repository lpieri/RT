/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:20:58 by cpieri            #+#    #+#             */
/*   Updated: 2018/06/04 17:01:23 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

t_camera	new_cam(t_vector3d orig, double x, double y, double z)
{
	t_camera	camera;

	camera.aspect_ratio = W_WIDTH / (double)W_HEIGHT;
	camera.origin = orig;
	camera.rot = new_matrix(x, y, z);
	camera.fov = 60;
	camera.h = atan(camera.fov);
	camera.w = camera.h * camera.aspect_ratio;
	return (camera);
}

t_vector3d	set_axe(int x, int y, t_camera *cam)
{
	t_vector3d	new_axe;
	t_vector3d	ndc_space;
	t_vector3d	plan_cam;
	t_vector3d	direction;

	ndc_space.x = (x + 0.5) / W_WIDTH;
	ndc_space.y = (y + 0.5) / W_HEIGHT;
	new_axe.x = (2 * ndc_space.x - 1) * cam->aspect_ratio;
	new_axe.y = 1 - 2 * ndc_space.y;
	plan_cam.x = new_axe.x * tan((cam->fov * 0.5) * DEG2RAD);
	plan_cam.y = new_axe.y * tan((cam->fov * 0.5) * DEG2RAD);
	direction = new_vector_3d(plan_cam.x, plan_cam.y, 1);
	direction = adjust_direction(direction, cam->rot);
	return (normalize(direction));
}
