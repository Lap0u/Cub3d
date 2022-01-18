#include "raycaster.h"

int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod)
{
	int		st;
	int		bpp;
	unsigned char	color;
	unsigned char	color1;
	unsigned char	color2;
	unsigned char	color3;
	unsigned int	ind;
	int		new;

	// fprintf(stderr, "deb1 i scale x rx mod \t %d %d %d %d %d\n", i, scale, x, rx, mod);
	new = 0;
	ind = app->dr.mod;
	// x %= 64;
	if (scale > app->y)
		i = i + (scale / 2 -  app->y / 2);
	i = i * 64 / scale;  //remplacer les 2 64 pour le scaling en fonction de la taille de l'image
	x = rx % 64;//remplacer les 2 64 pour le scaling en fonction de la taille de l'image
	// fprintf(stderr, "deb2 i scale x rx mod \t %d %d %d %d %d\n", i, scale, x, rx, mod);
	bpp = app->txr[0].bpp / 8;
	color = app->txr[0].addr[i * app->txr[0].size + x * bpp + 0 ];
	color1 = app->txr[0].addr[i * app->txr[0].size + x * bpp  + 1];
	color2 = app->txr[0].addr[i * app->txr[0].size + x * bpp  + 2];
	color3 = app->txr[0].addr[i * app->txr[0].size + x * bpp + 3];


	
	new |= color3 << 24;
	new |= color2 << 16;
	new |= color1 << 8;
	new |= color;

	
	// printf("color: %d, color1: %d, color2: %d, color3: %d\n", color, color1, color2, color3);
	// bpp = app->wall.bpp / 8;
	// st = (app->wall.bpp / 8) * (x + y * RES_X);
	// get_pixel_col(&app->north, x, y);
	return (new);
}