#include "raycaster.h"

void	draw_rays_3d(t_app *app)
{
	int	i, r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, a_tan, n_tan, x, y, hdist, vdist;
	extern int map_x;
	extern int map_y;
	extern int map[];
	
	ra = app->sp.game_state.pa;
	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	r = 0;
	i = 0;
	while (r < 1)
	{
		// Check Horizontal Lines
		dof = 0;
		a_tan = -1 / tan(app->sp.game_state.pa);
		if (app->sp.game_state.pa > PI) //looking down
		{
			ry = (((int)app->sp.game_state.player_y >> 6)<< 6) - 0.0001;
			rx = (app->sp.game_state.player_y - ry) * a_tan + app->sp.game_state.player_x;
			yo = -64;
			xo = -yo * a_tan;
		}
		if (app->sp.game_state.pa < PI) //looking up
		{
			ry = (((int)app->sp.game_state.player_y >> 6)<< 6) + 64;
			rx = (app->sp.game_state.player_y - ry) * a_tan + app->sp.game_state.player_x;
			yo = 64;
			xo = -yo * a_tan;
		}
		if ((app->sp.game_state.pa == 0) || (app->sp.game_state.pa == PI)) //looking straight felt or right
		{
			rx = app->sp.game_state.player_x;
			ry = app->sp.game_state.player_y;
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
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && (map[mp] == 1)) // hit wall
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;  
				dof += 1; // next line
			}
			// printf("dof = %d\n", dof);
		}
		printf("%d : mp_hor\n", mp);
		// printf("%d : case\n", map[mp]);
		hdist = sqrt(pow(rx-x, 2) + (pow(ry-y, 2)));
		/*check vertical line*/
		dof = 0;
		n_tan = -tan(ra);
		if (ra > PI2 && ra < PI3) //looking left
		{
			rx = (((int)app->sp.game_state.player_x >> 6)<< 6) - 0.0001;
			ry = (app->sp.game_state.player_x - rx) * n_tan + app->sp.game_state.player_y;
			xo = -64;
			yo = -xo * n_tan;
		}
		if (ra < PI2 || ra > PI3) //looking right
		{
			rx = (((int)app->sp.game_state.player_x >> 6)<< 6) + 64;
			ry = (app->sp.game_state.player_x - rx) * n_tan + app->sp.game_state.player_y;
			xo = 64;
			yo = -xo * n_tan;
		}
		if ((app->sp.game_state.pa == 0) || (app->sp.game_state.pa == PI)) //looking straight up or down
		{
			rx = app->sp.game_state.player_x;
			ry = app->sp.game_state.player_y;
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
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * map_x + mx;
			if (mp > 0 && mp < map_x * map_y && (map[mp] == 1)) // hit wall
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;  
				dof += 1; // next line
			}
		}
		printf("%d : mp_vert\n", mp);
		// printf("%d : case\n", map[mp]);
		vdist = sqrt(pow(rx-x, 2) + (pow(ry-y, 2)));
		int i = 0;
		while (i < vdist && i < hdist) /*affiche plus petite distance entre vertical et horizontal*/
		{
			my_mlx_pixel_put(&(app->img), (x * 10 + 5) + (i * cos(app->ray.game_state.pa)/2), 
			(y * 10 + 5) + (i * sin(app->ray.game_state.pa)/2), 0x00FFFFFF);
			i++;
		}
		r++;
	}
}
