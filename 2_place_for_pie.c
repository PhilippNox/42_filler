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
            if (tmp == 'y' || tmp == 'z')
                continue;
            score += tmp - 48;
        }
    }
    return (score);
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
        if (res == 1)
            out = pos;
    }
    if (SHOW_FIND_DEBUG)
        debug_print(">>>>>>>>", 1, 0);
    return (out);
}