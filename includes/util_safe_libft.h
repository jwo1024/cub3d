/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_libft.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:10:00 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/12 17:35:34 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_SAFE_LIBFT_H
# define UTIL_SAFE_LIBFT_H

# include <stdio.h>

char	*safe_ft_substr(char const *s, unsigned int start, size_t len);
char	**safe_ft_split(char const *s, char c);
void	free_ft_split(char **s);

#endif
