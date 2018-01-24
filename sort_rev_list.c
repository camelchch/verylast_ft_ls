/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rev_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:45:28 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/23 15:40:16 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	for_sort(t_dir *cp, t_dir **add, char *flags)
{
	if (ft_strchr(flags, 'u'))
	{
		if (cp->buf.st_atimespec.tv_sec > (*add)->buf.st_atimespec.tv_sec || \
				(cp->buf.st_atimespec.tv_sec == \
				(*add)->buf.st_atimespec.tv_sec && \
				ft_strcmp(cp->name, (*add)->name) > 0))
			*add = cp;
	}
	else if (cp->buf.st_mtimespec.tv_sec > (*add)->buf.st_mtimespec.tv_sec ||\
			(cp->buf.st_mtimespec.tv_sec == \
			(*add)->buf.st_mtimespec.tv_sec && \
			ft_strcmp(cp->name, (*add)->name) > 0))
		*add = cp;
}

static	void	sort_list(t_dir **list, char *flags)
{
	t_dir	*cp;
	t_dir	*add;
	t_dir	*re;

	re = NULL;
	if (!ft_strchr(flags, 'f'))
	{
		while (*list)
		{
			add = *list;
			cp = (*list)->next;
			while (cp)
			{
				if (ft_strchr(flags, 't'))
					for_sort(cp, &add, flags);
				else if (ft_strcmp(cp->name, add->name) < 0)
					add = cp;
				cp = cp->next;
			}
			re = add_lst(re, add);
			del_onelt(list, add);
		}
		*list = re;
	}
}

static	void	for_sort_d(t_dir *cp, t_dir **add, char *flags)
{
	if (ft_strchr(flags, 'f'))
	{
		if (cp->file < (*add)->file)
			*add = cp;
	}
	else
	{
		if (ft_strchr(flags, 'u'))
		{
			if (cp->file < (*add)->file || (cp->file == (*add)->file\
						&& cp->buf.st_atimespec.tv_sec > \
						(*add)->buf.st_atimespec.tv_sec))
				*add = cp;
		}
		else if (cp->file < (*add)->file || (cp->file == (*add)->file && \
					cp->buf.st_mtimespec.tv_sec > \
					(*add)->buf.st_mtimespec.tv_sec))
			*add = cp;
	}
}

static	void	sort_list_d(t_dir **list, char *flags)
{
	t_dir	*cp;
	t_dir	*add;
	t_dir	*re;

	re = NULL;
	while (*list)
	{
		add = *list;
		cp = (*list)->next;
		while (cp)
		{
			if (ft_strchr(flags, 'f') || ft_strchr(flags, 't'))
				for_sort_d(cp, &add, flags);
			else if (cp->file < add->file || (cp->file == add->file \
						&& ft_strcmp(cp->name, add->name) < 0))
				add = cp;
			cp = cp->next;
		}
		re = add_lst(re, add);
		del_onelt(list, add);
	}
	*list = re;
}

void			sort_rev_list(t_dir **list, char *flags, char c)
{
	t_dir	*cp;
	t_dir	*re;

	re = NULL;
	if (*list)
	{
		if (!ft_strchr(flags, 'd') && c == 'd')
			sort_list_d(list, flags);
		else
			sort_list(list, flags);
		if (ft_strchr(flags, 'r') && !ft_strchr(flags, 'f'))
		{
			while (*list)
			{
				cp = *list;
				while (cp->next)
					cp = cp->next;
				re = add_lst(re, cp);
				del_onelt(list, cp);
			}
			*list = re;
		}
	}
}
