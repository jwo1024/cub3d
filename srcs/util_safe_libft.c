/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:06:59 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/12 22:21:44 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"
#include	"util_error.h"

char	*safe_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		exit_with_error("NULL string found at substr");
	str = ft_substr(s, start, len);
	if (str == NULL)
		exit_with_error("malloc error");
	return (str);
}

char	**safe_ft_split(char const *s, char c)
{
	char	**str;

	if (s == NULL)
		exit_with_error("NULL string found at split");
	str = ft_split(s, c);
	if (str == NULL)
		exit_with_error("malloc error");
	return (str);
}

void	free_ft_split(char **sptr)
{
	int	idx;

	if (sptr)
	{
		idx = 0;
		while (sptr[idx])
			free(sptr[idx++]);
		free(sptr);
	}
}
