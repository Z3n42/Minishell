/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:42:57 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:42:57 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_freelist(t_list *l)
{
	t_list	*act;
	t_list	*next;

	act = l;
	while (act)
	{
		next = act->next;
		ft_del_node(act, 0);
		act = next;
	}
}
