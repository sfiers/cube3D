#include "wolf.h"

void fill_info(t_info *info, t_maptab *tab)
{
	info->tex_x = 0; //************new
//info->count_x = 0; //**********new
	info->blocksize = 64;
	// info->screenwidth = 1600; // a degager
	// info->screenheight = 900; // a degager
	info->mapwidth = tab->len_max;
	info->mapheight = tab->counter;
	coordinatesofbarrel(info);
//printf("mapwidth = %d et mapheight = %d\n", info->mapwidth, info->mapheight);
	info->pov = 66;
//	info->a.x = 160; // a degager
//	info->a.y = 96; // a degager
	//info->angle = 90; // a degager
	info->bad = info->pov/2;
	info->bd = info->screenwidth / 2;
	info->ad = toa(info->bad, info->bd);
	info->dir.x = cos(ft_deg2rad(info->angle)) * info->ad;
	info->dir.y = sin(ft_deg2rad(info->angle)) * info->ad;
	info->plan.x = cos(ft_deg2rad(info->angle + 90)) * info->bd;
	info->plan.y = sin(ft_deg2rad(info->angle + 90)) * info->bd;
	info->b.x = info->a.x + info->dir.x + info->plan.x;
	info->b.y = info->a.y + info->dir.y + info->plan.y;
	info->c.x = info->a.x + info->dir.x - info->plan.x;
	info->c.y = info->a.y + info->dir.y - info->plan.y;
	info->next_axis[0] = (int)info->a.x + (int)info->blocksize - ((int)info->a.x % (int)info->blocksize);
	info->next_axis[1] = (int)info->a.y + (int)info->blocksize - ((int)info->a.y % (int)info->blocksize);
	info->side = 0; //*************new
}

void update_info(t_info *info)
{
	info->dir.x = cos(ft_deg2rad(info->angle)) * info->ad;
	info->dir.y = sin(ft_deg2rad(info->angle)) * info->ad;
	info->plan.x = cos(ft_deg2rad(info->angle + 90)) * info->bd;
	info->plan.y = sin(ft_deg2rad(info->angle + 90)) * info->bd;
	info->b.x = info->a.x + info->dir.x + info->plan.x;
	info->b.y = info->a.y + info->dir.y + info->plan.y;
	info->c.x = info->a.x + info->dir.x - info->plan.x;
	info->c.y = info->a.y + info->dir.y - info->plan.y;
	info->next_axis[0] = (int)info->a.x + (int)info->blocksize - ((int)info->a.x % (int)info->blocksize);
	info->next_axis[1] = (int)info->a.y + (int)info->blocksize - ((int)info->a.y % (int)info->blocksize);
	// // // // printf("info->next_axis[0] = %f\n", info->next_axis[0]);
	// // // // printf("info->next_axis[1] = %f\n", info->next_axis[1]);
}

void	mlx_put_in_img(t_info *info, int x, int y, int color)
{
	info->s.data[((int)info->screenwidth) * y + x] = color;
}

// t_s		*create_image(t_info *info, int x, int y)
// {
// 	int i;
// ​
// 	s = begin_list(s);
// 	i = (x * s->screen.bpp / 8) + (s->screen.size_line * y);
// 	info->s.data[i] = info->ceiling.red;
// 	s->screen.data[++i] = info->ceiling.green;
// 	s->screen.data[++i] = info->ceiling.blue;
// 	s->screen.data[++i] = 0;
// 	return (s);
// }

void	ft_display(t_info *info, int whichray, double wall_hight) // probablenent suppr float distance
{
	int		y;
	float	wall_down;
	double color;
	double ratio;
	double rest;
	int *texture;

	y = 0;
	info->tex_y = 0;
	ratio = 64/wall_hight;
	if (wall_hight > info->screenheight)
		info->tex_y = ((wall_hight - info->screenheight) / 2) * ratio;
	if (info->side == 1)
	{
		if ((rest = info->wall[0] % 64) != 0)
			info->tex_x = rest;
		else
			info->tex_x = 0;
	}
	if (info->side == 0)
	{
		if ((rest = info->wall[1] % 64) != 0)
			info->tex_x = rest;
		else
			info->tex_x = 0;
	}
	wall_down = (info->screenheight - wall_hight) / 2;
	// put_texture(info);
	nesw(info);
	if (info->nesw == 0)
		texture = info->no.data;
	else if (info->nesw == 1)
		texture = info->ea.data;
	else if (info->nesw == 2)
		texture = info->so.data;
	else
		texture = info->we.data;
	while (y < info->screenheight)
	{
		while (y < info->screenheight && y < wall_down) //plafond
			//mlx_put_in_img(info, whichray, y++, 0x87ceff);
			mlx_put_in_img(info, whichray, y++,info->trgb_ceiling);
		while (y < info->screenheight && y < (wall_down + wall_hight)) //mur
		{
			info->tex_y = info->tex_y + ratio;
			if ((int)info->tex_y >= 64)
				break;
			color = texture[(int)info->tex_x + (int)info->tex_y * 64];
			mlx_put_in_img(info, whichray, y++, color);
		}
		if (y < info->screenheight)
			//mlx_put_in_img(info, whichray, y++, 0x54ff9f);  //sol
			mlx_put_in_img(info, whichray, y++, info->trgb_floor);
	}
}

