/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:37:36 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:38:05 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	ft_isvalidquotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		i++;
	}
	if (quote != '\0')
	{
		printf("-bash: quotes not closed.\n");
		return (0);
	}
	return (1);
}
