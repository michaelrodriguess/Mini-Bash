#include "libft.h"

char	*remove_substr(char	*str, int from, int to)
{
	char	*ret;
	char	*temp;
	char	*suffix;

	ret = ft_substr(str, 0, from);
	suffix = ft_substr(str, to + 1, ft_strlen(&str[to]));
	temp = ret;
	ret = ft_strjoin(ret, suffix);
	free(temp);
	free(suffix);
	return (ret);
}
