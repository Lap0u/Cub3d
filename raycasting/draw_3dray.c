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
	// st = (app->wall.bpp / 8) * (x + y * app->x);
	// get_pixel_col(&app->north, x, y);
	return (new);
}

void	draw_rays_3d(t_app *app)
{
	int	i, r, mx, my, mp, dof;
	float	rx, ry, ra, xo, hx, hy, vx, vy, yo, a_tan, n_tan, x, y, hdist, vdist, dis_ta;
	extern int map_x;
	extern int map_y;
	extern int map[];
	
	ra = app->ray.game_state.pa - DR * 30 * 8;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	r = 0;
	i = 0;
	mp = 0;

	/*draw floor and ceiling*/
	int color;
	for (int k = app->x / 2; k < app->x; k++)
	{
		for (int l = 0; l < app->y; l++)
		{
			if (l < app->y / 2)
				color = 0x000000FF;
			else
				color = 0x00FF0000;
			my_mlx_pixel_put(&(app->img), k, l, color);
		}
	}
	while (r < 60 * 8)
	{
		// Check Horizontal Lines
		dof = 0; // nbr des cases que l'on regarde
		mp = 0;
		a_tan = -1 / tan(ra);
		if (ra > PI) //looking down
		{
			ry = (((int)y >> 6)<< 6) - 0.0001;
			rx = (y - ry) * a_tan + x;
			yo = -64;
			xo = (-1 * yo) * a_tan;
		}
		if (ra < PI) //looking up
		{
			ry = (((int)y >> 6)<< 6) + 64;
			rx = (y - ry) * a_tan + x;
			yo = 64;
			xo = (-1 * yo) * a_tan;
			printf("ra = %f, ry = %f, rx = %f, xo = %f\n", ra, ry, rx, xo);
		}
		if ((ra == 0) || (ra == PI)) //looking straight felt or right
		{
			rx = x;
			ry = y;
			dof = 8;
		}
		/*print la map*/
		// for (int i =0; i < 64;i++)
		// {
		// 	if (i % 8 == 0)
		// 		printf("\n");
		// 	printf("%d", map[i]);
		// }
		while (dof < 8)
		{
			mp = 0;
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < (map_x * map_y) && (map[mp] == 1)) // hit wall
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;  
				dof += 1; // next line
				mp = 100;
			}
			// printf("dof = %d\n", dof);
		}
		// printf("%d : case\n", map[mp]);
		hx = rx;
		hy = ry;
		hdist = sqrt(pow(rx-x, 2) + (pow(ry-y, 2)));
		// printf("%d : mp_hor, hdist = %f, my = %d, map_x = %d, int mx = %d\n", mp, hdist, my, map_x, mx);
		/*check vertical line*/
		dof = 0;
		n_tan = -tan(ra);
		if (ra > PI2 && ra < PI3) //looking left
		{
			rx = (((int)x >> 6)<< 6) - 0.0001;
			ry = (x - rx) * n_tan + y;
			xo = -64;
			yo = -xo * n_tan;
		}
		if (ra < PI2 || ra > PI3) //looking right
		{
			rx = (((int)x >> 6)<< 6) + 64;
			ry = (x - rx) * n_tan + y;
			xo = 64;
			yo = -xo * n_tan;
		}
		if ((ra == 0) || (ra == PI)) //looking straight up or down
		{
			rx = x;
			ry = y;
			dof = 8;
			printf("nope\n");
		}
		/*print la map*/
		// for (int i =0; i < 64;i++)
		// {
		// 	if (i % 8 == 0)
		// 		printf("\n");
		// 	printf("%d", map[i]);
		// }
		
		while (dof < 8)
		{
			mp = 0;
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < (map_x * map_y) && (map[mp] == 1)) // hit wall
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;  
				dof += 1; // next line
				mp = 100;
			}
		}
		vx = rx;
		vy = ry;
		printf("%f vx\n", vx);
		// printf("%d : mp_vert\n", mp);
		// printf("pox sp : %f %f\n", x, y);
		// // printf("%d : case\n", map[mp]);
		vdist = sqrt(pow(rx-x, 2) + (pow(ry-y, 2)));
		int i = 0;
		while (i < (int)vdist && i < (int)hdist) /*affiche plus petite distance entre vertical et horizontal*/
		{
			my_mlx_pixel_put(&(app->img), (x) + (i * cos(ra)), 
			(y) + (i * sin(ra)), 0x003AB0A7);
			i++;
		}
		/*draw 3D*/
		// printf("rx1 v h = %f %f %f\t", rx, vx, hx);
		int mod;
		if (vdist < hdist)
		{
			dis_ta = vdist;
			rx = vx;
			ry = vy;
			if (ra > PI2 && ra < PI3)
				mod = 0; //look left
			else
				mod = 1; //look right
		}
		else
		{
			dis_ta = hdist;
			rx = hx;
			ry = hy;
			// printf("%d rboucle?\n", r);
			if (ra > PI)//look north
				mod = 3;
			else
				mod = 2;//look south
		}
		printf("%d %f ter\n", mod, rx);
		// printf("rx2 v h = %f %f %f\t", rx, vx, hx);
		app->x;//
		app->y;//
		float lineH, ca;

		//fix fish-eye*/
		ca = app->sp.game_state.pa -ra;
		if (ca < 0)
			ca += (2* PI);
		if (ca > 2*PI)
			ca -= (2*PI);
		dis_ta = dis_ta * cos(ca);
		//
		lineH = (map_x * map_y * (app->x / 2)) / dis_ta;
		float saveH = lineH;
		if (lineH > ((app->x / 2)))
			lineH = ((app->x/ 2));
		i = 0;
		printf("%f : lineH\t%f : dis_ta\n", lineH, dis_ta);
		// while (i < lineH)//old 
		// {	
		// 	float j =  0;
		// 	while (j < 8) // j simule la largeur de 8 pixel
		// 	{
		// 		my_mlx_pixel_put(&(app->img), ((j + r * 8 + app->x / 2)), 
		// 		i + (app->y / 2 - lineH / 2), 0x00FFFFFF);
		// 		j+=0.1;
		// 	}
		// 	i++;
		// }
		while (i < lineH) //new
		{	
			int j =  0;
			while (j < 1) // j simule la largeur de 8 pixel
			{
				// draw_img_at_pos(app, &(app->north), ((j + r * 8 + app->x / 2)), i + (app->y / 2 - lineH / 2));
				my_mlx_pixel_put(&(app->img), ((j + r + app->x / 2)), 
				i + (app->y / 2 - lineH / 2), get_color(app, (j + r * 8 + app->x / 2), i + (app->y / 2 - lineH / 2), saveH,  rx , i, r, mod));
				j++;
			}
			i++;
		}
		/*loop for all rays*/
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		r++;
	}
}
