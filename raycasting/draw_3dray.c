#include "raycaster.h"

int	get_pixel_col(t_data *txr, int line, int col)
{
	// int		bpp;
	// char	*str;

	// bpp = txr->bpp / 8;
	// str = copy_size(&txr->addr[line * txr->size + col * bpp + 0], bpp, 10);
	// if (txr->addr[line * txr->size + col * bpp + 0] != 0)
	// 	printf("lu");
	// free(str);
	return (0x00FFFFFF);
}

int		get_color(t_app *app, int x, int y, int scale, int rx, int i, int r, int mod)
{
	int		st;
	int		bpp;
	unsigned char	color;
	unsigned char	color1;
	unsigned char	color2;
	unsigned char	color3;
	int		new;

	// fprintf(stderr, "deb1 i scale x rx mod \t %d %d %d %d %d\n", i, scale, x, rx, mod);
	new = 0;
	// x %= 64;
	if (scale > RES_Y)
		i = i + (scale / 2 - RES_Y / 2);
	i = i * 64 / scale;
	x = rx % 64;
	// fprintf(stderr, "deb2 i scale x rx mod \t %d %d %d %d %d\n", i, scale, x, rx, mod);
	if (mod == 3)
	{
		bpp = app->north.bpp / 8;
		color = app->north.addr[x * app->north.size + i * bpp + 0 ];
		color1 = app->north.addr[x * app->north.size + i * bpp  + 1];
		color2 = app->north.addr[x * app->north.size + i * bpp  + 2];
		color3 = app->north.addr[x * app->north.size + i * bpp + 3];
	}
	else if (mod == 2)
	{
		bpp = app->south.bpp / 8;
		color = app->south.addr[x * app->south.size + i * bpp + 0 ];
		color1 = app->south.addr[x * app->south.size + i * bpp  + 1];
		color2 = app->south.addr[x * app->south.size + i * bpp  + 2];
		color3 = app->south.addr[x * app->south.size + i * bpp + 3];
	}
	else if (mod == 1)
	{
		bpp = app->east.bpp / 8;
		color = app->east.addr[x * app->east.size + i * bpp + 0 ];
		color1 = app->east.addr[x * app->east.size + i * bpp  + 1];
		color2 = app->east.addr[x * app->east.size + i * bpp  + 2];
		color3 = app->east.addr[x * app->east.size + i * bpp + 3];
	}
	else if (mod == 0)
	{
		bpp = app->west.bpp / 8;
		color = app->west.addr[x * app->west.size + i * bpp + 0 ];
		color1 = app->west.addr[x * app->west.size + i * bpp  + 1];
		color2 = app->west.addr[x * app->west.size + i * bpp  + 2];
		color3 = app->west.addr[x * app->west.size + i * bpp + 3];
	}
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

void	draw_floor_ceil(t_app *app)
{
	int	color;
	int	k;
	int	l;

	k = 0;
	while (k < RES_X)
	{
		l = 0;
		while (l < RES_Y)
		{
			if (l < RES_Y / 2)
				color = 0x000000FF;
			else
				color = 0x00FF0000;
			if (k >= 64 * SCALING || l >= 64 * SCALING)//laisse la place pour la map en haut a gauche, change valeur pour agrandir / retraicir / faire un scaling
				my_mlx_pixel_put(&(app->img), k, l, color);
			l++;
		}
		k++;
	}
}

void	draw_rays_3d(t_app *app)
{
	t_draw rays;
	extern int map_x;
	extern int map_y;
	extern int map[];
	
	rays.ra =app->ray.game_state.pa - DR * SCALING;
	if (rays.ra < 0)
		rays.ra += 2 * PI;
	if (rays.ra > 2 * PI)
		rays.ra -= 2 * PI;
	rays.x = app->sp.game_state.player_x;
	rays.y = app->sp.game_state.player_y;
	rays.r = 0;
	rays.i = 0;
	rays.mp = 0;

	draw_floor_ceil(app);
	while (rays.r < RES_X)
	{
		// Check Horizontal Lines
		rays.dof = 0; // nbr des cases que l'on regarde
		rays.mp = 0;
		rays.a_tan = -1 / tan(rays.ra);
		if (rays.ra > PI) //looking down
		{
			rays.ry = (((int)rays.y >> 6)<< 6) - 0.0001;
			rays.rx = (rays.y - rays.ry) * rays.a_tan + rays.x;
			rays.yo = -64;
			rays.xo = (-1 * rays.yo) * rays.a_tan;
		}
		if (rays.ra < PI) //looking up
		{
			rays.ry = (((int)rays.y >> 6)<< 6) + 64;
			rays.rx = (rays.y - rays.ry) * rays.a_tan + rays.x;
			rays.yo = 64;
			rays.xo = (-1 * rays.yo) * rays.a_tan;
			printf("rays.ra = %f, ry = %f, rx = %f, xo = %f\n", rays.ra, rays.ry, rays.rx, rays.xo);
		}
		if ((rays.ra == 0) || (rays.ra == PI)) //looking straight felt or right
		{
			rays.rx = rays.x;
			rays.ry = rays.y;
			rays.dof = 8;
		}
		while (rays.dof < 8)
		{
			rays.mp = 0;
			rays.mx = (int)(rays.rx) >> 6;
			rays.my = (int)(rays.ry) >> 6;
			rays.mp = rays.my * map_x + rays.mx;
			if (rays.mp > 0 && rays.mp < (map_x * map_y) && (map[rays.mp] == 1)) // hit wall
			{
				rays.dof = 8;
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;  
				rays.dof += 1; // next line
				rays.mp = 100;
			}
			// printf("dof = %d\n", dof);
		}
		// printf("%d : case\n", map[mp]);
		rays.hx = rays.rx;
		rays.hy = rays.ry;
		rays.hdist = sqrt(pow(rays.rx-rays.x, 2) + (pow(rays.ry-rays.y, 2)));
		// printf("%d : mp_hor, hdist = %f, my = %d, map_x = %d, int mx = %d\n", mp, hdist, my, map_x, mx);
		/*check vertical line*/
		rays.dof = 0;
		rays.n_tan = -tan(rays.ra);
		if (rays.ra > PI2 && rays.ra < PI3) //looking left
		{
			rays.rx = (((int)rays.x >> 6)<< 6) - 0.0001;
			rays.ry = (rays.x - rays.rx) * rays.n_tan + rays.y;
			rays.xo = -64;
			rays.yo = -1 * rays.xo * rays.n_tan;
		}
		if (rays.ra < PI2 || rays.ra > PI3) //looking right
		{
			rays.rx = (((int)rays.x >> 6)<< 6) + 64;
			rays.ry = (rays.x - rays.rx) * rays.n_tan + rays.y;
			rays.xo = 64;
			rays.yo = -1 * rays.xo * rays.n_tan;
		}
		if ((rays.ra == 0) || (rays.ra == PI)) //looking strays.raight up or down
		{
			rays.rx = rays.x;
			rays.ry = rays.y;
			rays.dof = 8;
		}		
		while (rays.dof < 8)
		{
			rays.mp = 0;
			rays.mx = (int)(rays.rx) >> 6;
			rays.my = (int)(rays.ry) >> 6;
			rays.mp = rays.my * map_x + rays.mx;
			if (rays.mp > 0 && rays.mp < (map_x * map_y) && (map[rays.mp] == 1)) // hit wall
			{
				rays.dof = 8;
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;  
				rays.dof += 1; // next line
				rays.mp = 100;
			}
		}
		rays.vx = rays.rx;
		rays.vy = rays.ry;
		printf("%f vx\n", rays.vx);
		rays.vdist = sqrt(pow(rays.rx - rays.x, 2) + (pow(rays.ry - rays.y, 2)));
		int mod;
		if (rays.vdist < rays.hdist)
		{
			rays.dis_ta = rays.vdist;
			rays.rx = rays.vy;
			rays.ry = rays.vy;
			if (rays.ra > PI2 && rays.ra < PI3)
				rays.mod = 0; //look left
			else
				rays.mod = 1; //look right
		}
		else
		{
			rays.dis_ta = rays.hdist;
			rays.rx = rays.hx;
			rays.ry = rays.hy;
			// printf("%d rboucle?\n", r);
			if (rays.ra > PI)//look north
				rays.mod = 3;
			else
				rays.mod = 2;//look south
		}
		printf("%d %f ter\n", rays.mod, rays.rx);
		// printf("rx2 v h = %f %f %f\t", rx, vx, hx);
		RES_X;//
		RES_Y;//

		//fix fish-eye*/
		rays.ca = app->sp.game_state.pa -rays.ra;
		if (rays.ca < 0)
			rays.ca += (2* PI);
		if (rays.ca > 2*PI)
			rays.ca -= (2*PI);
		rays.dis_ta = rays.dis_ta * cos(rays.ca);
		//
		draw_walls(app, rays);
		int i = 0;
		while (i < (int)rays.vdist && i < (int)rays.hdist) /*affiche plus petite distance entre vertical et horizontal*/
		{
			my_mlx_pixel_put(&(app->img), ((rays.x) + (i * cos(rays.ra))) / SCALING, 
			((rays.y) + (i * sin(rays.ra))) / SCALING, 0x003AB0A7);
			i++;
		}
		rays.ra += DR;
		if (rays.ra < 0)
			rays.ra += 2 * PI;
		if (rays.ra > 2 * PI)
			rays.ra -= 2 * PI;
		rays.r++;
	}
}

void	draw_walls(t_app *app, t_draw rays)
{
	int	i;
	int	j;
	extern int map_x;
	extern int map_y;

	rays.lineH = (map_x * map_y * (RES_Y)) / rays.dis_ta;
	rays.saveH = rays.lineH;
	if (rays.lineH > ((RES_Y)))
		rays.lineH = ((RES_Y));
	i = 0;
	printf("%f : lineH\t%f : dis_ta\n", rays.lineH, rays.dis_ta);
	while (i < rays.lineH) //dessine les murs en 3D
	{	
		j =  0;
		while (j < 1) // j simule la largeur de 8 pixel
		{
			// drays.raw_img_at_pos(app, &(app->north), ((j + r * 8 + RES_X / 2)), i + (RES_Y / 2 - lineH / 2));
			my_mlx_pixel_put(&(app->img), ((j + rays.r + RES_X)), 
			rays.i + (RES_Y / 2 - rays.lineH / 2), get_color(app, (j + rays.r * 8 + RES_X / 2), rays.i + (RES_Y / 2 - rays.lineH / 2), rays.saveH,  rays.rx , rays.i, rays.r, rays.mod));
			j++;
		}
		i++;
	}
}
	