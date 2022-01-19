#include "raycaster.h"

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
	unsigned char	temp_r;
	unsigned char	temp_g;
	unsigned char	temp_b;
	int				color;

	color = 0;
	temp_r = app->ceil_col.red;
	temp_g = app->ceil_col.green;
	temp_b = app->ceil_col.blue;
	if (!(app->bool_map == 0 || x < MARGIN * 2 || y < MARGIN
	|| x > RES_X - MARGIN * 2 || y > RES_Y - MARGIN))
	{
		temp_r *= OPACITY;
		temp_g *= OPACITY;
		temp_b *= OPACITY;
	}
	color |= temp_r << 16;
	color |= temp_g << 8;
	color |= temp_b;
	return (color);
}

int	color_floor(t_app *app, int x, int y)
{
	unsigned char	temp_r;
	unsigned char	temp_g;
	unsigned char	temp_b;
	int				color;

	color = 0;
	temp_r = app->flo_col.red;
	temp_g = app->flo_col.green;
	temp_b = app->flo_col.blue;
	if (!(app->bool_map == 0 || x < MARGIN * 2 || y < MARGIN
	|| x > RES_X - MARGIN * 2 || y > RES_Y - MARGIN))
	{
		temp_r *= OPACITY;
		temp_g *= OPACITY;
		temp_b *= OPACITY;
	}
	color |= temp_r << 16;
	color |= temp_g << 8;
	color |= temp_b;
	return (color);
}

int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod)
{
	int		st;
	int		bpp;
	t_rgb	color;
	unsigned int	ind;
	int		new;

	new = 0;
	ind = app->dr.mod;
	if (scale > RES_Y)
		i = i + (scale / 2 -  RES_Y / 2);
	i = i * 64 / scale;
	x = rx % 64;
	bpp = app->txr[ind].bpp / 8;
	color.blue = app->txr[ind].addr[i * app->txr[ind].size + x * bpp + ind ];
	color.green = app->txr[ind].addr[i * app->txr[ind].size + x * bpp  + 1];
	color.red = app->txr[ind].addr[i * app->txr[ind].size + x * bpp  + 2];
	color.op = app->txr[ind].addr[i * app->txr[ind].size + x * bpp + 3];
	opacity(app, y, x, &color);
	new |= color.op << 24;
	new |= color.red << 16;
	new |= color.green << 8;
	new |= color.blue;
	return (new);
}