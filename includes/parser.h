/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:15:20 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/12 21:15:28 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "list.h"
# include "utils.h"

t_list	*ft_words_to_list(char *table[], t_list	*commands);
t_list	**ft_parse(t_list *list);
#endif