void put_texture(t_info *info)
{
	int size;

	size = 64;
	//info->no.ptr = mlx_xpm_file_to_image(info->s.mlx, "./stone.xpm", &size, &size);
	info->no.ptr = mlx_xpm_file_to_image(info->s.mlx, info->no_texture, &size, &size);
	info->no.data = (int *)mlx_get_data_addr(info->no.ptr, &info->no.bpp, &info->no.size, &info->no.a);
	info->so.ptr = mlx_xpm_file_to_image(info->s.mlx, info->so_texture, &size, &size);
	info->so.data = (int *)mlx_get_data_addr(info->so.ptr, &info->so.bpp, &info->so.size, &info->so.a);
	info->we.ptr = mlx_xpm_file_to_image(info->s.mlx, info->we_texture, &size, &size);
	info->we.data = (int *)mlx_get_data_addr(info->we.ptr, &info->we.bpp, &info->we.size, &info->we.a);
	info->ea.ptr = mlx_xpm_file_to_image(info->s.mlx, info->ea_texture, &size, &size);
	info->ea.data = (int *)mlx_get_data_addr(info->ea.ptr, &info->ea.bpp, &info->ea.size, &info->ea.a);
	info->sp.ptr = mlx_xpm_file_to_image(info->s.mlx, info->sp_texture, &size, &size);
	info->sp.data = (int *)mlx_get_data_addr(info->sp.ptr, &info->sp.bpp, &info->sp.size, &info->sp.a);
}

int main()
{
	t_info info;
	t_maptab tab;
	t_error error;
	t_sprites barrel;
	t_element elem;

	if (parsing(&tab, &info) == -1)
		return (-1);
	else
		info.worldMap = tab.tab;
	if (parsing2(&elem, &info) == -1)
	{
		printf("stop\n");
		return (-1);
	}
	fill_info(&info, &tab);
	//fill_static(&info);
	info.s.mlx = mlx_init();
// 	all->fractal.img = mlx_new_image(all->wdw.mlx_ptr, W_SIZE_X, W_SIZE_Y);
// all->fractal.data = (int *)mlx_get_data_addr(all->fractal.img, &all->fractal.bpp, &all->fractal.size, &all->fractal.a);
   	info.s.win = mlx_new_window(info.s.mlx, info.screenwidth, info.screenheight, "Cube3D");
	info.s.img = mlx_new_image(info.s.mlx, info.screenwidth, info.screenheight);
	info.s.data = (int *)mlx_get_data_addr(info.s.img, &info.s.bpp, &info.s.size, &info.s.a);
	rendering(&info);
	free_tabs(&info);
	// mlx_put_image_to_window(s.mlx, s.win, s.img, info.screenWidth, info.screenHeight);
	mlx_key_hook(info.s.win, ft_key_press, &info);
	// mlx_key_hook(s.win, ft_angle, &info);
//	mlx_loop_hook(s.mlx);
	//mlx_hook(s.win, 2, 1L<<0, ft_angle, &s);
//	mlx_hook(s.win, 3, 1L<<1, ft_angle, &s);
	// mlx_hook(info.s.win, 2, 1L<<0, ft_close, &info.s); //fermer la fenetre, 0xffff);  //imprimer pixel
  mlx_loop(info.s.mlx);
//   if (tab.map_str1 != NULL)
//   	free(tab.map_str1);
  free_malloc(&info);
 // system("leaks checker");
}

void free_malloc(t_info *info)
{
	int i;

	i = 0;
	free(info->no_texture);
	free(info->so_texture);
	free(info->ea_texture);
	free(info->we_texture);
	free(info->sp_texture);
	while (i < info->mapheight)
	{
		free(info->worldMap[i]);
		i++;
	}
}

