/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:57:00 by saxiao            #+#    #+#             */
/*   Updated: 2018/01/29 15:38:54 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "libft/libft.h"

# define RED "\033[0;31m"
# define BGRED "\033[7;31m"
# define GREEN "\033[0;32m"
# define BGYELLOW "\033[7;33m"
# define BGBLUE "\033[7;34m"
# define BLUE "\033[1;36m"
# define PURPLE "\033[0;35m"
# define RESET "\033[0m"
# define SIXMP 15778476
# define SIXMM -15778476

typedef	struct	s_lformat
{
	char	owner[256];
	char	group[256];
	char	change_tm[40];
	int		sixm;
	int		major;
	int		minor;
	char	aclatr;
}				t_lformat;

typedef	struct	s_max
{
	int		m_link;
	int		m_owner;
	int		m_group;
	int		m_size;
	int		m_maj;
	int		m_min;
	int		total;
}				t_max;

typedef	struct	s_dir
{
	struct stat		buf;
	char			name[256];
	char			permi[10];
	int				na_len;
	int				file;
	char			type;
	char			path[300];
	t_lformat		long_f;
	struct s_dir	*next;
}				t_dir;

typedef	struct	s_win
{
	int		max;
	int		line;
	int		col;
	int		ct_lt;
}				t_win;

typedef	struct	s_index
{
	char			flags[11];
	int				i;
	int				j;
	int				k;
	struct winsize	w;
	int				hv_acl;
	char			*tm;
	int				ct;
	t_dir			*temp;
}				t_index;

typedef	struct	s_ct
{
	int		i;
	int		j;
	int		ct;
}				t_ct;

void			color_reset(void);
void			blue(void);
void			bg_red(void);
void			put_dirname(t_dir *list, int max);
void			del_onelt(t_dir **list, t_dir *onelt);
void			get_dirlt(t_dir **list, DIR *sub_dp, char *sub, char *flags);
t_dir			*add_lst(t_dir *list, t_dir *add);
t_dir			*for_revlist(t_dir **list, char c);
void			sort_rev_list(t_dir **list, char *flags, char c);
void			init_lformat(t_dir *list, t_max *max, char *flags);
int				inclu_cbfile(t_dir *list);
int				inclu_dir(t_dir *list);
int				inclu_norfile(t_dir *list);
void			init_cbfile(t_dir *list, t_max *max);
void			init_dictype(t_dir *add);
void			reini_dir(t_dir **dic, t_dir **only_dir, t_index *dex, int w);
void			creat_dic(char **av, t_dir **dic);
void			freelist(t_dir *list);
void			eachdic(t_dir *only_dir, int winsize, t_index *dex);
int				for_putbigr(t_dir *list);
int				for_addirlt(char *path, t_dir *add);
void			put_bigr(char *dic, int winsize, t_dir *only, t_index *index);
void			inside_bigr(t_dir *s, char *sub_dic, int win, t_index *index);
void			init_forowngp(t_dir *list);
void			init_permi(t_dir *list);
void			for_init_permi(t_dir *list);
void			for_initchangetm(t_dir *list);
int				is_flagls(char c);
void			init_acllist(t_dir *list);
int				inclu_acl(t_dir *list);
void			put_oneflag(t_dir *list);
void			put_list(t_dir *list, t_index *index, int winsize);
#endif
