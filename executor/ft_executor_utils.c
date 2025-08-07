/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:42:54 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:47:02 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_search_dir(char **path, char *search)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*result;

	while (*path)
	{
		dp = opendir(*path);
		if (dp != NULL)
		{
			dirp = readdir(dp);
			while (dirp != NULL)
			{
				if (ft_strequals(search, dirp->d_name))
				{
					result = ft_read_dir(*path, dirp);
					closedir(dp);
					return (result);
				}
				dirp = readdir(dp);
			}
			closedir(dp);
		}
		path++;
	}
	return (NULL);
}

char	*ft_get_path(t_list *command, t_execution *exe, char **args)
{
	char	*path;
	char	**env;

	path = NULL;
	if (access(args[0], X_OK) == 0)
		path = ft_strcpy(args[0]);
	else
	{
		env = ft_split(ft_getenv(exe->envp, "PATH"), ':');
		if (env != NULL)
			path = ft_search_dir(env, command->token);
		ft_free_chartable(env);
	}
	return (path);
}

int	ft_count_commands(t_list **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		i++;
	return (i);
}

void	ft_create_pipes(t_list **commands, t_execution *exe)
{
	int	i;

	exe->total_c = ft_count_commands(commands);
	exe->pipes = malloc(sizeof(int) * (exe->total_c * 2 + 1));
	exe->pids = malloc(sizeof(int) * (exe->total_c));
	i = 0;
	while (i < exe->total_c - 1)
	{
		pipe(&exe->pipes[i * 2]);
		i = i + 1;
	}
}

void	ft_close_pipes(int *pipes, t_execution *exe)
{
	int	i;

	i = 0;
	while (i < exe->total_c - 1)
	{
		close(pipes[i * 2]);
		close(pipes[i * 2 + 1]);
		i++;
	}
}
