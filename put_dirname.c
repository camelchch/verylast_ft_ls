/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_dirname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:44:42 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/23 15:53:29 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	red(void)
{
	ft_printf(RED);
}

static	void	bg_yellow(void)
{
	ft_printf(BGYELLOW);
}

static	void	bg_blue(void)
{
	ft_printf(BGBLUE);
}

static	void	purple(void)
{
	ft_printf(PURPLE);
}

void			put_dirname(t_dir *list, int max)
{
	if (list->type == 'd')
		blue();
	else if (list->type == 'l')
		purple();
	else if (list->type == 'c')
		bg_yellow();
	else if (list->type == 'b')
		bg_blue();
	else if (!ft_strcmp(list->name, "ft_ls"))
		red();
	ft_printf("%s", list->name);
	color_reset();
	ft_printf("%*s", max - ft_strlen(list->name), " ");
}
