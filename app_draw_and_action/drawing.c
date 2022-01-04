/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 22:41:26 by okushnir          #+#    #+#             */
/*   Updated: 2022/01/02 22:41:28 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	*bit_copy(void *dst, const void *src, int j)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (!dst && !src)
		return ((void *)0);
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	*(p_dst + j) = *(p_src + j);
	return (dst);
}

void	drow_map_body(t_app *app, char c, int j, int i)
{
	if (c == '1')
		draw_img_at_pos(app, &(app->sp[0]), 48 * j, 48 * i);
	else if (c == '0')
		draw_img_at_pos(app, &(app->sp[1]), 48 * j, 48 * i);
	else if (c == 'P')
	{
		draw_img_at_pos(app, &(app->sp[1]), 48 * j, 48 * i);
		player_position_init(app, j, i);
	}
	else if (c == 'C')
	{
		if (app->flag == 0)
			app->total_col++;
		draw_img_at_pos(app, &(app->sp[1]), 48 * j, 48 * i);
		draw_img_at_pos(app, &(app->sp[2]), 48 * j, 48 * i);
	}
	else if (c == 'E')
	{
		draw_img_at_pos(app, &(app->sp[1]), 48 * j, 48 * i);
		draw_img_at_pos(app, &(app->sp[4]), 48 * j, 48 * i);
	}
}

void	drow_map(t_app *app)
{
	t_map	*p;
	int		len;
	int		i;
	int		j;

	i = 0;
	p = app->carte;
	len = 13; //change
	while (i < len)
	{
		j = 0;
		while (j < 33)
		{
			drow_map_body(app, p->line[j], j, i);
			j++;
		}
		p = p->next;
		i++;
	}
	app->flag = 1;
}

int	check_pixel(t_texture *txr, int line, int col)
{
	int	bpp;

	bpp = txr->bpp / 8;
	if ((txr->addr[line * txr->size + col * bpp + 0] != 0)
		&& (txr->addr[line * txr->size + col * bpp + 1] != 0)
		&& (txr->addr[line * txr->size + col * bpp + 2] != 0)
		&& (txr->addr[line * txr->size + col * bpp + 3] != -1))
		return (1);
	else
		return (0);
}

void	draw_img_at_pos_body(t_app *app, t_texture *txr, int st, int bpp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < txr->sp_y)
	{
		j = 0;
		while (j < txr->sp_y)
		{
			if (check_pixel(txr, i, j))
			{
				k = 0;
				while (k < 3)
					bit_copy(app->image_addr + st + i * app->x * bpp + j * bpp,
						txr->addr + bpp * txr->sp_x * i + j * bpp, k++);
			}
			j++;
		}
		i++;
	}
}

void	draw_img_at_pos(t_app *app, t_texture *txr, int x, int y)
{
	int	st;
	int	bpp;

	bpp = txr->bpp / 8;
	st = (txr->bpp / 8) * (x + y * app->x);
	draw_img_at_pos_body(app, txr, st, bpp);
}
