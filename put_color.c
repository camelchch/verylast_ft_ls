/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:42:40 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/24 13:11:50 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	blue(void)
{
	ft_printf(BLUE);
}

void	color_reset(void)
{
	ft_printf(RESET);
}

void	bg_red(void)
{
	ft_printf(BGRED);
}

int		for_putbigr(t_dir *list)
{
	if (list->file && ft_strcmp(list->name, ".")\
			&& ft_strcmp(list->name, ".."))
		return (1);
	return (0);
}

int		for_addirlt(char *path, t_dir *add)
{
	int		i;

	if (add->type == 'l')
		i = lstat(path, &(add->buf));
	else
		i = stat(path, &(add->buf));
	return (i);
}
