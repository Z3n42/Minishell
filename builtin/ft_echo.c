/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:28:48 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 12:39:36 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_echo_arguments(int *start, t_list *node, int *n)
{
	int	j;

	if (*start == 0 && node->token[0] == '-' && ft_strlen(node->token) > 1)
	{
		j = 1;
		while (node->token[j])
		{
			if (node->token[j] != 'n')
				*start = 1;
			j++;
		}
		if (*start == 0 && ft_strlen(node->token) > 1)
			*n = 1;
	}
	else
		*start = 1;
}

void	ft_echo(t_list *command)
{
	int		start;
	int		n;
	t_list	*node;

	start = 0;
	n = 0;
	node = command->next;
	while (node != NULL)
	{
		if (start == 1)
			write(1, " ", 1);
		ft_echo_arguments(&start, node, &n);
		if (start == 1)
			write(1, node->token, ft_strlen(node->token));
		node = node->next;
	}
	if (n == 0)
		write(1, "\n", 1);
	g_global.errnor = 0;
}
