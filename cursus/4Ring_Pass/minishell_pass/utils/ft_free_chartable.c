/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_chartable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:40:32 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:42:32 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_free_chartable(char **list)
{
	int	i;

	if (!list)
		return ;
	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
