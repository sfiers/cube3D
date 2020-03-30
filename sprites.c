#include "wolf.h" 

// typedef struct      s_droite
// {
// 	double a;
// 	double b;
// 	double c;
// }					t_droite;

// typedef struct      s_sprites
// {
// 	double distance[nbsprite];
// 	int nbsprite;
// 	double x[nbsprite];
// 	double y[nbsprite];
// 	double seensprites[whichray][nbsprites];
// 	t_p spriteplandir;
// 	double startdrawx[nbsprite];
// 	double startdrawy[nbsprite];
// 	int startray;
// 	double ab[nbsprites];
// 	double disttworay[nbsprites];
// 	t_ray firstray;
// 	t_ray lastray;
// 	t_ray spriteray;
// 	t_ray xaxis;
// 	t_droite droitetemp;
// 	t_droite droitetemp2;
// 	t_p pointtemp;
// 	t_p temp2;
// 	// float rayseekm;
// }				    t_sprites;

// t_sprites barrel;

int findray(t_info *info, int i, double x, double y)
{
	double distance;
	double distance2;
	int whichray;

	// info->barrel.pointtemp.x = info->barrel.startdrawx[i];
	// info->barrel.pointtemp.y = info->barrel.startdrawy[i];
	info->barrel.pointtemp.x = x;
	info->barrel.pointtemp.y = y;
	//printf("pointtemp.x = %f et pointtemp.y = %f\n", info->barrel.pointtemp.x, info->barrel.pointtemp.y);
	//whichray = -(info->screenWidth/2);
	whichray = 0;
	//printf("barrel.a[%d] = %f et barrel.c[%d] = %f\n", i, info->barrel.a[i], i, info->barrel.c[i]);
	while (whichray < info->screenWidth - 1)
	{
	//	printf("info->barrel.a[%d] = %f et info->barrel.c[%d] = %f\n", whichray, info->barrel.a[whichray], whichray, info->barrel.c[whichray]);
		// y = mx + n=> Ax + By + C = 0
		info->barrel.droitetemp.a = info->barrel.a[whichray] ; // m
		//droitetemp.b = info->barrel.b[whichray]; // -1
		info->barrel.droitetemp.b = -1; // -1
		//info->barrel.droitetemp.c = barrel_c[whichray]; // n
		info->barrel.droitetemp.c = info->barrel.c[whichray];
		info->barrel.droitetemp2.a = info->barrel.a[whichray + 1];
		//info->barrel.droitetemp2.b = info->barrel.b[whichray + 1];
		info->barrel.droitetemp2.b = -1;
		info->barrel.droitetemp2.c = info->barrel.c[whichray + 1];
		distance = ft_distancepointdroite(info->barrel.pointtemp, info->barrel.droitetemp);
		distance2 = ft_distancepointdroite(info->barrel.pointtemp, info->barrel.droitetemp2);
	//	printf("distance = %f et distance2 = %f\n", distance, distance2);
		if(distance < distance2)
			break;
		whichray++;
	}
	info->barrel.startray = (info->barrel.reverse == 0 ? whichray - 1 : info->barrel.startray);
	printf("startray = %d\n", info->barrel.startray);
	// if (info->barrel.startray == -1)
	// 	info->barrel.startray = info->screenWidth - 1;
	info->barrel.endray = (info->barrel.reverse == 0 ? whichray - 1: info->barrel.endray);
	if (info->barrel.startray < 0 && info->barrel.reverse == 0)
	{
		info->barrel.reverse = 1;
		info->barrel.startdrawx[i] = info->barrel.x[i] - info->barrel.spriteplandir.x;
		info->barrel.startdrawy[i] = info->barrel.y[i] - info->barrel.spriteplandir.y;
		// printf("barrel.x1[%d] = %f et barrel.y1[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
		// printf("plandir.x1 = %f et plandir.y1 = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
		// printf("startdrawx1[%d] = %f et startdrawy1[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
		info->barrel.endray = findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]);
	}
	return (whichray - 1);
}

// void handlesprites(t_sprites *barrel, t_info *info)
// {
// 	int i;

// 	i = 0;
// 	coordinatesofbarrel(barrel, info); // coordonnees x et y de chaque sprite via la map
// 	distance_2_sprite(barrel, info); // distance entre le centre de chaque sprite et la joueur
// 	ft_sort_sprite(barrel, info); // tri les distances du + loin au + proche 
// 	while (i < info->nbsprite)
// 	{	
// 		initialise(barrel, info, i);
// 		seekdrawstart(barrel, info, i);
// 		findray(barrel, info, i);
// 	}
// }