int saveintab(t_info *info, int whichray)
{
	if ((!(info->barrel.walldistance = malloc(sizeof(double) * (info->screenwidth))))
		|| (!(info->barrel.a = malloc(sizeof(double) * (info->screenwidth))))
		|| (!(info->barrel.c = malloc(sizeof(double) * (info->screenwidth))))
		|| (!(info->barrel.distance = malloc(sizeof(double) * (info->nbsprite)))))
		return (-1);
	// if (!(info->barrel.a = malloc(sizeof(double) * (info->screenwidth))))
	// 	return (-1);
	// if (!(info->barrel.c = malloc(sizeof(double) * (info->screenwidth))))
	// 	return (-1);
	// if (!(info->barrel.distance = malloc(sizeof(double) * (info->nbsprite))))
	// 	return (-1);
	
	// info->barrel.a[whichray] = info->ray.m;
	// info->barrel.c[whichray] = info->ray.n;
	//printf("ray.m = %f et ray.n = %f\n", info->ray.m, info->ray.n);
	//printf("info->barrel.a[%d] = %f et info->barrel.c[%d] = %f\n", whichray, info->barrel.a[whichray], whichray, info->barrel.c[whichray]);
	return (1);
}

int rendering(t_info *info)
{
	int whichray;
	double shortest_distance;
	double wall_height;
	
	info->wall[0] = -1;
	info->wall[1] = -1;
	whichray = 0;
	// mlx_clear_window(info->s.mlx, info->s.win); don t clear with image
	put_texture(info);
	saveintab(info, whichray);
	while(whichray < info->screenwidth)
	{
		// printf("------------------ray = %d\n", whichray);
		update_info(info);
		p_on_plan(info, (double)whichray);  
		ray(&info->ray, info->a, info->p_of_plan);
		info->barrel.a[whichray] = info->ray.m;
		info->barrel.c[whichray] = info->ray.n;
		//printf("info->barrel.a[%d] = %f et info->barrel.c[%d] = %f\n", whichray, info->barrel.a[whichray], whichray, info->barrel.c[whichray]);
		test_x_axis(info);
		test_y_axis(info);
		shortest_distance = distance_to_wall(info);
		//printf("whichray = %d\n", whichray);
		info->barrel.walldistance[whichray] = shortest_distance;
		//printf("shortest_distance = %f et distance_tab[whichray] = %f\n", shortest_distance, distance_tab[whichray]);
		wall_height = walls(info, shortest_distance, whichray);
		// // printf("distance %f\n", shortest_distance);
		// printf("slice_hight %f\n", slice_hight);dds
		ft_display(info, whichray, wall_height);
		whichray++;
		// // // // printf("a.x = %f\n", info->a.x);
		// // // // printf("a.y = %f\n", info->a.y);
	}
	handlesprites(info);
	mlx_put_image_to_window(info->s.mlx, info->s.win, info->s.img, 0, 0);
	// printf("a.x = %f\n", info->a.x);
	// printf("a.y = %f\n", info->a.y);
	// printf("angle = %f\n", info->angle);
	return (1);
} 

void p_on_plan(t_info *info, double whichray)
{
	info->p_of_plan.x = info->b.x - (whichray * (info->b.x - info->c.x) / info->screenwidth); 
	info->p_of_plan.y = info->b.y - (whichray * (info->b.y - info->c.y) / info->screenwidth);
}

void test_x_axis(t_info *info)
{
	int hit;
	int n;
	
	n = 0;
	hit = 0;
	info->redflag[0] = 0;
	info->test_axis[n].x = (info->a.x < info->p_of_plan.x) ? info->next_axis[n] : info->next_axis[n] - info->blocksize;
	while (hit == 0)
	{
		find_y(&info->test_axis[n], info->ray.m, info->ray.n);
		// printf("test x = %f\n", info->test_axis[n].x);
		// printf("test y = %f\n", info->test_axis[n].y);
		if (map_bounderies(info, n) == 1)
			break;
		if((hit = hit_map(info, n) == 1))
		{
			// printf("hit = %d\n", hit);
			break;
		}
		info->test_axis[n].x += (info->a.x < info->p_of_plan.x) ? info->blocksize : - info->blocksize;
	}
}

void test_y_axis(t_info *info)
{
	int hit;
	int n;
	
	n = 1;
	hit = 0;
	info->redflag[1] = 0;
	info->test_axis[n].y = (info->a.y < info->p_of_plan.y) ? info->next_axis[n] : info->next_axis[n] - info->blocksize;
	while (hit == 0)
	{
		find_x(&info->test_axis[n], info->ray.m, info->ray.n);
		// printf("info->test_axis[1] = %f\n", info->test_axis[n].x);
		// printf("info->test_axis[1] = %f\n", info->test_axis[n].y);
		if (map_bounderies(info, n) == 1)
			break;
		if((hit = hit_map(info, n) == 1))
		{
			// printf("hit = %d\n", hit);
			break;
		}
		// // // printf("info->test_axis[1] = %f\n", info->test_axis[n].x);
		// // // printf("info->test_axis[1] = %f\n", info->test_axis[n].y);
		info->test_axis[n].y += (info->a.y < info->p_of_plan.y) ? info->blocksize : - info->blocksize;
		// // // printf("info->test_axis[1] = %f\n", info->test_axis[n].x);
		// // // printf("info->test_axis[1] = %f\n", info->test_axis[n].y);
	}
}

