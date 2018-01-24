/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:10:56 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/24 13:11:31 by saxiao           ###   ########.fr       */
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
		free(temp);
	}
}
