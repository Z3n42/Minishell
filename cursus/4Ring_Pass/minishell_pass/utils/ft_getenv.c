/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:31:53 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:40:30 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getenv(t_list *l, char *path)
{
	int		j;
	char	*value;
	t_list	*next;

	next = l;
	while (next)
	{
		value = next->token;
		j = 0;
		while (path[j])
		{
			if (value[j] != path[j])
				break ;
			j++;
		}
		if (value[j] == '=' && path[j] == '\0')
			return (&value[j + 1]);
		next = next->next;
	}
	return (NULL);
}
