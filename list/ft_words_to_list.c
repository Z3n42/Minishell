/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:43:33 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:43:33 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_words_to_list(char *table[], t_list	*commands)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (commands == NULL)
			commands = ft_lstnew(table[i]);
		else
			ft_lstadd_back(ft_get_last_node(commands), ft_lstnew(table[i]));
		i++;
	}
	return (commands);
}
