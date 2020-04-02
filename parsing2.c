/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduhamel <lduhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:18:04 by lduhamel          #+#    #+#             */
/*   Updated: 2020/04/02 20:46:19 by lduhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line.h"
#include <stdio.h>
#include "wolf.h"

int is_digit(char c)
{
	return(c >= '0' && c <= '9' ? 1 : 0);
}

// char	*ft_strdup1(char *s1)
// {
// 	char	*ptr;
// 	int		i;

// 	if (!s1 || !(ptr = (char*)malloc(sizeof(char) * (ft_strlen1(s1) + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

// int		ft_strlen1(char *s)
// {
// 	int i;

// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	printf("i = %d\n", i);
// 	return(i);
// }

// void	ft_putstr1(char *s)
// {
// 	int i;

// 	i = 0;
// 	if (s == NULL)
// 		return ;
// 	while (s[i] != '\0')
// 	{
// 		write(1, &s[i], 1);
// 		i++;
// 	}
// }

void		put_error1(t_element *elem)
{
	error_ret1(elem);
	if (elem->ret < 0)
		ft_putstr1("Error\n");
	ft_putstr1(elem->msg);
	//free(tab->error);
}

int			atoi_v1(t_element *elem)
{
	int			i;
	long long	result;
	long long	previous;

	i = 0;
	result = 0;
	previous = 0;
	while (elem->line[elem->i] >= '0' && elem->line[elem->i] <= '9')
	{
		result = result * 10 + (elem->line[elem->i++] - '0');
		if (result < previous || result > 9223372036854775807)
			return (-1);
		previous = result;
	}
	elem->i--;
	return (result);
}

int error_ret1(t_element *elem)
{
	elem->msg = NULL;
	if (elem->ret < 0)
	{
		if (elem->ret == -1)
			elem->msg = ft_strdup1("Resolution information must only be 2 numbers");
		if (elem->ret == -2)
			elem->msg = ft_strdup1("Resolution information should be 2 numbers, not less, not more");
		if (elem->ret == -3)
			elem->msg = ft_strdup1("The numbers must be >= 0");
		if (elem->ret == -4)
			elem->msg = ft_strdup1("The 3 color numbers must be separated by a comma (spaces allowed) /! be careful : no comma after the 3rd number");
		if (elem->ret == -5)
			elem->msg = ft_strdup1("Color numbers must be >= 0 and <= 255");
		if (elem->ret == -6)
			elem->msg = ft_strdup1("Color information should be 3 numbers, not less, not more");
		if (elem->ret == -7)
			elem->msg = ft_strdup1("Color information must only be 3 numbers");
		return (1);
	}
	return (0);
}

int resolution(t_element *elem, t_info *info)
{
	elem->flag = 0;
	elem->i++;
	while (elem->line[elem->i] != '\0')
	{
		if (elem->line[elem->i] == '-' && is_digit(elem->line[elem->i+1]))
			return (-3);
		else if (is_digit(elem->line[elem->i]))
		{
			info->screenwidth = (elem->flag == 0 ? atoi_v1(elem) : info->screenwidth);
			info->screenheight = (elem->flag == 1 ? atoi_v1(elem) : info->screenheight);
			elem->flag++;
		}
		else if (elem->line[elem->i] != ' ')
			return (-1);
		elem->i++;
	}
	return (elem->flag == 2 ? 1 : -2);
	info->screenwidth = (info->screenwidth > 3200 ? 3200 : info->screenwidth);
	info->screenwidth = (info->screenwidth < 320 ? 320 : info->screenwidth);
	info->screenheight = (info->screenheight > 1800 ? 1800 : info->screenheight);
	info->screenheight = (info->screenheight < 200 ? 200 : info->screenheight);
	return (1);
}

int if_digit(t_element *elem)
{
	elem->r = (elem->flag == 0 ? atoi_v1(elem) : elem->r);
	elem->g = (elem->flag == 1 ? atoi_v1(elem) : elem->g);
	elem->b = (elem->flag == 2 ? atoi_v1(elem) : elem->b);
	if (elem->r > 255 || elem->g > 255 || elem->b > 255)
		return (-5);
	elem->flag++;
	//printf("i = %d\n", elem->i);
	elem->i = (elem->line[elem->i+1] != '\0' && elem->flag < 3 ? elem->i + 1 : elem->i);
	if (elem->flag < 3)
	{
		while (elem->line[elem->i] != '\0' && elem->line[elem->i] == ' ')
			elem->i++;
	//	printf("line[i] = %c\n", elem->line[elem->i]);
		if (elem->line[elem->i] != ',')
			return (-4);
	}
	return (1);
}

void init_elem(t_element *elem)
{
	elem->r = 0;
	elem->g = 0;
	elem->b = 0;
	elem->flag = 0;
}

int color(t_element *elem, int trgb)
{
	int ret;

	trgb = 0;
	init_elem(elem);
	elem->i++;
	while (elem->line[elem->i] != '\0')
	{
	//	printf("i = %d\n", elem->i);
		if (elem->line[elem->i] == '-' && is_digit(elem->line[elem->i+1]))
			return (-5);
		else if (is_digit(elem->line[elem->i]))
		{
			if ((ret = if_digit(elem)) < 0)
				return (ret);
		}
		else if (elem->line[elem->i] != ' ')
		{
			if (elem->flag == 3 && elem->line[elem->i] == ',')
				return (-4);
			else
				return (-7);
		}
		elem->i++;
	}
	if (elem->flag != 3)
		return (-6);
	// printf("r = %d\n", elem->r);
	// printf("g = %d\n", elem->g);
	// printf("b = %d\n", elem->b);
	trgb = 65536 * elem->r + 256 * elem->g + elem->b;
	return (trgb);
}

int texture(t_element *elem, t_info *info, char *path)
{
	printf("Texture\n");
	return (1);
}

int read_elem(t_element *elem, t_info *info)
{
	elem->ret = 1;
	while (elem->ret == 1) //degager la boucle qui sert a rien
	{
		elem->i = 0;
		elem->ret = get_next_line(elem->fd, &elem->line);
		//printf("line = %s\n", elem->line);
		if (elem->line[0] == '\0')
			return (0);
		while (elem->line[elem->i] == ' ')
			elem->i++;
		if (elem->line[elem->i] == 'R')
		{
			if ((elem->ret = resolution(elem, info)) < 0)
				return (-1);
		}
		if (elem->line[elem->i] == 'S')
			texture(elem, info, elem->texture_sprite);
		if (elem->line[elem->i] == 'F')
		{
			if ((info->trgb_floor = color(elem, info->trgb_floor)) < 0)
			{
				elem->ret = info->trgb_floor;
				return (elem->ret);
			}
		}
		if (elem->line[elem->i] == 'C')
		{
			if ((info->trgb_ceiling = color(elem, info->trgb_ceiling)) < 0)
			{
				elem->ret = info->trgb_ceiling;
				return (elem->ret);
			}
		}
		if (elem->line[elem->i] == 'N' && elem->line[elem->i+1] == 'O')
			texture(elem, info, elem->texture_no);
		if (elem->line[elem->i] == 'S' && elem->line[elem->i+1] == 'O')
			texture(elem, info, elem->texture_so);
		if (elem->line[elem->i] == 'W' && elem->line[elem->i+1] == 'E')
			texture(elem, info, elem->texture_we);
		if (elem->line[elem->i] == 'E' && elem->line[elem->i+1] == 'A')
			texture(elem, info, elem->texture_ea);

		// printf("ceiling = %p\n", info->trgb_ceiling);
		// printf("floor = %p\n", info->trgb_floor);
	}
	return (0);
}

int	parsing2(t_element *elem, t_info *info)
{
	elem->counter = 0;
	if ((elem->fd = open("map2.txt", O_RDONLY)) < 0)
		return (-1);
	if (read_elem(elem, info) < 0)
	{
		put_error1(elem);
	}
	close(elem->fd);
	return(0);
}


// int main()
// {
// 	t_element	elem;
// 	t_info		info;
// 	if (parsing2(&elem, &info) == -1)
// 		return (-1);
// 	// while(1)
// 	// {
// 	// 	tab.len_tab = 0;
// 	// }
// }