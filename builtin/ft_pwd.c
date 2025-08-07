/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:30:45 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 12:40:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(void)
{
	char	*result;

	result = malloc(sizeof(char) * 2500);
	getcwd(result, 2500);
	write(1, result, ft_strlen(result));
	write(1, "\n", 1);
	g_global.errnor = 0;
	free(result);
}
