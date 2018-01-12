#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include "libft/libft.h"

typedef	struct	s_dir
{
	struct stat buf;
	char		name[256];
	int			na_len;
	int			file;
	char		type;
	struct s_dir *next;
}				t_dir;

typedef	struct	s_win
{
	int		max;
	int		line;
	int		col;
	int		ct_lt;
}				t_win;

#endif
