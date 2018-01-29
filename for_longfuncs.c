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

#include <time.h>
#include "ft_ls.h"

void	for_initchangetm(t_dir *cp)
{
	ft_strcpy((cp->long_f).change_tm, ctime((const time_t *)\
				&((cp->buf).st_atimespec).tv_sec));
	if (time(NULL) - (cp->buf).st_atimespec.tv_sec > SIXMP ||\
	time(NULL) - (cp->buf).st_atimespec.tv_sec < SIXMM)
		cp->long_f.sixm = 1;
}
