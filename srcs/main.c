/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:09:23 by tmilon            #+#    #+#             */
/*   Updated: 2018/06/14 14:10:45 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "SDL_ttf.h"

static void		launch(t_all *param, t_env *env)
{
	SDL_Event		event;

	env->rend = surface_2_rend(env);
	while (env->loop)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			env->loop = 0;
		else if (event.type == SDL_KEYDOWN)
			sdl_key(param, event.key.keysym.sym);
		if (event.type == SDL_WINDOWEVENT)
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				SDL_GetWindowSize(env->win, &env->w, &env->h);
				new_ui(param);
				refresh_img(param);
			}
		//else if (event.type == SDL_MOUSEBUTTONDOWN)
		//	event_button(param, event.button.x, event.button.y);
	}
}

static t_all	init_param(t_all param)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_abort("Error SDL_Init");
	if (TTF_Init() != 0)
		ft_abort("Error TTF_Init");
	if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)))
		ft_abort("Error IMG_Init");
	create_win_render(param.env);
	create_all_surface(param.env);
	clear_render(param.env);
	SDL_GetWindowSize(param.env->win, &param.env->w, &param.env->h);
	//	param.data.ambiantlight = 0;
	param.env->loop = 1;
	param.data.fastmode = 1;
	param.data.filter = 4;
	return (param);
}

int				main(int ac, char **av)
{
	t_all	param;

	if (ac != 2)
		ft_abort("Usage: ./rtv1 [scene_file.csv]");
	if (!(param.env = (t_env*)malloc(sizeof(t_env))))
		ft_abort("Malloc Failed: struct env");
	parse(&param, av[1]);
	param = init_param(param);
	new_ui(&param);
	create_render(&param);
	launch(&param, param.env);
	quit_exe(param);
}
