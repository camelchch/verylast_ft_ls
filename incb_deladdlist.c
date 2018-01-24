/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incb_deladdlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:22:51 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/22 12:23:55 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "ft_ls.h"

void			del_onelt(t_dir **list, t_dir *onelt)
{
	t_dir	*del;
	t_dir	*pre;
	t_dir	*temp;

	del = *list;
	pre = NULL;
	while (del && ft_strcmp(del->name, onelt->name))
	{
		pre = del;
		del = del->next;
	}
	if (!pre)
	{
		temp = *list;
		*list = (*list)->next;
		temp->next = NULL;
	}
	else
	{
		pre->next = del->next;
		del->next = NULL;
	}
}

t_dir			*add_lst(t_dir *list, t_dir *add)
{
	t_dir	*temp;

	if (!list)
		list = add;
	else
	{
		temp = list;
		while (temp->next)
			temp = temp->next;
		temp->next = add;
	}
	return (list);
}

int				inclu_cbfile(t_dir *list)
{
	while (list)
	{
		if (list->type == 'c' || list->type == 'b')
			return (1);
		list = list->next;
	}
	return (0);
}

static	void	init_maxmm(t_dir *list, t_max *max)
{
	t_dir	*c;

	max->m_maj = 0;
	max->m_min = 0;
	c = list;
	while (c)
	{
		if ((c->type == 'c' || c->type == 'b') && c->long_f.major > max->m_maj)
			max->m_maj = c->long_f.major;
		c = c->next;
	}
	max->m_maj = nb_dg_inbase(max->m_maj, 10);
	max->m_maj++;
	c = list;
	while (c)
	{
		if ((c->type == 'c' || c->type == 'b') && c->long_f.minor > max->m_maj)
			max->m_min = c->long_f.minor;
		c = c->next;
	}
	max->m_min = nb_dg_inbase(max->m_min, 10);
	max->m_min++;
}

void			init_cbfile(t_dir *list, t_max *max)
{
	t_dir	*cp;

	cp = list;
	while (cp)
	{
		if (cp->type == 'c' || cp->type == 'b')
		{
			cp->long_f.major = major(cp->buf.st_rdev);
			cp->long_f.minor = minor(cp->buf.st_rdev);
		}
		cp = cp->next;
	}
	if (inclu_cbfile(list))
	{
		init_maxmm(list, max);
		if (inclu_norfile(list) && max->m_size < max->m_maj + max->m_min + 1)
			max->m_size = max->m_maj + max->m_min + 1;
	}
}
