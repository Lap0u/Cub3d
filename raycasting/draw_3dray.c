#include "raycaster.h"

void	prepa_init_ray(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->ra = app->ray.game_state.pa - DR * 30;
	if (dr->ra < 0)
		dr->ra += 2 * PI;
	if (dr->ra > 2 * PI)
		dr->ra -= 2 * PI;
	dr->x = app->sp.game_state.player_x;
	dr->y = app->sp.game_state.player_y;
	dr->r = 0;
	dr->i = 0;
	dr->mp = 0;
}

void	check_hor_down(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->ry = (((int)dr->y >> 6)<< 6) - 0.0001;
	dr->rx = (dr->y - dr->ry) * dr->a_tan + dr->x;
	dr->yo = -64;
	dr->xo = (-1 * dr->yo) * dr->a_tan;
}

void	check_hor_up(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->ry = (((int)dr->y >> 6)<< 6) + 64;
	dr->rx = (dr->y - dr->ry) * dr->a_tan + dr->x;
	dr->yo = 64;
	dr->xo = (-1 * dr->yo) * dr->a_tan;
}

void	check_hor_left_right(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->rx = dr->x;
	dr->ry = dr->y;
	dr->dof = 8;
}

void	check_hor_action(t_app *app)
{
	t_draw	*dr;
	extern	int map_x;
	extern	int map_y;
	extern	int map[];

	dr = &(app->dr);
	dr->mp = 0;
	dr->mx = (int)(dr->rx) >> 6;
	dr->my = (int)(dr->ry) >> 6;
	dr->mp = dr->my * map_x + dr->mx;
	if (dr->mp > 0 && dr->mp < (map_x * map_y) && (map[dr->mp] == 1)) // hit wall
	{
		dr->dof = 8;
	}
	else
	{
		dr->rx += dr->xo;
		dr->ry += dr->yo;  
		dr->dof += 1; // next line
		dr->mp = 100;
	}
}

void	check_horizont_line(t_app *app)
{
	t_draw	*dr;
	extern	int map_x;
	extern	int map_y;
	extern	int map[];

	dr = &(app->dr);
	dr->dof = 0; // nbr des cases que l'on a deja checke
	dr->mp = 0; // numero de case  que l'on check
	dr->a_tan = -1 / tan(dr->ra);
	if (dr->ra > PI) //looking down
		check_hor_down(app);
	if (dr->ra < PI) //looking up
		check_hor_up(app);
	if ((dr->ra == 0) || (dr->ra == PI)) //looking straight felt or right
		check_hor_left_right(app);
	while (dr->dof < 8)
		check_hor_action(app);
	dr->hx = dr->rx;
	dr->hy = dr->ry;
	dr->hdist = sqrt(pow(dr->rx - dr->x, 2) + (pow(dr->ry - dr->y, 2)));
}

void	check_vert_left(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->rx = (((int)dr->x >> 6)<< 6) - 0.0001;
	dr->ry = (dr->x - dr->rx) * dr->n_tan + dr->y;
	dr->xo = -64;
	dr->yo = -1  * dr->xo * dr->n_tan;
}

void	check_vert_right(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->rx = (((int)dr->x >> 6)<< 6) + 64;
	dr->ry = (dr->x - dr->rx) * dr->n_tan + dr->y;
	dr->xo = 64;
	dr->yo = -1 * dr->xo * dr->n_tan;
}

void	check_vert_down_up(t_app *app)
{
	t_draw	*dr;

	dr = &(app->dr);
	dr->rx = dr->x;
	dr->ry = dr->y;
	dr->dof = 8;
}

void	check_vert_action(t_app *app)
{
	t_draw	*dr;
	extern	int map_x;
	extern	int map_y;
	extern	int map[];

	dr = &(app->dr);
	dr->mp = 0;
	dr->mx = (int)(dr->rx) >> 6;
	dr->my = (int)(dr->ry) >> 6;
	dr->mp = dr->my * map_x + dr->mx;
	if (dr->mp > 0 && dr->mp < (map_x * map_y) && (map[dr->mp] == 1)) // hit wall
	{
		dr->dof = 8;
	}
	else
	{
		dr->rx += dr->xo;
		dr->ry += dr->yo;  
		dr->dof += 1; // next line
		dr->mp = 100;
	}
}

