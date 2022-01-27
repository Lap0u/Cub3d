#include "../cub3d.h"
// #include "raycaster.h"

void	opacity(t_app *app, int y, int x, t_rgb *color)
{
	if (!(app->bool_map == 0 || x < MARGIN * 2 || y < MARGIN
	|| x > RES_X - MARGIN * 2 || y > RES_Y - MARGIN))
	{
		color->red  *= OPACITY;
		color->green *= OPACITY;
		color->blue *= OPACITY;
		color->op *= OPACITY;
	}
}

int	color_ceil(t_app *app, int x, int y)
{
	t_rgb	color;
	int		new;

	new = 0;
	color.red = app->ceil_col.red;
	color.green = app->ceil_col.green;
	color.blue = app->ceil_col.blue;
	opacity(app, y, x, &color);
	new |= color.op << 24;
	new |= color.red << 16;
	new |= color.green << 8;
	new |= color.blue;
	return (new);
}

int	color_floor(t_app *app, int x, int y)
{
	t_rgb	color;
	int		new;

	new = 0;
	color.red = app->flo_col.red;
	color.green = app->flo_col.green;
	color.blue = app->flo_col.blue;
	opacity(app, y, x, &color);
	new |= color.op << 24;
	new |= color.red << 16;
	new |= color.green << 8;
	new |= color.blue;
	return (new);
}

int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod)
{
	int		st;
	int		bpp;
	t_rgb	color;
	unsigned int	ind;
	int		new;
	int		save_x;
	new = 0;
	ind = app->dr.mod;
	if (scale > RES_Y)
		i = i + (scale / 2 -  RES_Y / 2);
	i = i * 64 / scale;
	save_x = x;
	x = rx % 64;
	bpp = app->txr[ind].bpp / 8;
	color.blue = app->txr[ind].addr[i * app->txr[ind].size + x * bpp];
	color.green = app->txr[ind].addr[i * app->txr[ind].size + x * bpp  + 1];
	color.red = app->txr[ind].addr[i * app->txr[ind].size + x * bpp  + 2];
	color.op = app->txr[ind].addr[i * app->txr[ind].size + x * bpp + 3];
	opacity(app, y, save_x, &color);
	new |= color.op << 24;
	new |= color.red << 16;
	new |= color.green << 8;
	new |= color.blue;
	return (new);
}