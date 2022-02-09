/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:13:30 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 18:18:04 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_quote(char *str, int *i, char *quote, char *token)
{
	while ((ft_isspace(str[*i]) == 0 && str[*i] != '|' && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != ';' && str[*i] != '&'
			&& str[*i] != '\0') || *quote != '\0')
	{
		token[*i] = str[*i];
		if (str[*i] == *quote)
			*quote = '\0';
		else if ((str[*i] == '"' || str[*i] == '\'') && *quote == '\0')
			*quote = str[*i];
		*i = *i + 1;
	}
	if (*i == 0)
	{
		*quote = str[0];
		while (str[*i] == *quote)
		{
			token[*i] = str[*i];
			*i = *i + 1;
		}
		*quote = '\0';
	}
}

char	*ft_reduce(char *str, int *i, char *quote, char *token)
{
	ft_strcut_toend(str, *i);
	*i = 0;
	*quote = '\0';
	token = malloc(ft_strlen(str) + 1);
	ft_quote(str, i, quote, token);
	token[*i] = '\0';
	ft_strcut_toend(str, *i);
	return (token);
}

t_list	*ft_lexer(char *readl)
{
	char	*str;
	int		i;
	char	quote;
	char	*token;
	t_list	*start;

	start = NULL;
	str = ft_strcpy(readl);
	while (ft_strcontainstext(str))
	{
		i = 0;
		while (ft_isspace(str[i]))
			i++;
		token = ft_reduce(str, &i, &quote, token);
		if (start == NULL)
			start = ft_lstnew(token);
		else
			ft_lstadd_back(start, ft_lstnew(token));
		free(token);
	}
	free(str);
	return (start);
}
