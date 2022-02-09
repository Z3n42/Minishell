/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:18:46 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 13:16:58 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_change_env(t_execution *exe, char *search, char *new)
{
	t_list	*tmp;
	char	*newvar;

	tmp = exe->envp;
	while (tmp)
	{
		if (ft_strstartwith(tmp->token, search))
		{
			free(tmp->token);
			tmp->token = ft_strcpy(search);
			tmp->token = ft_append_tostr(tmp->token, "=");
			tmp->token = ft_append_tostr(tmp->token, new);
			return ;
		}
		tmp = tmp->next;
	}
	newvar = ft_strcpy(search);
	newvar = ft_append_tostr(newvar, "=");
	newvar = ft_append_tostr(newvar, new);
	tmp = ft_lstnew(newvar);
	free(newvar);
	ft_lstadd_back(exe->envp, tmp);
}

void	ft_export_error(char *err)
{
	printf("bash: export: `");
	printf("%s", err);
	printf("': not a valid identifier\n");
	g_global.errnor = 1;
}

void	ft_export_aux(t_execution *exe, t_list *node)
{
	char	**var;
	int		i;

	i = 0;
	while (node->token[i] != '\0' && node->token[i] != '=')
		i++;
	if (node->token[i] == '=')
	{
		var = ft_split(node->token, '=');
		if (var != NULL)
		{
			ft_strcut_toend(node->token, ft_strlen(var[0]) + 1);
			if (var != NULL && (ft_isdigit(var[0][0]) == 1
				|| ft_strisalnum(var[0]) == 0))
				ft_export_error(var[0]);
			else if (var != NULL && var[1])
				ft_change_env(exe, var[0], node->token);
			else if (var != NULL && var[1] == NULL)
				ft_change_env(exe, var[0], "");
			if (var != NULL)
				ft_free_chartable(var);
		}
	}
}

void	ft_export(t_list *command, t_execution *exe)
{
	t_list	*node;

	g_global.errnor = 0;
	if (command->next == NULL || command->next->token == NULL)
		return ;
	node = command->next;
	while (node)
	{
		if (node->token[0] == '=')
			ft_export_error(node->token);
		else
		{
			ft_export_aux(exe, node);
		}
		node = node->next;
	}
	return ;
}