void	check_vertical_line(t_app *app)
{
	t_draw	*dr;
	extern	int map_x;
	extern	int map_y;
	extern	int map[];

	dr = &(app->dr);
	dr->dof = 0;
	dr->n_tan = -1 * tan(dr->ra);
	if (dr->ra > PI2 && dr->ra < PI3) //looking left
		check_vert_left(app);
	if (dr->ra < PI2 || dr->ra > PI3) //looking right
		check_vert_right(app);
	if ((dr->ra == 0) || (dr->ra == PI)) //looking straight up or down
		check_vert_down_up(app);		
	while (dr->dof < 8)
		check_vert_action(app);
	dr->vx = dr->rx;
	dr->vy = dr->ry;
	dr->vdist = sqrt(pow(dr->rx - dr->x, 2) + (pow(dr->ry - dr->y, 2)));
}

void	fix_fish_eye(t_app *app)
{
	t_draw	*dr;
	
	dr = &(app->dr);
	dr->ca = app->ray.game_state.pa - dr->ra;
	if (dr->ca < 0)
	{
		dr->ca += 2 * PI;
	}
	if (dr->ca > 2 * PI)
	{
		dr->ca -= 2 * PI;
	}
	dr->tdist = dr->tdist * cos(dr->ca);
}

void	draw_mini_rays(t_app *app)
{
	t_draw	*dr;
	
	dr = &(app->dr);
	prepa_init_ray(app);
	while (dr->r < 60)
	{
		check_horizont_line(app);
		check_vertical_line(app);
		if (dr->vdist < dr->hdist)
			dr->tdist = dr->vdist;
		if (dr->hdist < dr->vdist)
			dr->tdist = dr->hdist;
		dr->i = -1;
		while (++dr->i < (int)(dr->tdist / 2)) /*affiche plus petite distance entre vertical et horizontal*/
			my_mlx_pixel_put(&(app->img), (((dr->i * cos(dr->ra))) + dr->x/2),
			(((dr->i * sin(dr->ra))) + dr->y/2), 0x003ABFF7);
		dr->r++;
		dr->ra += DR;
		if (dr->ra < 0)
			dr->ra += 2 * PI;
		if (dr->ra > 2 * PI)
			dr->ra -= 2 * PI;
	}
}

void	which_is_dir(t_app *app)
{
	t_draw	*dr;
	
	dr = &(app->dr);
	if (dr->vdist < dr->hdist)
	{
		dr->tdist = dr->vdist;
		dr->rx = dr->vy;
		dr->ry = dr->vy;
		if (dr->ra > PI2 && dr->ra < PI3)
			dr->mod = 2; //look left
		else
			dr->mod = 4; //look right
	}
	if (dr->hdist < dr->vdist)
	{
		dr->tdist = dr->hdist;
		dr->rx = dr->hx;
		dr->ry = dr->hy;
		if (dr->ra > PI)//look north
			dr->mod = 0;
		else
			dr->mod = 1;//look south
	}
}

void	draw_rays_3d(t_app *app)
{
	t_draw	*dr;
	extern	int map_x;
	extern	int map_y;
	extern	int map[];
	extern	int map_s;
	
	dr = &(app->dr);
	prepa_init_ray(app);
	while (dr->r < 60)
	{
		// int vmt = 0, hmt = 0;
		check_horizont_line(app);
		check_vertical_line(app);
		which_is_dir(app);
		int color;
		if (dr->tdist == dr->vdist)
			color = 0x003AB0A7;
		else
			color = 0x003F8080;
		fix_fish_eye(app);
		// draw 3D Walls
		dr->lineH = (map_s * app->y)/dr->tdist; // line height
		dr->saveH = dr->lineH;

		// float ty_step = 64.0 / dr->saveH;
		// float ty_off = 0;
		if (dr->lineH > app->y)
			dr->lineH = app->y;
		dr->lineO = app->y / 2 - dr->lineH / 2;
		// float ty = ty_off *ty_step;
		// float tx = (int)(rx/2.0) % 64;
		dr->i = 0;
		while (dr->i < (int)dr->lineH) /*affiche plus petite distance entre vertical et horizontal*/
		{
			dr->j = 0;
			while (dr->j < 60)
			{
				int x = dr->j + dr->r * app->x/60 + app->x;
				my_mlx_pixel_put(&(app->img), x,dr->i + dr->lineO,
				get_color(app, dr->j + dr->r * app->x/60 + app->x, dr->i + dr->lineO, dr->saveH, 
				dr->rx, dr->i, dr->r, dr->mod));
				dr->j++;
			}
			dr->i++;
		}
		dr->r++;
		dr->ra += DR;
		if (dr->ra < 0)
			dr->ra += 2 * PI;
		if (dr->ra > 2 * PI)
			dr->ra -= 2 * PI;
	}
}
