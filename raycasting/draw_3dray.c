#include "raycaster.h"

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
	
	while (r < 30)
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
		r++;
		ra += 2 * DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}