void handlesprites(t_info *info)
{
	int i;

	i = 0;
	//int raynb;
	//coordinatesofbarrel(barrel, info); // coordonnees x et y de chaque sprite via la map
	info->barrel.reverse = 0;
	distance_2_sprite(info); // distance entre le centre de chaque sprite et la joueur
	ft_sort_sprites(info); // tri les distances du + loin au + proche 
	//printf ("nbsprite = %d\n",  info->nbsprite);
	while (i < info->nbsprite)
	{	
		info->barrel.endray = 0;
		initialise(info, i);
		if (fabs(info->barrel.spriteangle - info->angle) < 90 || fabs(info->barrel.spriteangle - info->angle) > 270)
		{	
			info->barrel.pointtemp.x = 0;
			info->barrel.pointtemp.y = 0;
			info->barrel.middleray = findray(info, i, info->barrel.x[i], info->barrel.y[i]);
			printf("middleray = %d\n", info->barrel.middleray);
			info->barrel.middleray = (info->barrel.middleray < 0 ? 0 : info->barrel.middleray);
			info->barrel.middleray = (info->barrel.middleray >= info->screenWidth ? info->screenWidth : info->barrel.middleray);
			info->barrel.height = walls(info, info->barrel.distance[i], info->barrel.middleray);
			//nb_ray(info, i);
			seekdrawstart(info, i);
			//info->barrel.middleray = findray(info, i, info->barrel.x[i], info->barrel.y[i]);
			//info->barrel.startray = info->barrel.middleray - (info->barrel.ray_nb/2);
			info->barrel.startray = findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]);
			printf ("info->barrel.startray = %d\n",  info->barrel.startray);
			//info->barrel.height = projected_slice_hight(info, info->barrel.distance[i]);
			info->barrel.startray >= 0 ? print_sprite(info, i) : print_sprite_reverse(info, i);
			// if (info->barrel.startray >= 0)
			// {
			// 	//printf("startray = %d\n", info->barrel.startray);
			// 	print_sprite(info, i);
			// }
			// else
			// {
			// 	// info->barrel.startdrawx[i] = info->barrel.x[i] - info->barrel.spriteplandir.x;
			// 	// info->barrel.startdrawy[i] = info->barrel.y[i] - info->barrel.spriteplandir.y;
			// 	//info->barrel.endray = (findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]) - 0);
			// //	info->barrel.middleray = findray(info, i, info->barrel.x[i], info->barrel.y[i]);
			// 	info->barrel.endray = info->barrel.middleray + (info->barrel.ray_nb/2);
			// 	//printf("barrel.height = %f\n", info->barrel.height);
			// 	//info->barrel.endray = info->barrel.startray + ((64/info->barrel.height) * 64);
			// 	printf("endray = %d\n", info->barrel.endray);
			// 	//info->barrel.endray -= 51;
			// 	print_sprite_reverse(info, i);
			// }
		}
		i++;
	}
}

void print_sprite(t_info *info, int i)
{
	int whichray;
	int y;
	double ratio;
	double color;
	int start;

	//printf("hauteur[%d] = %f\n", i, info->barrel.distance[i]);
	start = (info->screenHeight - info->barrel.height)/2;
	y = start;
	//printf("y = %d\n", y);
	ratio = 64/info->barrel.height;
	//printf("ratio = %f\n", ratio);
	info->tex_x = 0;
	info->tex_y = 0;
	whichray = info->barrel.startray;
//	printf("whichray = %d\n", whichray);
	while (info->tex_x < 64 && whichray < info->screenWidth)
	{
	//	printf("tex_x = %f\n", info->tex_x);
		while (y < info->screenHeight && y < (start + info->barrel.height) && whichray < info->screenWidth)
		{
		//	printf("y = %d\n", y);
			info->tex_y = info->tex_y + ratio;
			// printf("y = %d\n", y);
		//	 printf("tex_y + ratio = %f\n", (info->tex_y + ratio)); 
		//	printf("walldistance[%d] = %f et distance[%d] = %f\n", whichray, info->barrel.walldistance[whichray], i, info->barrel.distance[i]);
			if ((int)info->tex_y >= 64)
				break;
			//printf("tex_y + ratio = %f\n", (info->tex_y + ratio));
			if (info->barrel.walldistance[whichray] > info->barrel.distance[i])
			{
				if ((info->sp.data[(int)info->tex_x + (int)info->tex_y * 64]) != 0)
					color = info->sp.data[(int)info->tex_x + (int)info->tex_y * 64];
				
			//printf("tex_x = %d et tex_y = %d\n", (int)info->tex_x, (int)info->tex_y);
			}
			if ((info->sp.data[(int)info->tex_x + (int)info->tex_y * 64]) != 0 && info->barrel.walldistance[whichray] > info->barrel.distance[i])
				mlx_put_in_img(info, whichray, y, color);
			y++;
		}
		info->tex_y = 0;
		y = start;
		info->tex_x += ratio;
		whichray++;
	}
	//info->barrel.lastray = whichray - 1;
	//printf("whichray = %d\n", whichray - 1);
}

