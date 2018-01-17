#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include "libft/libft.h"

typedef	struct	s_lformat
{
	char	*owner;
	char	*group;
	char	permi[10];
	char	*change_tm;
}				t_lformat;

typedef	struct	s_max
{
	int		m_link;
	int		m_owner;
	int		m_group;
	int		m_size;
	int		total;
}				t_max;

typedef	struct	s_dir
{
	struct stat buf;
	char		name[256];
	int			na_len;
	int			file;
	char		type;
	char		*path;
	t_lformat	long_f;
	struct s_dir *next;
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
	
}
#endif
