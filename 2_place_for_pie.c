#include "filler.h"

int row_p(t_map *map, int pos)
{
    return (pos / map->col);
}

int col_p(t_map *map, int pos)
{
    return (pos % map->col + SHIFT_M);
}

int col_pg(t_map *map, int pos)
{
    return (pos % map->col);
}

int not_in_borders(t_map *map, int pos, int t_r, int t_c)
{
    if (row_p(map, pos) + t_r >= map->row)
        return (1);
    if (col_p(map, pos) - SHIFT_M + t_c >= map->col)
        return (1);
    return (0);
}

int is_enemy(int player, char trg)
{
    if (player == 1 && trg == 'z') 
        return (1);
    if (player == 2 && trg == 'y') 
        return (1);  
    return (0);
}

void is_ally_inc(int player, char trg, int *count)
{
    if (player == 1 && trg == 'y') 
        (*count)++;
    if (player == 2 && trg == 'z') 
        (*count)++;  
}

int is_a_place(int player, t_map *map, t_map *pie, int pos)
{
    int r;
    int c;
    char tmp;
    int count;

    r = -1;
    c = -1;
    count = 0;
    while (++r < pie->row)
    {
        c = -1;
        while(++c < pie->col)
        {
            if (pie->map[r][c] == '.')
                continue;
            if (not_in_borders(map, pos, r, c))
                return (-1);
            tmp = map->map[row_p(map, pos) + r][col_p(map, pos) + c];
            if (is_enemy(player, tmp))
                return (-2);
            is_ally_inc(player, tmp, &count);
            if (count > 1)
                return (-3);
        }
    }
    if (count == 0)
        return (0);
    return (1);
}

int find_place(int player, t_map *map, t_map *pie)
{
    int pos;
    int res;
    int out;
    int score;
    int tmp_score;

    out = -1;
    pos = -1;
    score = MAX_INT;
    while (++pos / map->col < map->row)
    {
        tmp_score = MAX_INT;
        res = is_a_place(player, map, pie, pos);
        if (res == 1)
        {
            tmp_score = calc_score(map, pie, pos);
            if (tmp_score < score)
            {
                score = tmp_score;
                out = pos;
            }
        }
        if (SHOW_FIND_DEBUG)
            find_debug(map, pos, res, tmp_score);
    }
    if (SHOW_FIND_DEBUG)
        debug_print(">>>>>>>>", 1, 0);
    return (out);
}

void as_map(t_map *src, t_map *trg)
{
    int idx;

    idx = -1;
    while (++idx < src->row)
        ft_strcpy(trg->map[idx], src->map[idx]);
}

int cpy_map(t_map *src, t_map *trg)
{
    int idx;
    int malloc_failed;

    trg->row = src->row;
    trg->col = src->col;
    trg->player = src->player;

    trg->map = (char **)malloc((trg->row) * sizeof(char **));
    if (!trg->map)
		return (1);
    
    malloc_failed = 0;
    idx = -1;
    while (++idx < trg->row)
    {
        if((trg->map[idx] = ft_strnew(trg->col + SHIFT_M)) == NULL)
        {
            malloc_failed = 1;
            break;
        }
    }
    if (malloc_failed)
    {
        while (--idx > -1)
            free(trg->map[idx]);
        free(trg->map);
        return (1);
    }
    return (0);
}

int make_map(t_map *src, t_map *trg)
{
    if (cpy_map(src, trg))
        return (1);
    as_map(src, trg);
    return (0);
}

void place_pie(int pos, t_map *pie, t_map *adv)
{
    char to_place;
    int r;
    int c;

    //to_place = (adv->player == 1) ? 'y' : 'z';
    to_place = 'w';
    r = -1;
    c = -1;
    while (++r < pie->row)
    {
        c = -1;
        while(++c < pie->col)
        {
            if (pie->map[r][c] == '.')
                continue;
            set_val(adv, pos + c + r * (adv->col),to_place);
        }
    }
}

int calc_score(t_map *map, t_map *pie, int pos)
{
    int score;
    int r;
    int c;
    char tmp;

    score = 0;
    r = -1;
    c = -1;
    while (++r < pie->row)
    {
        c = -1;
        while(++c < pie->col)
        {
            if (pie->map[r][c] == '.')
                continue;
            tmp = map->map[row_p(map, pos) + r][col_p(map, pos) + c];
            if (tmp == 'y' || tmp == 'z' || tmp == '.')
                continue;
            score += tmp - 48;
        }
    }
    return (score);
}

int calc_iso_score(t_map *map, t_map *adv)
{
    int pos;
    int out;

    pos = -1;
    out = 0;
    while (++pos / map->col < map->row)
        if(get_val(adv, pos) == '.' && get_val(map, pos) != '.')
            out += 1;
        
    return (out);
}

int calc_diff_score(t_map *map, t_map *adv)
{
    int pos;
    int ad;
    int ma;
    int out;

    pos = -1;
    out = 0;
    while (++pos / map->col < map->row)
    {
        ad = get_val(adv, pos);
        ma = get_val(map, pos);

        if (SHOW_VALUE_MAP_ADV == 2)
        {
            if(ad > 48 && ad < 119 && ma > 48 && ma < 119)
            {
                if (ad == ma)
                    set_val(adv, pos, 48);
                else
                {
                    set_val(adv, pos, ad - ma + 48);
                    out += ad - ma;
                } 
            }
        }
        else
        {
            if(ad > 48 && ad < 119 && ma > 48 && ma < 119 && ad !=ma)
                out += ad - ma;
        }
    }   
    return (out);
}



t_score get_score(int pos, t_map *map, t_map *pie, t_map *adv)
{
    t_score out;
    out.enemy_dist = 1;
    (void) map;

    place_pie(pos, pie, adv);
    set_val_map(adv, adv->player);
    
    out.pos = pos;
    out.enemy_dist = calc_score(map, pie, pos);
    out.diff_map = calc_diff_score(map, adv);
    out.isolated = calc_iso_score(map, adv);

    out.decision = out.enemy_dist * 1 - out.diff_map / 10 - out.isolated * 1;

    if (SHOW_VALUE_MAP_ADV)
    {
        score_debug(map, pos, &out);
        debug_value_map_color_adv(adv, "\t\t\t");
    }
    return (out);
}


t_score find_place_adv(t_map *org, t_map *map, t_map *pie, t_map *adv)
{
    int pos;
    int res;
    
    t_score score;
    t_score tmp_score;

    pos = -1;
    score.decision = MAX_INT;
    score.pos = -1;
    while (++pos / org->col < org->row)
    {
        res = is_a_place(org->player, map, pie, pos);
        if (res == 1)
        {
            as_map(org, adv);
            tmp_score = get_score(pos, map, pie, adv);

            if (tmp_score.enemy_dist != 0 && tmp_score.decision < score.decision)
            {
                score = tmp_score;
            }
        }
        if (SHOW_FIND_DEBUG)
            find_debug(map, pos, res, score.decision);
        //debug_print(ft_itoa(pos), 0, 1);
        //debug_print(" ", 0, 0);
        //debug_print(ft_itoa(score.pos), 1, 1);
    }
    if (score.pos == -1)
    {
        score = tmp_score;
    }
    if (SHOW_FIND_DEBUG)
    {
        debug_print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", 1, 0);
        debug_print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", 1, 0);
        debug_print(">>>>>>>>>>>>>>>>", 1, 0);
    }
    return (score);
}