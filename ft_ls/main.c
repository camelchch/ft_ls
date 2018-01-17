#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
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
		add->type = '-';
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

void	init_win(t_dir *list, int win_col, t_win *win)
{
	t_dir	*cp;

	cp = list;
	win->ct_lt = 0;
	win->max = 0;
	while (cp)
	{
		if (cp->na_len > win->max)
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
	if (!win->col)
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

void	sort_list(t_dir **list, char *flags)
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
			if (ft_strchr(flags, 't'))
			{
				if (ft_strchr(flags, 'u'))
				{
					if (cp->buf.st_atimespec.tv_sec > add->buf.st_atimespec.tv_sec || (cp->buf.st_atimespec.tv_sec == add->buf.st_atimespec.tv_sec && ft_strcmp(cp->name, add->name) > 0))
						add = cp;
				}
				else if (cp->buf.st_mtimespec.tv_sec > add->buf.st_mtimespec.tv_sec || (cp->buf.st_mtimespec.tv_sec == add->buf.st_mtimespec.tv_sec && ft_strcmp(cp->name, add->name) > 0))
					add = cp;
			}
			//else if (cp->file < add->file || (cp->file == add->file && ft_strcmp(cp->name, add->name) < 0))
			else if (ft_strcmp(cp->name, add->name) < 0)
				add = cp;
			cp = cp->next;
		}
		re = add_lst(re, add);
		del_onelt(list, add);
	}
	*list = re;
}

void	sort_list_d(t_dir **list, char *flags)
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
			if (ft_strchr(flags, 'f'))
			{
				if (cp->file < add->file)
					add = cp;
			}
			else if (ft_strchr(flags, 't'))
			{
				if (ft_strchr(flags, 'u'))
				{
					if (cp->file < add->file || (cp->file == add->file && cp->buf.st_atimespec.tv_sec > add->buf.st_atimespec.tv_sec))
						add = cp;
				}
				else if (cp->file < add->file || (cp->file == add->file && cp->buf.st_mtimespec.tv_sec > add->buf.st_mtimespec.tv_sec))
					add = cp;
			}
			else if (cp->file < add->file || (cp->file == add->file && ft_strcmp(cp->name, add->name) < 0))
				add = cp;
			cp = cp->next;
		}
		re = add_lst(re, add);
		del_onelt(list, add);
	}
	*list = re;
}

