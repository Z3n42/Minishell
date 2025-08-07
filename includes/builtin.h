/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:19:02 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 12:42:17 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "definitions.h"
# include "utils.h"
# include "list.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>

void	ft_echo(t_list *command);
void	ft_export(t_list *command, t_execution *exe);
void	ft_unset(t_list *command, t_execution *exe);
void	ft_env(t_execution *exe);
void	ft_pwd(void);
void	ft_cd(t_list *command, t_execution *exe);
void	ft_exit(t_list *command);
void	ft_change_env(t_execution *exe, char *search, char *new);
#endif