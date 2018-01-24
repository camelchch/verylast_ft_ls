/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:30:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/24 12:22:58 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include "ft_ls.h"

static	void	init_owngp(t_dir *list, t_max *max)
{
	t_dir	*cp;

	cp = list;
	init_forowngp(list);
	list = cp;
	while (list)
	{
		if (getgrgid(list->buf.st_gid))
			ft_strcpy((list->long_f).group, \
					(getgrgid(list->buf.st_gid)->gr_name));
		else
			ft_strcpy((list->long_f).group, ft_itoa(list->buf.st_gid));
		list = list->next;
	}
	list = cp;
	max->m_owner = ft_strlen((list->long_f).owner);
	cp = list->next;
	while (cp)
	{
		if (max->m_owner < (int)ft_strlen((cp->long_f).owner))
			max->m_owner = ft_strlen((cp->long_f).owner);
		cp = cp->next;
	}
	max->m_owner++;
}

static	void	init_m(t_dir *list, t_max *max)
{
	t_dir	*cp;

	cp = list->next;
	max->m_link = (list->buf).st_nlink;
	while (cp)
	{
		if ((cp->buf).st_nlink > max->m_link)
			max->m_link = (cp->buf).st_nlink;
		cp = cp->next;
	}
	max->m_link = nb_dg_inbase(max->m_link, 10) + 2;
	max->m_group = ft_strlen((list->long_f).group);
	cp = list->next;
	while (cp)
	{
		if (max->m_group < (int)ft_strlen((cp->long_f).group))
			max->m_group = ft_strlen((cp->long_f).group);
		cp = cp->next;
	}
	max->m_group = max->m_group + 2;
}

static	void	init_permi(t_dir *list)
{
	int		i;

	i = 0;
	while (i < 9)
		list->long_f.permi[i++] = '-';
	list->long_f.permi[i] = '\0';
	if (list->buf.st_mode & S_IRUSR)
		list->long_f.permi[0] = 'r';
	if (list->buf.st_mode & S_IWUSR)
		list->long_f.permi[1] = 'w';
	if (list->buf.st_mode & S_IXUSR)
		list->long_f.permi[2] = 'x';
	if (list->buf.st_mode & S_IRGRP)
		list->long_f.permi[3] = 'r';
	if (list->buf.st_mode & S_IWGRP)
		list->long_f.permi[4] = 'w';
	if (list->buf.st_mode & S_IXGRP)
		list->long_f.permi[5] = 'x';
	if (list->buf.st_mode & S_IROTH)
		list->long_f.permi[6] = 'r';
	if (list->buf.st_mode & S_IWOTH)
		list->long_f.permi[7] = 'w';
	if (list->buf.st_mode & S_IXOTH)
		list->long_f.permi[8] = 'x';
}

static	void	init_msize(t_dir *list, t_max *max)
{
	int		ma;
	t_dir	*cp;

	cp = list;
	ma = (list->buf).st_size;
	while (cp)
	{
		if (cp->type != 'c' && cp->type != 'b' && (cp->buf).st_size > ma)
			ma = (cp->buf).st_size;
		cp = cp->next;
	}
	max->m_size = nb_dg_inbase(ma, 10) + 2;
	cp = list;
	max->total = 0;
	while (cp)
	{
		max->total = max->total + cp->buf.st_blocks;
		cp = cp->next;
	}
}

void			init_lformat(t_dir *list, t_max *max, char *flags)
{
	t_dir *cp;

	init_owngp(list, max);
	init_m(list, max);
	init_msize(list, max);
	cp = list;
	while (cp)
	{
		init_permi(cp);
		cp = cp->next;
	}
	cp = list;
	while (cp)
	{
		if (ft_strchr(flags, 'u'))
			ft_strcpy((cp->long_f).change_tm, ctime((const time_t *)\
						&((cp->buf).st_atimespec).tv_sec));
		else
			ft_strcpy((cp->long_f).change_tm, ctime((const time_t *)\
						&((cp->buf).st_mtimespec).tv_sec));
		cp = cp->next;
	}
	if (inclu_cbfile(list))
		init_cbfile(list, max);
}
