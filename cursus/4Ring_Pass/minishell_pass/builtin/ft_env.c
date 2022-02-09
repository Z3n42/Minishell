/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:29:46 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/14 17:34:27 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_execution *exe)
{
	t_list	*node;

	node = exe->envp;
	while (node)
	{
		write(1, node->token, ft_strlen(node->token));
		write(1, "\n", 1);
		node = node->next;
	}
	g_global.errnor = 0;
}
