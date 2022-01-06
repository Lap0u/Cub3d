#include "raycaster.h"

void	draw_img_at_pos(t_app *app, t_data *txr, int x, int y)
{
	int	st;
	int	bpp;

	bpp = txr->bpp / 8;
	st = (txr->bpp / 8) * (x + y * app->x);
	draw_img_at_pos_body(app, txr, st, bpp);
}

void	draw_img_at_pos_body(t_app *app, t_data *txr, int st, int bpp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < txr->h)
	{
		j = 0;
		while (j < txr->w)
		{
			if (check_pixel(txr, i, j))
			{
				k = 0;
				while (k < 3)
					bit_copy(app->image_addr + st + i * app->x * bpp + j * bpp,
						txr->addr + bpp * txr->w * i + j * bpp, k++);
			}
			j++;
		}
		i++;
	}
}

int	check_pixel(t_data *txr, int line, int col)
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
