/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:15 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/12 21:15:38 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include <stdio.h>
# include "definitions.h"
# include "utils.h"

int	ft_isvalidquotes(char *str);
int	ft_forbidden_char(char *str);
int	ft_command_checker(t_list **commands);
#endif