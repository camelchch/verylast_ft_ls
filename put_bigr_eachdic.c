/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_bigr_eachdic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:29:02 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/30 12:35:08 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

int				is_flagls(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || \
			c == 'u' || c == 'f' || c == 'g' || c == 'd' || c == '1');
}

static void		for_bigr(t_dir **sub_lt, char **sub_dic, t_dir *only, char *dic)
{
	char	*temp;

	*sub_lt = NULL;
	*sub_dic = ft_strjoin(dic, "/");
	temp = *sub_dic;
	*sub_dic = ft_strjoin(temp, only->name);
	free(temp);
}

void			put_bigr(char *dic, int winsize, t_dir *only, t_index *index)
{
	DIR		*sub_dp;
	char	*sub_dic;
	t_dir	*s;

	for_bigr(&s, &sub_dic, only, dic);
	sub_dp = opendir((const char *)sub_dic);
	if (sub_dp)
	{
		get_dirlt(&s, sub_dp, sub_dic, index->flags);
		sort_rev_list(&s, index->flags, 'n');
		ft_printf("\n%s:\n", sub_dic);
		put_list(s, index, winsize);
		if (inclu_dir(s))
			inside_bigr(s, sub_dic, winsize, index);
		freelist(s);
		closedir(sub_dp);
	}
	else
		perror("open directory failed");
	free(sub_dic);
}

static	void	for_eachdic(t_dir *only, int win, t_dir *dir_lt, t_index *dex)
{
	t_dir	*temp;

	while (dir_lt)
	{
		temp = dir_lt;
		if (dir_lt->file && ft_strcmp(dir_lt->name, ".") && \
				ft_strcmp(dir_lt->name, ".."))
			put_bigr(only->name, win, dir_lt, dex);
		dir_lt = dir_lt->next;
	}
}

void			eachdic(t_dir *only_dir, int winsize, t_index *dex)
{
	DIR		*dp;
	t_dir	*dir_lt;

	dir_lt = NULL;
	if (dex->i)
		ft_printf("\n");
	if (dex->j)
		ft_printf("%s:\n", only_dir->name);
	if ((dp = opendir((const char *)only_dir->name)))
	{
		get_dirlt(&dir_lt, dp, only_dir->name, dex->flags);
		sort_rev_list(&dir_lt, dex->flags, 'k');
		put_list(dir_lt, dex, winsize);
		if (ft_strchr(dex->flags, 'R') && inclu_dir(dir_lt))
			for_eachdic(only_dir, winsize, dir_lt, dex);
		dex->i = 1;
		dex->j = 1;
		freelist(dir_lt);
		closedir(dp);
	}
	else
		perror("open directory failed");
}
