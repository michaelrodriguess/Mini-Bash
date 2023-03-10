#include "libft.h"

char	*insert_substr(char	*str, char *substr, int i)
{
	char	*ret;
	char	*temp;
	char	*suffix;

	ret = ft_substr(str, 0, i);
	suffix = ret;
	ret = ft_strjoin(ret, substr);
	free(suffix);
	suffix = ft_substr(str, i, ft_strlen(&str[i]));
	temp = ret;
	ret = ft_strjoin(ret, suffix);
	free(temp);
	free(suffix);
	return (ret);
}
