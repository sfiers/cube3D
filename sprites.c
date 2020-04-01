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
	//whichray = -(info->screenwidth/2);
	whichray = 0;
	//printf("barrel.a[%d] = %f et barrel.c[%d] = %f\n", i, info->barrel.a[i], i, info->barrel.c[i]);
	while (whichray < info->screenwidth - 1)
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
	return (whichray - 1);
}

int findmiddleray(t_info *info, int i, double x, double y)
{
	double distance;
	double distance2;
	int whichray;

	// info->barrel.pointtemp.x = info->barrel.startdrawx[i];
	// info->barrel.pointtemp.y = info->barrel.startdrawy[i];
	info->barrel.pointtemp.x = x;
	info->barrel.pointtemp.y = y;
	//printf("pointtemp.x = %f et pointtemp.y = %f\n", info->barrel.pointtemp.x, info->barrel.pointtemp.y);
	//whichray = -(info->screenwidth/2);
	whichray = 0;
	//printf("barrel.a[%d] = %f et barrel.c[%d] = %f\n", i, info->barrel.a[i], i, info->barrel.c[i]);
	while (whichray < info->screenwidth - 1)
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
		if (distance < distance2)
			break;
		whichray++;
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
	info->barrel.reverse = 0;
	distance_2_sprite(info); // distance entre le centre de chaque sprite et la joueur
	ft_sort_sprites(info); // tri les distances du + loin au + proche 
	printf("coucou\n");
	while (i < info->nbsprite)
	{	
		info->barrel.endray = 0;
		//info->barrel.height = projected_slice_hight(info, info->barrel.distance[i]);
		//info->barrel.height = spriteheight(info, info->barrel.distance[i]);
		//seekdrawend(info, i);
		initialise(info, i);
		info->barrel.height = spriteheight(info, info->barrel.distance[i]);
		if (fabs(info->barrel.spriteangle - info->angle) < 90 || fabs(info->barrel.spriteangle - info->angle) > 270)
		{	
			seekdrawstart(info, i);
			//seekdrawend(info, i);
			info->barrel.middleray = findmiddleray(info, i, info->barrel.x[i], info->barrel.y[i]);
			printf ("info->barrel.middleray = %d\n",  info->barrel.middleray);
			info->barrel.startray = findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]);
			printf ("info->barrel.startray = %d\n",  info->barrel.startray);
			info->barrel.spriteplandir.x = cos(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
			info->barrel.spriteplandir.y = sin(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
			printf("info->angle = %f\n", info->angle);
			info->barrel.startdrawx[i] = info->barrel.x[i] - info->barrel.spriteplandir.x;
	 		info->barrel.startdrawy[i] = info->barrel.y[i] - info->barrel.spriteplandir.y;
			printf("end spriteplandir1.x = %f et end spriteplandir1.y = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
			printf("enddraw[%d] = %f et enddrawy[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
			info->barrel.endray = findray(info, i, info->barrel.startdrawx[i], info->barrel.startdrawy[i]);
			printf("endray = %d\n", info->barrel.endray);
			info->barrel.startray >= 0 ? print_sprite(info, i) : print_sprite_reverse(info, i);
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
	start = (info->screenheight - info->barrel.height)/2;
	y = start;
	//printf("y = %d\n", y);
	//ratio = 64/info->barrel.height;
	ratio = 0;
	//printf("ratio = %f\n", ratio);
	info->tex_x = 0;
	info->tex_y = 0;
	whichray = info->barrel.startray;
	printf("startray = %d\n", whichray);
	while (info->tex_x < 64 && whichray < info->screenwidth)
	{
	//	printf("tex_x = %f\n", info->tex_x);
		while (y < info->screenheight && y < (start + info->barrel.height) && whichray < info->screenwidth)
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
			ratio = 64/info->barrel.height;
		}
		info->tex_y = 0;
		y = start;
		info->tex_x += ratio;
		whichray++;
	}
	//info->barrel.lastray = whichray - 1;
	printf("lastray = %d\n", whichray - 1);
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
	start = (info->screenheight - info->barrel.height)/2;
	y = start;
	//printf("y = %d\n", y);
	//ratio = 64/info->barrel.height;
	ratio = 0;
	//printf("ratio = %f\n", ratio);
	info->tex_x = 63;
	info->tex_y = 0;
	whichray = info->barrel.endray;
	//printf("endray = %d\n", whichray);
	while (info->tex_x >= 0 && whichray >= 0)
	{
	//	printf("tex_x = %f\n", info->tex_x);
		while (y < info->screenheight && y < (start + info->barrel.height) && whichray >= 0)
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
			ratio = 64/info->barrel.height;
		}
		info->tex_y = 0;
		y = start;
		info->tex_x -= ratio;
		whichray--;
	}
	printf("firstray = %d\n", whichray + 1);
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
	printf("spriteangle1 = %f\n", info->barrel.spriteangle);
	// le spriteangle doit etre proche du vrai angle 
	//info->barrel.spriteangle -= (info->barrel.spriteangle - info->angle);
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
		if (info->barrel.y[i] < info->a.y)
			info->barrel.spriteangle += 180;
	}
//	info->barrel.spriteangle -= (info->barrel.spriteangle - info->angle);
	//info->barrel.spriteplandir.x = round(cos(ft_deg2rad(info->barrel.spriteangle + 90)) * info->blocksize/2);
	// info->barrel.spriteplandir.x = round(cos(ft_deg2rad(info->angle + 90)) * info->blocksize/2);
	// info->barrel.spriteplandir.y = round(sin(ft_deg2rad(info->angle + 90)) * info->blocksize/2);
	info->barrel.spriteplandir.x = cos(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
	info->barrel.spriteplandir.y = sin(ft_deg2rad(info->angle + 90)) * info->blocksize/2;
	//info->barrel.spriteplandir.y = round(sin(ft_deg2rad(info->barrel.spriteangle + 90)) * info->blocksize/2);
//	printf("spriteangle = %f\n", info->barrel.spriteangle);
	printf("spriteplandir.x = %f et spriteplandir.y = %f\n", info->barrel.spriteplandir.x, info->barrel.spriteplandir.y);
}

void seekdrawstart(t_info *info, int i)
{
	info->barrel.startdrawx[i] = info->barrel.x[i] + info->barrel.spriteplandir.x;
	info->barrel.startdrawy[i] = info->barrel.y[i] + info->barrel.spriteplandir.y;
	printf("startdrawx[%d] = %f et startdrawy[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
}

// void seekdrawend(t_info *info, int i)
// {
// 	info->barrel.enddrawx[i] = info->barrel.x[i] - info->barrel.spriteplandir.x;
// 	info->barrel.enddrawy[i] = info->barrel.y[i] - info->barrel.spriteplandir.y;
// 	printf("startdrawx2[%d] = %f et startdrawy2[%d] = %f\n", i, info->barrel.startdrawx[i], i, info->barrel.startdrawy[i]);
// }

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
			if (info->worldMap[i][j] == 2)
			{
				info->barrel.x[n] = j * 64 + 32;
				info->barrel.y[n] = (mapHeight - 1 - i) * 64 + 32; 
				n++;
			}
			j++;
		}
		i++;
	}
}

double spriteheight(t_info *info, double distance)
{
	double corrected_distance;
	double height;

	corrected_distance = fishbowlsprite(info, distance); // il faut appliquer cette formule pour tout angle ou juste pour les angle droit??
	printf("---------------------------------------------------------corrected_distance %f\n", corrected_distance);
	height = projected_slice_hight(info, corrected_distance);
	return (height);
}

double fishbowlsprite(t_info *info, double distorted_distance)
{
	double corrected_distance;

	// // // // printf("angle_offset = %f\n", angle_offset);
	if (info->angle < info->barrel.spriteangle)
	{
		printf("----------------------------------------------------hey1\n");
		corrected_distance = distorted_distance * cos(ft_deg2rad(info->barrel.spriteangle - info->angle));
	}
	else
	{
		printf("----------------------------------------------------hey2\n");
		printf("----------------------------------------------------spriteangle = %f\n", info->barrel.spriteangle);
		corrected_distance = distorted_distance * cos(ft_deg2rad(info->angle - info->barrel.spriteangle));
	}
	return (corrected_distance);
}