// void nb_ray(t_info *info, int i)
// {
// 	int whichray;
// 	double ratio;

// 	info->barrel.ray_nb = 0;
// 	ratio = 64/info->barrel.height;
// 	//printf("ratio = %f\n", ratio);
// 	info->tex_x = 0;
// 	whichray = 0;
// //	printf("whichray = %d\n", whichray);
// 	while (info->tex_x < 64)
// 	{
// 		info->tex_x += ratio;
// 		whichray++;
// 	}
// 	info->barrel.ray_nb = whichray - 1;
// 	printf("raynb = %d\n", whichray - 1);
// }

void print_sprite_reverse(t_info *info, int i)
{
	int whichray;
	int y;
	double ratio;
	double color;
	int start;

	//printf("hauteur[%d] = %f\n", i, info->barrel.distance[i]);
	start = (info->screenHeight - info->barrel.height)/2;
	y = start;
	//printf("y = %d\n", y);
	ratio = 64/info->barrel.height;
	//printf("ratio = %f\n", ratio);
	info->tex_x = 63;
	info->tex_y = 0;
	whichray = info->barrel.endray;
	printf("whichray = %d\n", whichray);
	while (info->tex_x >= 0 && whichray >= 0)
	{
	//	printf("tex_x = %f\n", info->tex_x);
		while (y < info->screenHeight && y < (start + info->barrel.height) && whichray >= 0)
		{
		//	printf("y = %d\n", y);
			info->tex_y = info->tex_y + ratio;
			// printf("y = %d\n", y);
		//	 printf("tex_y + ratio = %f\n", (info->tex_y + ratio)); 
		//	printf("walldistance[%d] = %f et distance[%d] = %f\n", whichray, info->barrel.walldistance[whichray], i, info->barrel.distance[i]);
			if ((int)info->tex_y >= 64)
				break;
			//printf("tex_y + ratio = %f\n", (info->tex_y + ratio));
			if (info->barrel.walldistance[whichray] > info->barrel.distance[i])
			{
				if ((info->sp.data[(int)info->tex_x + (int)info->tex_y * 64]) != 0)
					color = info->sp.data[(int)info->tex_x + (int)info->tex_y * 64];
				
			//printf("tex_x = %d et tex_y = %d\n", (int)info->tex_x, (int)info->tex_y);
			}
			if ((info->sp.data[(int)info->tex_x + (int)info->tex_y * 64]) != 0 && info->barrel.walldistance[whichray] > info->barrel.distance[i])
				mlx_put_in_img(info, whichray, y, color);
			y++;
		}
		info->tex_y = 0;
		y = start;
		info->tex_x -= ratio;
		whichray--;
	}
}

