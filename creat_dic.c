/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_dic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:13:50 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/29 15:13:49 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

void			init_dictype(t_dir *add)
{
	add->file = 0;
	if (S_ISBLK(add->buf.st_mode))
		add->type = 'b';
	else if (S_ISCHR(add->buf.st_mode))
		add->type = 'c';
	else if (S_ISDIR(add->buf.st_mode))
	{
		add->type = 'd';
		add->file = 1;
	}
	else if (S_ISFIFO(add->buf.st_mode))
		add->type = 'p';
	else if (S_ISLNK(add->buf.st_mode))
		add->type = 'l';
	else if (S_ISREG(add->buf.st_mode))
		add->type = '-';
	else if (S_ISSOCK(add->buf.st_mode))
		add->type = 's';
}

static	t_dir	*add_dic(t_dir *list, char *dic)
{
	t_dir	*add;

	add = (t_dir *)malloc(sizeof(t_dir));
	if (lstat(dic, &(add->buf)) == -1)
		stat(dic, &(add->buf));
	if (errno)
	{
		ft_printf("ls: %s : ", dic);
		perror("");
		errno = 0;
		return (list);
	}
	init_dictype(add);
	ft_strcpy(add->name, dic);
	ft_strcpy(add->path, add->name);
	add->na_len = ft_strlen(add->name);
	init_permi(add);
	add->next = NULL;
	return (add_lst(list, add));
}

void			creat_dic(char **av, t_dir **dic)
{
	if (!(*av))
		*dic = add_dic(*dic, ".");
	else
	{
		while (*av)
			*dic = add_dic(*dic, *av++);
	}
}

static	void	for_renidir(t_dir **dic, t_dir **only_dir, t_index *dex)
{
	if (*dic)
		dex->i = 1;
	if ((*dic && *only_dir) || (*only_dir && (*only_dir)->next))
		dex->j = 1;
	if (!*dic)
		dex->k = 1;
}

void			reini_dir(t_dir **dic, t_dir **only_dir, t_index *dex, int w)
{
	t_dir	*cp;
	int		no_dir;

	no_dir = 1;
	cp = *dic;
	if (cp->file)
	{
		*only_dir = cp;
		*dic = NULL;
	}
	else
	{
		while (cp && no_dir)
		{
			if (cp->next && cp->next->file)
			{
				*only_dir = cp->next;
				no_dir = 0;
				cp->next = NULL;
			}
			cp = cp->next;
		}
	}
	for_renidir(dic, only_dir, dex);
	put_list(*dic, dex, w);
}
