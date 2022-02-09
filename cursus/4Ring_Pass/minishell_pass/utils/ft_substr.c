/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:39:39 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:42:27 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	t_len;
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	dst = malloc (sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	t_len = 0;
	while (s[i])
	{
		if (i >= start && t_len < len)
		{
			dst[t_len] = s[i];
			t_len++;
		}
		i++;
	}
	dst[t_len] = 0;
	return (dst);
}
