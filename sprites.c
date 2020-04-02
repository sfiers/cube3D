#include "wolf.h" 

int findray(t_info *info, int i, double x, double y)
{
	double distance;
	double distance2;
	int whichray;

	info->barrel.pointtemp.x = x;
	info->barrel.pointtemp.y = y;
	whichray = 0;
	while (whichray < info->screenwidth - 1)
	{
		// y = mx + n=> Ax + By + C = 0
		info->barrel.droitetemp.a = info->barrel.a[whichray] ; // m
		info->barrel.droitetemp.b = -1; // -1
		info->barrel.droitetemp.c = info->barrel.c[whichray];
		info->barrel.droitetemp2.a = info->barrel.a[whichray + 1];
		info->barrel.droitetemp2.b = -1;
		info->barrel.droitetemp2.c = info->barrel.c[whichray + 1];
		distance = ft_distancepointdroite(info->barrel.pointtemp, info->barrel.droitetemp);
		distance2 = ft_distancepointdroite(info->barrel.pointtemp, info->barrel.droitetemp2);
		if (distance < distance2)
			break;
		whichray++;
	}
//	info->barrel.startray = (info->barrel.reverse == 0 ? whichray - 1 : info->barrel.startray);
	//printf("startray = %d\n", info->barrel.startray);
	// if (info->barrel.startray == -1)
	// 	info->barrel.startray = info->screenwidth - 1;
	// info->barrel.endray = (info->barrel.reverse == 0 ? whichray - 1: info->barrel.endray);
	// if (info->barrel.startray < 0 && info->barrel.reverse == 0)
	// {
	// 	info->barrel.reverse = 1;
	// 	info->barrel.startdrawx[i] = info->barrel.x[i] - info->barrel.spriteplandir.x;
	// 	info->barrel.startdrawy[i] = info->barrel.y[i] - info->barrel.spriteplandir.y;
	//	printf("barrel.x[%d] = %f et barrel.y[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
		// printf("plandir1.x = %f et plandir1.y = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
		// printf("startdrawx1[%d] = %f et startdrawy1[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
		// printf("barrel.x1[%d] = %f et barrel.y1[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
		// printf("plandir.x1 = %f et plandir.y1 = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
		// printf("startdrawx1[%d] = %f et startdrawy1[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
	//	info->barrel.endray = findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]);
	//	printf("endray = %d\n", info->barrel.endray);
//	}
	if (whichray == info->screenwidth - 1)
		return (whichray);
	return (whichray - 1);
}

void handlesprites(t_info *info)
{
	int i;

	i = 0;
	distance_2_sprite(info); // distance entre le centre de chaque sprite et la joueur
	ft_sort_sprites(info); // tri les distances du + loin au + proche 
	printf("coucou\n");
	while (i < info->nbsprite)
	{	
		initialise(info, i);
		if (fabs(info->barrel.spriteangle - info->angle) < 90 || fabs(info->barrel.spriteangle - info->angle) > 270)
		{	
			seekdrawstart(info, i);
			info->barrel.middleray = findray(info, i, info->barrel.x[i], info->barrel.y[i]);
			printf ("info->barrel.middleray = %d\n",  info->barrel.middleray);
			info->barrel.startray = findray(info, i, info->barrel.startdrawx, info->barrel.startdrawy);
			printf ("info->barrel.startray = %d\n",  info->barrel.startray);
			if (info->barrel.startray < 0)
			{
				info->barrel.startdrawx = info->barrel.x[i] - info->barrel.spriteplandir.x;
	 			info->barrel.startdrawy = info->barrel.y[i] - info->barrel.spriteplandir.y;
				info->barrel.endray = findray(info, i, info->barrel.startdrawx, info->barrel.startdrawy);
				printf("endray = %d\n", info->barrel.endray);
				info->barrel.endray == info->screenwidth - 1 ? print_sprite_middle(info, i) : print_sprite_right(info, i, info->barrel.endray, 63);
			}
			else
				print_sprite_left(info, i, info->barrel.startray, 0);
		}
		i++;
	}
}

