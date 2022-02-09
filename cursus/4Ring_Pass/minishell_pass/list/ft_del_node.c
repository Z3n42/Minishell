/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:48:28 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:51:17 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_del_node_aux(t_list *start, t_list *last, t_list *act, t_list *next)
{
	if (last == NULL)
	{
		free(start->token);
		free(start);
		return (next);
	}
	last->next = next;
	free(act->token);
	free(act);
	return (start);
}

t_list	*ft_del_node(t_list *start, int del)
{
	t_list	*last;
	t_list	*act;
	t_list	*next;
	int		i;

	if (!start)
		return (NULL);
	i = -1;
	last = NULL;
	act = start;
	next = act->next;
	while (++i < del)
	{
		last = act;
		act = next;
		next = next->next;
	}
	return (ft_del_node_aux(start, last, act, next));
}
