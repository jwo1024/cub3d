/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:57:43 by jaeyjeon          #+#    #+#             */
/*   Updated: 2023/01/11 15:59:01 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"util_error.h"
#include	"libft.h"
#include	<stdlib.h>

void	exit_with_error(char *error_msg)
{
	ft_putstr("Error\n");
	if (error_msg)
		ft_putstr(error_msg);
	exit(1);
}
