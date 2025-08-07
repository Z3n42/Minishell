/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:58:24 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:10:40 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_read_dir(char *path, struct dirent *dirp)
{
	char			*tmp;
	char			*result;

	tmp = ft_strcat(path, "/");
	result = ft_strcat(tmp, dirp->d_name);
	free(tmp);
	return (result);
}
