/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:39:24 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:51:40 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_expand(char *token, int *i, t_list *envp)
{
	int		j;
	char	envvar[2500];
	char	*result;
	char	init;

	result = NULL;
	j = 0;
	*i = *i + 1;
	init = token[*i];
	if (init == '?')
		return (ft_itoa(g_global.errnor));
	if (ft_isalpha(init) == 0 && init != '\0')
		return (NULL);
	while (ft_isalpha(init) && token[*i] && ft_isalnum(token[*i]) == 1)
	{
		envvar[j] = token[*i];
		j++;
		*i = *i + 1;
	}
	envvar[j] = '\0';
	if (ft_strlen(envvar) == 0)
		return (ft_append_ctostr(result, '$'));
	*i = *i - 1;
	result = ft_strcpy(ft_getenv(envp, envvar));
	return (result);
}

char	*ft_clean_aux(t_list *next, t_list *envp, char *quote)
{
	int		i;
	char	*str;
	char	*tmp;

	i = -1;
	str = NULL;
	while (next->token[++i])
	{
		if ((next->token[i] == '"' || next->token[i] == '\'') && *quote == '\0')
			*quote = next->token[i];
		else if (next->token[i] == *quote)
			*quote = '\0';
		else if (*quote != '\'' && next->token[i] == '$'
			&& next->token[i + 1] != '\0')
		{
			tmp = ft_expand(next->token, &i, envp);
			str = ft_append_tostr(str, tmp);
			if (tmp)
				free(tmp);
		}
		else
			str = ft_append_ctostr(str, next->token[i]);
	}
	return (str);
}

void	ft_clean_quote(t_list *command, t_list *envp)
{
	t_list	*next;
	char	quote;
	char	*str;
	int		i;

	next = command;
	i = 0;
	while (next)
	{
		quote = '\0';
		str = ft_clean_aux(next, envp, &quote);
		free(next->token);
		next->token = ft_strcpy(str);
		free(str);
		next = next->next;
	}
}