void print_sprite_middle(t_info *info, int i)
{
	print_sprite_left(info, i, info->barrel.middleray, 31);
	print_sprite_right(info, i, info->barrel.middleray, 31);
}

void print_sprite_right(t_info *info, int i, int whichray, double tex_x)
{
	int y;
	double ratio;

	y = info->barrel.ystart;
	ratio = 0;
	info->tex_y = 0;
	while (tex_x >= 0 && whichray >= 0)
	{
		while (y < info->screenheight && y < (info->barrel.ystart + info->barrel.height) && whichray >= 0)
		{
			info->tex_y = info->tex_y + ratio;
			if ((int)info->tex_y >= 64)
				break;
			if (info->barrel.walldistance[whichray] > info->barrel.distance[i])
			{
				if ((info->sp.data[(int)tex_x + (int)info->tex_y * 64]) != 0)
					info->barrel.color = info->sp.data[(int)tex_x + (int)info->tex_y * 64];
			}
			if ((info->sp.data[(int)tex_x + (int)info->tex_y * 64]) != 0 && info->barrel.walldistance[whichray] > info->barrel.distance[i])
				mlx_put_in_img(info, whichray, y, info->barrel.color);
			y++;
			ratio = 64/info->barrel.height;
		}
		info->tex_y = 0;
		y = info->barrel.ystart;
		tex_x -= ratio;
		whichray--;
	}
	printf("firstray = %d\n", whichray + 1);
}

void print_sprite_left(t_info *info, int i, int whichray, double tex_x)
{
	int y;
	double ratio;

	y = info->barrel.ystart;
	ratio = 0;
	info->tex_y = 0;
	while (tex_x < 64 && whichray < info->screenwidth)
	{
		while (y < info->screenheight && y < (info->barrel.ystart + info->barrel.height) && whichray < info->screenwidth)
		{
			info->tex_y = info->tex_y + ratio;
			if ((int)info->tex_y >= 64)
				break;
			if (info->barrel.walldistance[whichray] > info->barrel.distance[i])
			{
				if ((info->sp.data[(int)tex_x + (int)info->tex_y * 64]) != 0)
					info->barrel.color = info->sp.data[(int)tex_x + (int)info->tex_y * 64];
			}
			if ((info->sp.data[(int)tex_x + (int)info->tex_y * 64]) != 0 && info->barrel.walldistance[whichray] > info->barrel.distance[i])
				mlx_put_in_img(info, whichray, y, info->barrel.color);
			y++;
			ratio = 64/info->barrel.height;
		}
		info->tex_y = 0;
		y = info->barrel.ystart;
		tex_x += ratio;
		whichray++;
	}
	printf("lastray = %d\n", whichray - 1);
}

