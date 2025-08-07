/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:39:49 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:43:34 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "definitions.h"
# include "builtin.h"
# include "list.h"
# include "utils.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "syntax.h"

int		ft_execute(t_list **commands, t_execution *e);
char	*ft_get_path(t_list *command, t_execution *exe, char **args);
void	ft_create_pipes(t_list **commands, t_execution *exe);
void	ft_close_pipes(int *pipes, t_execution *exe);
t_list	*ft_output(t_list *command, t_execution *exe);
t_list	*ft_check_input(t_list *command, t_execution *exe);
void	ft_clean_quote(t_list *command, t_list *envp);
void	ft_default_pipes(t_execution *exe, int i);
void	ft_dup_output(t_execution *exe);
void	ft_dup_input(t_execution *exe);
char	*ft_read_dir(char *path, struct dirent *dirp);
#endif