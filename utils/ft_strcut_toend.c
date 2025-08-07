/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut_toend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:39:54 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:39:58 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_strcut_toend(char *str, int from)
{
	int	i;

	i = 0;
	while (str[from + i])
	{
		str[i] = str[from + i];
		i++;
	}
	str[i] = str[from + i];
}
