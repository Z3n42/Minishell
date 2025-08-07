/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:40:07 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:41:39 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strcat(char *dst, char *src)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 1));
	i = 0;
	while (dst && dst[i])
	{
		result[i] = dst[i];
		i++;
	}
	j = 0;
	while (src && src[j])
	{
		result[i + j] = src[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
