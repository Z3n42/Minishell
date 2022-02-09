/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:55:31 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:54:52 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_dup_output(t_execution *exe)
{
	int	infd;

	if (exe->redi == 1)
	{
		infd = open(exe->outputfile, O_RDWR | O_CREAT | O_TRUNC, 0755);
		dup2(infd, 1);
	}
	else if (exe->redi == 2)
	{
		infd = open(exe->outputfile, O_RDWR | O_CREAT | O_APPEND, 0755);
		dup2(infd, 1);
	}
	if ((exe->redi == 1 || exe->redi == 2))
		close(infd);
}

void	ft_dup_input(t_execution *exe)
{
	int	infd;
	int	newpipe[2];

	if (exe->in_redi == 1)
	{
		infd = open(exe->inputpath, O_RDWR, 0755);
		if (infd != -1)
			dup2(infd, 0);
		else
		{
			printf("-bash: %s: No such file or directory\n", exe->inputfile);
			exit (127);
		}
	}
	else if (exe->in_redi == 2)
	{
		pipe(newpipe);
		write(newpipe[1], exe->inputfile, ft_strlen(exe->inputfile));
		dup2(newpipe[0], 0);
		close(newpipe[0]);
		close(newpipe[1]);
	}
	if (exe->in_redi == 1)
		close(infd);
}

void	ft_default_pipes(t_execution *exe, int i)
{
	if (i == (exe->total_c - 1) && exe->total_c >= 2)
	{
		dup2(exe->pipes[(i - 1) * 2], 0);
	}
	if (i == 0 && exe->total_c >= 2)
	{
		dup2(exe->pipes[1], 1);
	}
	else if ((i < (exe->total_c - 1)) && exe->total_c >= 3)
	{
		dup2(exe->pipes[(i - 1) * 2], 0);
		dup2(exe->pipes[(i * 2) + 1], 1);
	}
}
