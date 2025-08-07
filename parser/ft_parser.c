/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:37:54 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:31:51 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_parse_aux(t_list *list, int *i)
{
	t_list	*l;

	*i = 1;
	l = list;
	while (l)
	{
		if (ft_strequals(l->token, "|"))
			*i = *i + 1;
		l = l->next;
	}
	return (l);
}

t_list	*ft_next_cmd(t_list *l, int *i, int *j)
{
	t_list	*tmp;

	tmp = l->next;
	l->next = NULL;
	l = tmp;
	*i = *i + 1;
	*j = 0;
	return (l);
}

t_list	**ft_parse(t_list *list)
{
	int		i;
	int		j;
	t_list	*l;
	t_list	**result;

	l = ft_parse_aux(list, &i);
	result = malloc(sizeof(t_list *) * (i + 1));
	i = 0;
	l = list;
	j = 0;
	while (l)
	{
		if (j == 0)
			result[i] = l;
		j++;
		if (ft_strequals(l->token, "|"))
			l = ft_next_cmd(l, &i, &j);
		else
			l = l->next;
	}
	if (j == 0)
		result[i] = NULL;
	result[i + 1] = NULL;
	return (result);
}
