/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:43:27 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:43:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_back(t_list *last, t_list *new)
{
	t_list	*t;

	if (last)
	{
		t = ft_get_last_node(last);
		t->next = new;
	}
	else
		last = new;
}
