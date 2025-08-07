/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelist2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:13:26 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:43:01 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_freelist2d(t_list **l)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (l[i] != NULL)
	{
		tmp = l[i];
		while (tmp != NULL)
			tmp = ft_del_node(tmp, 0);
		i++;
	}
	free(l);
}
