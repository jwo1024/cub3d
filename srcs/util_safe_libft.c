/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:06:59 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 18:11:00 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*safe_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		; //error;
	str = ft_substr(s, start, len);
	if (str == NULL)
		; //error;
	return (str);
}
