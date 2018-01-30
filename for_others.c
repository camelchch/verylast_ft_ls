/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:10:56 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/30 12:34:51 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <stdlib.h>
#include "ft_ls.h"

void	init_forowngp(t_dir *list)
{
	while (list)
	{
		if (getpwuid(list->buf.st_uid))
			ft_strcpy((list->long_f).owner, \
					(getpwuid(list->buf.st_uid)->pw_name));
		else
			ft_strcpy((list->long_f).owner, ft_itoa(list->buf.st_uid));
		list = list->next;
	}
}

void	inside_bigr(t_dir *s, char *sub_dic, int winsize, t_index *index)
{
	t_dir	*temp;

	while (s)
	{
		temp = s;
		if (for_putbigr(s))
			put_bigr(sub_dic, winsize, s, index);
		s = s->next;
	}
}

void	for_init_permi(t_dir *list)
{
	if (list->buf.st_mode & S_ISUID)
	{
		if (list->permi[2] == 'x')
			list->permi[2] = 's';
		else
			list->permi[2] = 'S';
	}
	if (list->buf.st_mode & S_ISGID)
	{
		if (list->permi[5] == 'x')
			list->permi[5] = 's';
		else
			list->permi[5] = 'S';
	}
	if (list->buf.st_mode & S_ISVTX)
	{
		if (list->permi[8] == 'x')
			list->permi[8] = 't';
		else
			list->permi[8] = 'T';
	}
}

void	freelist(t_dir *list)
{
	t_dir	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

t_dir	*for_revlist(t_dir **list, char c)
{
	t_dir	*cp;
	t_dir	*re;
	int		no_dir;

	no_dir = 0;
	re = NULL;
	while (*list && !no_dir)
	{
		cp = *list;
		while (cp->next)
			cp = cp->next;
		if (!(c == 'd' && !cp->file))
		{
			re = add_lst(re, cp);
			del_onelt(list, cp);
		}
		else
			no_dir = 1;
	}
	return (re);
}
