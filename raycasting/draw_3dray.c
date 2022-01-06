#include "raycaster.h"

void	draw_rays_3d(t_app *app)
{
	int	i, r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo, a_tan, x, y;
	extern int map_x;
	extern int map_y;
	extern int map[];

	x = app->sp.game_state.player_x;
	y = app->sp.game_state.player_y;
	r = 0;
	i = 0;
	while (r < 1)
	{
		// Check Horizontal Lines
		dof = 0;
		a_tan = -1 / tan(app->ray.game_state.pa);
		if (app->ray.game_state.pa > PI) //looking up
		{
			ry = (((int)app->sp.game_state.player_y >> 6)<< 6) - 0.0001;
			rx = (app->sp.game_state.player_y - ry) * a_tan + app->sp.game_state.player_x;
			yo = -64;
			xo = -yo * a_tan;
		}
		if (app->ray.game_state.pa < PI) //looking down
		{
			ry = (((int)app->sp.game_state.player_y >> 6)<< 6) + 64;
			rx = (app->sp.game_state.player_y - ry) * a_tan + app->sp.game_state.player_x;
			yo = 64;
			xo = -yo * a_tan;
		}
		if ((app->ray.game_state.pa == 0) || (app->ray.game_state.pa = PI)) //looking straight felt or right
		{
			rx = app->sp.game_state.player_x;
			ry = app->sp.game_state.player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * map_x + mx;
			if ((mp < map_x * map_y) && (map[mp] == 1)) // hit wall
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1; // next line
				my_mlx_pixel_put(&(app->img), (rx * 10 + 5) + (i * cos(app->ray.game_state.pa)/2),
				(ry * 10 + 5) + (i * sin(app->ray.game_state.pa)/2), 0x00FFFF01);

			}
		}
	}
}