void	sort_rev_list(t_dir **list, char *flags, char c)
{
	t_dir	*cp;
	t_dir	*re;

	re = NULL;
	if (!ft_strchr(flags, 'f'))
	{
		if (c == 'd')
			sort_list_d(list, flags);
		else
			sort_list(list, flags);
		if (ft_strchr(flags, 'r'))
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

t_dir	*add_dirlt(t_dir *list, struct dirent *dir, char *dic)
{
	t_dir	*add;
	t_dir	*temp;
	char	*path;

	path = strdup(dic);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, dir->d_name);
	add = (t_dir *)malloc(sizeof(t_dir));
	init_fltype(dir, add);
	if (add->type == 'l')
		lstat(path, &(add->buf));
	else
		stat(path, &(add->buf));
	ft_strcpy(add->name, dir->d_name);
	add->path = path;
	add->na_len = ft_strlen(add->name);
	add->next = NULL;
	//free(path);
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

void	get_dirlt(t_dir **list, DIR *dp, char *dic, char *flags)
{
	struct	dirent	*dir;

	while ((dir = readdir(dp)))
	{
		if (dir->d_name[0] == '.')
		{
			if (ft_strchr(flags, 'a') || ft_strchr(flags, 'f'))
				*list = add_dirlt(*list, dir, dic);
		}
		else
			*list = add_dirlt(*list, dir, dic);
	}
	if (errno)
		perror("read directory failed");
}

void	init_owngp(t_dir *list, t_max *max)
{
	t_dir	*cp;

	cp = list;
	while (cp)
	{
		(cp->long_f).owner = (getpwuid(cp->buf.st_uid))->pw_name;
		cp = cp->next;
	}
	cp = list;
	while (cp)
	{
		(cp->long_f).group = (getgrgid(cp->buf.st_gid))->gr_name;
		cp = cp->next;
	}
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

void	init_m(t_dir *list, t_max *max)
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

void	init_permi(t_dir *list)
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

void	init_msize(t_dir *list, t_max *max)
{
	int		ma;
	t_dir	*cp;

	cp = list;
	ma = (list->buf).st_size;
	while (cp)
	{
		if ((cp->buf).st_size > ma)
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

void	init_lformat(t_dir *list, t_max *max, char *flags)
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
			cp->long_f.change_tm = ft_strdup(ctime((const time_t *)(&((cp->buf).st_atimespec).tv_sec)));
		else
			cp->long_f.change_tm = ft_strdup(ctime((const time_t *)(&((cp->buf).st_mtimespec).tv_sec)));
		cp = cp->next;
	}
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

void	put_lformat(t_dir *list, char *flags)
{
	t_max	max;
	char	link[256];

	if (list)
	{
		init_lformat(list, &max, flags);
		ft_printf("Total %d\n", max.total);
	}
	while (list)
	{
		//ft_printf("%s\n", list->long_f.permi);
		ft_printf("%c%s", list->type, (list->long_f).permi);
		ft_printf("%*d", max.m_link, (list->buf).st_nlink);
		if (!ft_strchr(flags, 'g'))
			ft_printf("%*s", max.m_owner, (list->long_f).owner);
		ft_printf("%*s", max.m_group, list->long_f.group);
		ft_printf("%*d", max.m_size, (list->buf).st_size);
		list->long_f.change_tm = list->long_f.change_tm + 3;
		ft_printf("%.13s", (list->long_f).change_tm);
		ft_printf(" %s", list->name);
		if (list->type == 'l')
		{
			readlink(list->path, link, 256);
			link[list->buf.st_size] = '\0';
			ft_printf(" -> %s", link);
		}
		ft_printf("\n");
		list = list->next;
	}
}

void	put_list(t_dir *list, char *flags, int winsize)
{
	if (ft_strchr(flags, 'l'))
		put_lformat(list, flags);
	else
		put_colum(list, winsize);
}

void	put_bigr(char *dic, int winsize, t_dir *only_dir, char *flags)
{
	DIR		*sub_dp;
	char	*sub_dic;
	t_dir	*sub_lt;
	char	*temp;

	sub_lt = NULL;
	sub_dic = ft_strjoin(dic, "/");
	temp = sub_dic;
	sub_dic = ft_strjoin(temp, only_dir->name);
	free(temp);
	sub_dp = opendir((const char *)sub_dic);
	get_dirlt(&sub_lt, sub_dp, sub_dic, flags);
	sort_rev_list(&sub_lt, flags, 'n');
	ft_printf("\n%s:\n", sub_dic);
	put_list(sub_lt, flags, winsize);
	if (inclu_dir(sub_lt))
	{
		while (sub_lt)
		{
			if (sub_lt->file)
				put_bigr(sub_dic, winsize, sub_lt, flags);
			sub_lt = sub_lt->next;
		}
	}
	closedir(sub_dp);
}


void	init_dictype(t_dir *add)
{
	add->file = 0;
	//	add->na_len = (int)ft_strlen(add->name);
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

t_dir	*add_dic(t_dir *list, char *dic)
{
	t_dir	*add;
	t_dir	*temp;

	add = (t_dir *)malloc(sizeof(t_dir));
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
	add->path = add->name;
	add->na_len = ft_strlen(add->name);
	add->next = NULL;
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

void	reini_dir(t_dir **dic, t_dir **only_dir, int *i, int *j)
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
	if (*dic)
		*i = 1;
	if ((*only_dir)->next)
		*j = 1;
}

void	eachdic(t_dir *only_dir, int winsize, int *i, int *j, char *flags)
{
	DIR		*dp;
	t_dir	*dir_lt;

	dir_lt = NULL;
	if (*i)
		ft_printf("\n");
	if (*j)
		ft_printf("%s:\n", only_dir->name);
	dp = opendir((const char *)only_dir->name);
	if (errno)
		perror("open directory failed");
	get_dirlt(&dir_lt, dp, only_dir->name, flags);
	sort_rev_list(&dir_lt, flags, 'k');
	put_list(dir_lt, flags, winsize);
	if (ft_strchr(flags, 'R') && inclu_dir(dir_lt))
	{
		while (dir_lt)
		{
			if (dir_lt->file)
				put_bigr(only_dir->name, winsize, dir_lt, flags);
			dir_lt = dir_lt->next;
		}
	}
	closedir(dp);
	*i = 1;
	*j = 1;
}

int		main(int ac, char **av)
{
	char	flags[10];
	int		i;
	int		j;
	t_dir	*dic;
	t_dir	*only_dir;
	//t_dir	*cp;
	struct	winsize w;
	ioctl(0,TIOCGWINSZ, &w);

	(void)ac;
	errno = 0;
	j = 0;
	only_dir = NULL;
	dic = NULL;
	i = set_flags_ls(flags, av);
	av = av + i;
	if (!*av)
		dic = add_dic(dic, ".");
	else
	{
		while (*av)
			dic = add_dic(dic, *av++);
	}
	i = 0;
	sort_rev_list(&dic, flags, 'd');
	reini_dir(&dic, &only_dir, &i, &j);
	put_list(dic, flags, w.ws_col);
	while (only_dir)
	{
		eachdic(only_dir, w.ws_col, &i, &j, flags);
		only_dir = only_dir->next;
	}
	return (0);
}

/*
   int		main(int ac, char **av)
   {
   DIR		*dp;
   char	flags[10];
   int		i;
   char	*dic;
   t_dir	*dir_lt;
   struct	winsize w;
   ioctl(0,TIOCGWINSZ, &w);

   (void)ac;
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
   get_dirlt(&dir_lt, dp, dic, flags);
   sort_rev_list(&dir_lt, flags);
   put_list(dir_lt, flags, w.ws_col);
   if (ft_strchr(flags, 'R') && inclu_dir(dir_lt))
   {
   while (dir_lt)
   {
   if (dir_lt->file)
   put_bigr(dic, w.ws_col, dir_lt, flags);
   dir_lt = dir_lt->next;
   }
   }
   return (0);
   }
   */