void initialise(t_info *info, int i)
{
	t_p spritecoordinates;

	spritecoordinates.x = info->barrel.x[i];
	spritecoordinates.y = info->barrel.y[i];
	ray(&info->barrel.spriteray, info->a, spritecoordinates);  // calcule droite allant du centre du sprite au joueur;
	info->barrel.spriteangle = ft_rad2deg(atan(fabs(info->barrel.spriteray.m))); // car equation de la droite x axis est y = 0 et la formule tan(alpha) = abs ((m2-m1)/(1 +(m2*m1)))
	if (info->barrel.spriteray.m == 0)
		info->barrel.spriteangle = (info->barrel.x[i] > info->a.x ? 0 : 180);
	else if(info->barrel.spriteray.m > 0)
		info->barrel.spriteangle += (info->barrel.y[i] < info->a.y ? 180 : 0);
	else
	{
		info->barrel.spriteangle = 180 - info->barrel.spriteangle;
		info->barrel.spriteangle += (info->barrel.y[i] < info->a.y ? 180 : 0);
	}
	info->barrel.spriteplandir.x = cos(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
	info->barrel.spriteplandir.y = sin(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
	info->barrel.height = spriteheight(info, info->barrel.distance[i]);
	info->barrel.ystart = (info->screenheight - info->barrel.height)/2;
}

void seekdrawstart(t_info *info, int i)
{
	info->barrel.startdrawx = info->barrel.x[i] + info->barrel.spriteplandir.x;
	info->barrel.startdrawy = info->barrel.y[i] + info->barrel.spriteplandir.y;
}

void distance_2_sprite(t_info *info)
{
	int i;

	i = 0;
	while (i < info->nbsprite)
	{
		info->barrel.distance[i] = sqrt(pow(info->barrel.x[i] - info->a.x, 2) + pow(info->barrel.y[i] - info->a.y, 2));
		i++;
	}
}

void ft_sort_sprites(t_info *info)
{
	int	count;
	int	i;
	double tmp[3];
	
	count = 0;
	while (count < info->nbsprite)
	{
		i = 0;
		while (i < (info->nbsprite) - 1)
		{
			if (info->barrel.distance[i] < info->barrel.distance[i + 1])
			{
				tmp[0] = info->barrel.distance[i];
				tmp[1] = info->barrel.x[i];
				tmp[2] = info->barrel.y[i];
				info->barrel.distance[i] = info->barrel.distance[i + 1];
				info->barrel.x[i] = info->barrel.x[i + 1];
				info->barrel.y[i] = info->barrel.y[i + 1];
				info->barrel.distance[i + 1] = tmp[0];
				info->barrel.x[i + 1] = tmp[1];
				info->barrel.y[i + 1] = tmp[2];
			}
			i++;
		}
		count++;
	}
}

int coordinatesofbarrel(t_info *info)
{
	int i;
	int j;
	int n;

	i = 0;  // lignes
	j = 0;  // colonnes
	n = 0;
	if ((!(info->barrel.x = malloc(sizeof(double) * (info->nbsprite)))) 
		|| (!(info->barrel.y = malloc(sizeof(double) * (info->nbsprite)))))
		return (-1);
	while (i < info->mapheight)
	{
		j = 0;
		while (j < info->mapwidth && n < info->nbsprite)
		{
			if (info->worldMap[i][j] == 2)
			{
				info->barrel.x[n] = j * 64 + 32;
				info->barrel.y[n] = (info->mapheight - 1 - i) * 64 + 32;
				n++;
			}
			player_position(info, i, j);
			printf("info->angle = %f\n", info->angle);
			j++;
		}
		i++;
	}
	return (1);
}

void player_position(t_info *info, int i, int j)
{
	if (info->worldMap[i][j] == 3) //N
		info->angle = 90;
	if (info->worldMap[i][j] == 4) //W
		info->angle = 180;
	if (info->worldMap[i][j] == 5) //S
		info->angle = 270;
	if (info->worldMap[i][j] == 6) //E
		info->angle = 0;
	if (info->worldMap[i][j] == 3 || info->worldMap[i][j] == 4
		|| info->worldMap[i][j] == 5 || info->worldMap[i][j] == 6)
	{
		info->a.x = j * 64 + 32;
		info->a.y = (info->mapheight - 1 - i) * 64 + 32;
	}
}

double spriteheight(t_info *info, double distance)
{
	double corrected_distance;
	double height;

	corrected_distance = fishbowlsprite(info, distance); // il faut appliquer cette formule pour tout angle ou juste pour les angle droit??
	height = projected_slice_hight(info, corrected_distance);
	return (height);
}

double fishbowlsprite(t_info *info, double distorted_distance)
{
	double corrected_distance;

	if (info->angle < info->barrel.spriteangle)
		corrected_distance = distorted_distance * cos(ft_deg2rad(info->barrel.spriteangle - info->angle));
	else
		corrected_distance = distorted_distance * cos(ft_deg2rad(info->angle - info->barrel.spriteangle));
	return (corrected_distance);
}
