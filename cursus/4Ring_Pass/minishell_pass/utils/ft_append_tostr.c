/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_tostr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:40:37 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:41:11 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_append_tostr(char *str, char *str2)
{
	char	*tmp;

	tmp = ft_strcat(str, str2);
	free(str);
	return (tmp);
}