int map_bounderies(t_info *info, int n)
{
	if ((int)info->test_axis[n].x < 0 || (int)info->test_axis[n].y < 0)
	{
		info->redflag[n] = 1;
		// printf("info->redflag[n] = %d\n", info->redflag[n]);
		return (1);
	}
	if ((int)info->test_axis[n].x >= (int)(info->mapheight * info->blocksize) || (int)info->test_axis[n].y >= (int)(info->mapwidth * info->blocksize))
	{
		info->redflag[n] = 1;
		// printf("info->redflag[n] = %d\n", info->redflag[n]);
		return (1);
	}
	return (0);
}

// void	width_wall(t_info *info, int whichray, int *old_wall)
// {
// 	static int wall[2];

// 	wall[0] = old_wall[0];
// 	wall[1] = old_wall[1];
// }

double distance_to_wall(t_info *info)
{
	double distance[2];
//	static int wall[2];

	if (info->redflag[0] == 1)
	{
		info->side = 1;
		// // // // printf("--------------1--------------\n");
		// printf("distance[0] %f\n", distance[0]);
		// printf("distance[1] %f\n", distance_2_points(info->a, info->test_axis[1]));
		info->wall[0] = info->test_axis[1].x;
		info->wall[1] = info->test_axis[1].y;
		return (distance_2_points(info->a, info->test_axis[1]));
	}
	if (info->redflag[1] == 1)
	{
		info->side = 0;
		// // // // printf("--------------2--------------\n");
		// printf("distance[0] %f\n", distance[0]);
		// printf("distance[1] %f\n", distance[1]);
		info->wall[0] = info->test_axis[0].x;
		info->wall[1] = info->test_axis[0].y;
		return (distance_2_points(info->a, info->test_axis[0]));
	}
	// // // printf("info->a = %f\n", info->a.x);
	// // // printf("info->a = %f\n", info->a.y);
	// // // printf("info->test_axis[0] = %f\n", info->test_axis[0].x);
	// // // printf("info->test_axis[0] = %f\n", info->test_axis[0].y);
	distance[0] = distance_2_points(info->a, info->test_axis[0]); // pour les x
	distance[1] = distance_2_points(info->a, info->test_axis[1]); 
	// printf("distance[0] %f\n", distance[0]);
	// printf("distance[1] %f\n", distance[1]);
	// // // printf("--------------distance to be used---------------\n");
	if (distance[0] < distance[1])
	{
		info->side = 0;
		info->wall[0] = info->test_axis[0].x;
		info->wall[1] = info->test_axis[0].y;
		info->wallx = info->test_axis[0].x;
		return (distance[0]);
	}
	else 
	{
		info->side = 1;
		info->wall[0] = info->test_axis[1].x;
		info->wall[1] = info->test_axis[1].y;
		info->wallx = info->test_axis[1].x;
		return (distance[1]);
	}
}

int hit_map(t_info *info, int n)
{
	info->map[0].x = (info->a.x < info->p_of_plan.x) ? bloc_to_map(info->test_axis[n].x, info->blocksize) : bloc_to_map(info->test_axis[n].x, info->blocksize) - 1;
	info->map[0].y = bloc_to_map(info->test_axis[n].y, info->blocksize);
	info->map[1].x = bloc_to_map(info->test_axis[n].x, info->blocksize);
	info->map[1].y = (info->a.y < info->p_of_plan.y) ? bloc_to_map(info->test_axis[n].y, info->blocksize) : bloc_to_map(info->test_axis[n].y, info->blocksize) - 1;
	// // printf("map 3 2 = %d\n", info->worldMap[3][2]);
	// printf("map A = %d\n", (mapWidth - 1) - info->map[n].y);
	// printf("map B = %d\n", info->map[n].x);
	// printf("test x = %d\n", info->map[n].x);
	// printf("test y = %d\n", info->map[n].y);	
	// // printf("map 3 2 = %d\n", info->worldMap[3][2]);
	if (info->map[n].x < 0 || info->map[n].y < 0) // y sais etre moins 1 dans le test peut etre x aussi
		return (1);
	if (info->worldMap[(info->mapwidth - 1) - info->map[n].y][info->map[n].x] == 1) // because our map y-axis is reversed (to be checked if mapWidth and not mapHeight)
	{
		// // printf("testtest\n");	
		return (1);
	}
	return(0);
}

void nesw(t_info *info)
{
	if (info->side == 0) 
		info->nesw = (info->a.x < info->p_of_plan.x) ? 1 : 3;
	if (info->side == 1) 
		info->nesw = (info->a.y < info->p_of_plan.y) ? 0 : 2;
	return;
}

void free_tabs(t_info *info)
{
	free(info->barrel.walldistance);
	free(info->barrel.a);
	free(info->barrel.c);
	free(info->barrel.distance);
}