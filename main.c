#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ft_ls.h"


int		is_flag(char c)
{
	return (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't' || \
			c == 'u' || c == 'f' || c == 'g' || c == 'd');
}

int		set_flags_ls(char *flags, char **av)
{
	int		ct;
	int		i;

	ct = 1;
	i = 0;
	av++;
	ft_bzero(flags, 10);
	while (*av && (*av)[0] == '-' && (*av)[1])
	{
		(*av)++;
		while (**av)
		{
			if (is_flag(**av))
			{
				if(!strchr(flags, **av))
					flags[i++] = *((*av)++);
			}
			else
			{
				ft_printf("ft_ls: illegal option -- %c\n", **av);
				ft_printf("usage: ft_ls [-lRartufgd] [file ...]\n");
				exit(1);
			}
		}
		(av)++;
		ct++;
	}
	return (ct);
}

void	init_fltype(struct dirent *dir, t_dir *add)
{
	add->file = 0;
	add->na_len = (int)ft_strlen(add->name);
	if (dir->d_type == DT_BLK)
		add->type = 'b';
	else if (dir->d_type == DT_CHR)
		add->type = 'c';
	else if (dir->d_type == DT_DIR)
	{
		add->type = 'd';
		add->file = 1;
	}
	else if (dir->d_type == DT_FIFO)
		add->type = 'p';
	else if (dir->d_type == DT_LNK)
		add->type = 'l';
	else if (dir->d_type == DT_REG)
		add->type = 'f';
	else if (dir->d_type == DT_SOCK)
		add->type = 's';
}

void	del_onelt(t_dir **list, t_dir *onelt)
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

void	put_list(t_dir *list)
{
	while(list)
	{
		ft_printf("inside print list\n");
		ft_printf("%s type=%c file=%d na_len=%d\n", list->name, list->type, list->file, list->na_len);
		list = list->next;
	}
}

void	init_win(t_dir *list, int win_col, t_win *win)
{
	t_dir	*cp;

	cp = list;
	win->ct_lt = 0;
	win->max = 0;
	while (cp)
	{
		if (cp->na_len >win->max)
			win->max = cp->na_len;
		cp = cp->next;
	}
	win->max++;
	cp = list;
	while (cp)
	{
		(win->ct_lt)++;
		cp = cp->next;
	}
	win->col = win_col / win->max;
	if (!win_col)
		win_col = 1;
	win->line = win->ct_lt / win->col;
	if (win->ct_lt % win->col > 0)
		win->line++;
}

void	put_colum(t_dir *list, int win_col)
{
	t_dir *cp;
	t_dir *lt;
	int		i;
	int		j;
	int		ct;
	t_win	w;

	j = -1;
	init_win(list, win_col, &w);
//	ft_printf("winsize= %d, w.max =%d\n", win_col, w.max);
	lt = list;
	while (++j < w.line)
	{
		cp = lt;
		i = -1;
		while (++i < w.col && cp)
		{
			ct = 0;
			if (cp)
				ft_printf("%-*s", w.max, cp->name);
			while (cp && ct++ < w.line)
				cp = cp->next;
		}
		ft_printf("\n");
		lt = lt->next;
	}
}

t_dir	*add_lst(t_dir *list, t_dir *add)
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

void	sort_byname(t_dir **list)
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
			if (cp->file < add->file || (cp->file == add->file && ft_strcmp(cp->name, add->name) < 0))
				add = cp;
			cp = cp->next;
		}
		re = add_lst(re, add);
		del_onelt(list, add);
	}
	*list = re;
}

t_dir	*add_dirlt(t_dir *list, struct dirent *dir, char *dic)
{
	t_dir	*add;
	t_dir	*temp;
	char	*path;

	path = strdup(dic);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, dir->d_name);
	add = (t_dir *)malloc(sizeof(t_dir));
	stat(path, &(add->buf));
	ft_strcpy(add->name, dir->d_name);
	init_fltype(dir, add);
	add->next = NULL;
	free(path);
	if (!list)
		return (add);
	else
	{	temp = list;
		while (list->next)
			list = list->next;
		list->next = add;
		return (temp);
	}
}

void	get_dirlt(t_dir **list, DIR *dp, char *dic)
{
	struct	dirent	*dir;

	while ((dir = readdir(dp)))
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
			*list = add_dirlt(*list, dir, dic);
	}
	if (errno)
		perror("read directory failed");
}

int		inclu_dir(t_dir *list)
{
	while (list)
	{
		if (list->file == 1)
			return (1);
		list = list->next;
	}
	return (0);
}

t_dir	*dir_begin(t_dir *list)
{
	while (list && !list->file)
		list = list->next;
	return (list);
}

void	put_bigr(char *dic, int winsize, t_dir *only_dir)
{
	DIR		*sub_dp;
	char	*sub_dic;
	t_dir	*sub_lt;
	char	*temp;

	sub_lt = NULL;
	sub_dic = ft_strjoin(dic, "/");
	//ft_printf("sub_dic=%s\n", sub_dic);
	temp = sub_dic;
	sub_dic = ft_strjoin(temp, only_dir->name);
	//ft_printf("sub_dic=%s\n", sub_dic);
	free(temp);
	sub_dp = opendir((const char *)sub_dic);
	get_dirlt(&sub_lt, sub_dp, sub_dic);
	sort_byname(&sub_lt);
	ft_printf("\n%s:\n", sub_dic);
	put_colum(sub_lt, winsize);
	while (inclu_dir(sub_lt))
	{
		while (sub_lt && !sub_lt->file)
			sub_lt = sub_lt->next;
		put_bigr(sub_dic, winsize, sub_lt);
		sub_lt = sub_lt->next;
		}
	closedir(sub_dp);
}

int		main(int ac, char **av)
{
	DIR		*dp;
	char	flags[10];
	int		i;
	char	*dic;
	t_dir	*dir_lt;
	t_dir	*only_dir;
	struct	winsize w;
	ioctl(0,TIOCGWINSZ, &w);

	(void)ac;
	//ft_printf ("columns %d\n", w.ws_col);
	errno = 0;
	dic = NULL;
	dir_lt = NULL;
	i = set_flags_ls(flags, av);
	av = av + i;
	if (!*av)
		dic = ft_strdup(".");
	else
		dic = *av;
	dp = opendir((const char *)dic);
	if (errno)
		perror("open directory failed");
	get_dirlt(&dir_lt, dp, dic);
	sort_byname(&dir_lt);
//	put_list(dir_lt);
	put_colum(dir_lt, w.ws_col);
	if (inclu_dir(dir_lt))
	{
		only_dir = dir_begin(dir_lt);
		while (only_dir)
		{
			put_bigr(dic, w.ws_col, only_dir);
			only_dir = only_dir->next;
		}
	}
	//ft_printf("%s\n",dic);
	//ft_printf("%s\n",flags);
	return (0);
}
