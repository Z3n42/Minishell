/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 09:47:50 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/17 19:41:12 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "utils.h"
# include <unistd.h>

t_list	*ft_del_node(t_list *start, int del);
void	ft_freelist(t_list *l);
void	ft_freelist2d(t_list **l);
t_list	*ft_get_last_node(t_list *lst);
int		ft_lstsize(t_list *lst);
char	**ft_list_to_char_table(t_list *lst);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list *last, t_list *new);
int		ft_node_position(t_list *start, t_list *find);
t_list	*ft_words_to_list(char *table[], t_list	*commands);
#endif