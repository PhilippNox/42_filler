/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n50_game_pack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgorold <wgorold@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:23:50 by wgorold           #+#    #+#             */
/*   Updated: 2019/09/17 19:06:40 by wgorold          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	game_pack_init_bot_maps(t_game_pack *game_p)
{
	game_p->org.map = NULL;
	game_p->map.map = NULL;
	game_p->adv.map = NULL;
	game_p->pie.map = NULL;
	game_p->att.map = NULL;
	game_p->fld.map = NULL;
	game_p->zon.map = NULL;
	game_p->fre.map = NULL;
	game_p->game.org = &(game_p->org);
	game_p->game.map = &(game_p->map);
	game_p->game.adv = &(game_p->adv);
	game_p->game.pie = &(game_p->pie);
	game_p->game.att = &(game_p->att);
	game_p->game.fld = &(game_p->fld);
	game_p->game.zon = &(game_p->zon);
	game_p->game.fre = &(game_p->fre);
	game_p->game.fields[0] = &(game_p->org);
	game_p->game.fields[1] = &(game_p->map);
	game_p->game.fields[2] = &(game_p->adv);
	game_p->game.fields[3] = &(game_p->pie);
	game_p->game.fields[4] = &(game_p->att);
	game_p->game.fields[5] = &(game_p->fld);
	game_p->game.fields[6] = &(game_p->zon);
	game_p->game.fields[7] = &(game_p->fre);
	game_p->game.fields[8] = NULL;
}

void	game_pack_init_bot(t_game_pack *game_p)
{
	game_pack_init_bot_maps(game_p);
	game_p->game.autoplace = 0;
	game_p->game.autoplay = 0;
	game_p->game.pnt[0] = 0;
	game_p->game.pnt[1] = 0;
	game_p->game.enemy_score = 0;
	game_p->game.show_read_debug = 0;
	game_p->game.show_place = 0;
	game_p->game.show_set_wave_debug = 0;
	game_p->game.show_set_debug = 0;
	game_p->game.show_send = 0;
	game_p->game.show_diff_debug = 0;
	game_p->game.show_score_debug = 0;
	game_p->game.decision_debug = 0;
	game_p->game.show_reset_wave_debug = 0;
	game_p->game.show_att_debug = 0;
	game_p->game.show_general_debug = 0;
	game_p->cmd_l[0] = '\0';
}
