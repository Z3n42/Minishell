/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontainstext.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:30:56 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:41:31 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcontainstext(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
