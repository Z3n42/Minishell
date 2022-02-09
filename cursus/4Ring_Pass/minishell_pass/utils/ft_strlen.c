/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:29:29 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/14 16:34:49 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlen(char *str)
{
	int	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size = size + 1;
	return (size);
}
