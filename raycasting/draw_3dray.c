#include "raycaster.h"

char	*copy_size(char *str, int size)
{
	int		i;
	char	*temp;

	temp = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	
}

int	get_pixel_col(t_data *txr, int line, int col)
{
	int		bpp;
	char	*str;

	bpp = txr->bpp / 8;
	str = copy_size(&txr->addr[line * txr->size + col * bpp + 0], 10);
	free(str);
	return (0x00FFFFFF);
}

int		get_color(t_app *app, int x, int y)
{
	t_data	txr;
	int		st;
	int		bpp;

	txr.img = mlx_xpm_file_to_image(app->mlx, "../textures/north.xpm", &txr.w, &txr.h);////pb ici
	txr.addr = mlx_get_data_addr(txr.img, &txr.bpp, &txr.size, &txr.endian);///// ou la
	bpp = txr.bpp / 8;
	st = (txr.bpp / 8) * (x + y * app->x);
	// return (get_pixel_col(&txr, x, y));
	return (0x00FFFFFF);
}

void	draw_rays_3d(t_app *app)
{
	int	i, r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, a_tan, n_tan, x, y, hdist, vdist, dis_ta;
	extern int map_x;
	extern int map_y;
	extern int map[];
	
	ra = app->ray.game_state.pa - DR * 30;
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
	while (r < 60)
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
		hdist = sqrt(pow(rx-x, 2) + (pow(ry-y, 2)));
		printf("%d : mp_hor, hdist = %f, my = %d, map_x = %d, int mx = %d\n", mp, hdist, my, map_x, mx);
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
		printf("%d : mp_vert\n", mp);
		printf("pox sp : %f %f\n", x, y);
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
		if (vdist < hdist)
			dis_ta = vdist;
		else
			dis_ta = hdist;
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
			float j =  0;
			while (j < 8) // j simule la largeur de 8 pixel
			{
				my_mlx_pixel_put(&(app->img), ((j + r * 8 + app->x / 2)), 
				i + (app->y / 2 - lineH / 2), get_color(app, (j + r * 8 + app->x / 2), i + (app->y / 2 - lineH / 2)));
				j+=0.1;
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