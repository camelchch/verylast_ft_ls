/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:10:56 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/30 11:27:56 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include "ft_ls.h"

void			for_initchangetm(t_dir *cp)
{
	ft_strcpy((cp->long_f).change_tm, ctime((const time_t *)\
				&((cp->buf).st_atimespec).tv_sec));
	if (time(NULL) - (cp->buf).st_atimespec.tv_sec > SIXMP ||\
	time(NULL) - (cp->buf).st_atimespec.tv_sec < SIXMM)
		cp->long_f.sixm = 1;
}

static	void	init_eachacl(t_dir *list)
{
	acl_t			acl;
	acl_entry_t		du;
	ssize_t			xattr;

	acl = NULL;
	xattr = 0;
	acl = acl_get_link_np(list->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &du) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(list->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		list->long_f.aclatr = '@';
	else if (acl)
	{
		list->long_f.aclatr = '+';
		acl_free(acl);
		acl = NULL;
	}
	else
		list->long_f.aclatr = ' ';
}

void			init_acllist(t_dir *list)
{
	while (list)
	{
		init_eachacl(list);
		list = list->next;
	}
}

int				inclu_acl(t_dir *list)
{
	while (list)
	{
		if (list->long_f.aclatr == '@' || list->long_f.aclatr == '+')
			return (1);
		list = list->next;
	}
	return (0);
}

void			put_oneflag(t_dir *list)
{
	t_dir	*cp;

	cp = list;
	while (cp)
	{
		put_dirname(cp, 0);
		ft_printf("\n");
		cp = cp->next;
	}
	freelist(list);
}
