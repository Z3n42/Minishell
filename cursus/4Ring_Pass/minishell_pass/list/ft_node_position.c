/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:42:46 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:42:47 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	ft_node_position(t_list *start, t_list *find)
{
	int		i;
	t_list	*node;

	i = 0;
	node = start;
	while (node && node != find)
	{
		node = node->next;
		i++;
	}
	if (node == find)
		return (i);
	else
		return (-1);
}