void initialise(t_info *info, int i)
{
	t_p spritecoordinates;
	//double spriteangle;

//	printf("coucou\n");
	//printf("barrel.distance[%d] = %f\n", i, info->barrel.distance[i]);
	spritecoordinates.x = info->barrel.x[i];
	spritecoordinates.y = info->barrel.y[i];
	//printf("a.x = %f et a.y = %f\n", info->a.x, info->a.y);
	//printf("spritecoordinates.x = %f et spritecoordinates.y = %f\n", spritecoordinates.x, spritecoordinates.y);
	ray(&info->barrel.spriteray, info->a, spritecoordinates);  // calcule droite allant du centre du sprite au joueur;
	// ci dessous on calcule l angle aigu entre 2 droite (x axis et spriteray)
//	printf("spriteray.m = %f\n", info->barrel.spriteray.m);
	info->barrel.spriteangle = ft_rad2deg(atan(fabs(info->barrel.spriteray.m))); // car equation de la droite x axis est y = 0 et la formule tan(alpha) = abs ((m2-m1)/(1 +(m2*m1)))
//	printf("spriteangle = %f\n", info->barrel.spriteangle);
	// le spriteangle doit etre proche du vrai angle 
	if (info->barrel.spriteray.m == 0)
	{
		if(info->barrel.x[i] > info->a.x)
			info->barrel.spriteangle = 0;
		if(info->barrel.x[i] < info->a.x)
			info->barrel.spriteangle = 180;
	}
	else if(info->barrel.spriteray.m > 0)
	{
	//	printf("hey1\n");
		if(info->barrel.y[i] < info->a.y)
			info->barrel.spriteangle += 180;
	}
	// if(info->barrel.spriteray.m == 0)
	// {
	// 	spriteangle = 0;
	// 	// printf("hey1\n");
	// 	// if(info->barrel.y[i] < info->a.y)
	// 	// 	spriteangle += 180;
	// }
	else
	{
	//	printf("hey2\n");
		info->barrel.spriteangle = 180 - info->barrel.spriteangle;
		if(info->barrel.y[i] < info->a.y)
			info->barrel.spriteangle += 180;	
	}
//	printf("spriteangle2 = %f\n", info->barrel.spriteangle);
	info->barrel.spriteplandir.x = round(cos(ft_deg2rad(info->barrel.spriteangle + 90)) * info->blocksize/2);
	info->barrel.spriteplandir.y = round(sin(ft_deg2rad(info->barrel.spriteangle + 90)) * info->blocksize/2);
	//printf("spriteplandirx = %f et spriteplandiry = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
}

void seekdrawstart(t_info *info, int i)
{
	info->barrel.startdrawx[i] = info->barrel.x[i] + info->barrel.spriteplandir.x;
	info->barrel.startdrawy[i] = info->barrel.y[i] + info->barrel.spriteplandir.y;
//	printf("barrel.x[%d] = %f et barrel.y[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
	//printf("barrel.x0[%d] = %f et barrel.y0[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
	//printf("plandir.x0 = %f et plandir.y0 = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
	//printf("startdrawx0[%d] = %f et startdrawy0[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
}

void distance_2_sprite(t_info *info)
{
	int i;

	i = 0;
	while (i < info->nbsprite)
	{
		//barrel->distance[i] = 0;
		//printf("a.x = %f et a.y = %f\n", info->a.x, info->a.y);
		//printf("barrel.x = %f et barrel.y = %f\n", barrel->x[i], barrel->y[i]);
		//info->barrel.distance[i] = sqrt(pow(info->barrel.x[i] - info->a.x, 2) + pow(info->barrel.y[i] - info->a.y, 2));
		info->barrel.distance[i] = sqrt(pow(info->barrel.x[i] - info->a.x, 2) + pow(info->barrel.y[i] - info->a.y, 2));
		//printf("distance[%d] = %f\n",i, info->barrel.distance[i]);
		// printf("barrel->x[%d] = %f\n", i , barrel->x[i]);
		// printf("barrel->y[%d] = %f\n", i , barrel->y[i]);
		//printf("coucou\n");
		//printf("barrel.distance[%d] = %f\n", i, info->barrel.distance[i]);
		i++;
	}
}

void ft_sort_sprites(t_info *info)
{
	int	count;
	int	i;
	double tmp[3];
	
	count = 0;
	// while (i < info->nbsprite)
	// {
	// 	printf("barrel.distance[%d] = %f\n", i, info->barrel.distance[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < info->nbsprite)
	// {
	// 	printf("barrel.x[%d] = %f et barrel.y[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
	// 	i++;
	// }
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
	// i = 0;
	// while (i < info->nbsprite)
	// {
	// 	printf("barrel.x[%d] = %f et barrel.y[%d] = %f\n", i, info->barrel.x[i], i, info->barrel.y[i]);
	// 	i++;
	// }
}

void coordinatesofbarrel(t_info *info)
{
	int i;
	int j;
	int n;

	i = 0;  // lignes
	j = 0;  // colonnes
	n = 0;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
		//	printf("info->worldMap[%d][%d] = %d\n", i, j, info->worldMap[i][j]);
			if (info->worldMap[i][j] == 2) // si un sprite c'est 2
			{
				info->barrel.x[n] = j * 64 + 32; // a verifier pour voir si c'est bon 
				info->barrel.y[n] = (mapHeight - 1 - i) * 64 + 32; // a verifier pour voir si c'est bon
				n++;
			//	printf("n = %d\n", n);
				//printf("barrel.x = %f et barrel.y = %f\n", barrel->x[n], barrel->y[n]);
			}
			//n++;
			j++;
			//printf("j = %d\n", j);
		}
		i++;
		//printf("i = %d\n", i);
	}
}
