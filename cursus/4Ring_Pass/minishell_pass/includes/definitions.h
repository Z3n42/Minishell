/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:22:46 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/19 12:54:36 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

typedef struct s_list
{
	char			*token;
	struct s_list	*next;
}	t_list;

typedef struct s_execution
{
	int		*pipes;
	int		*pids;
	int		total_c;
	int		total_f;
	int		redi;
	char	*outputfile;
	char	*output;
	int		in_redi;
	char	*inputfile;
	char	*inputpath;
	char	*error;
	t_list	*envp;
}	t_execution;

typedef struct s_global
{
	int	errnor;
	int	pid;
}	t_global;

t_global	g_global;
#endif