/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iibanez- <iibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:45 by iibanez-          #+#    #+#             */
/*   Updated: 2022/01/14 16:04:26 by iibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>
# include "definitions.h"
# include "list.h"

char	*ft_append_ctostr(char *str, char c);
char	*ft_append_tostr(char *str, char *str2);
int		ft_atoi(const char *str);
void	ft_free_chartable(char **list);
char	*ft_getenv(t_list *l, char *path);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(char c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
void	ft_str_to_lower(char *str);
char	*ft_strcat(char *dst, char *src);
int		ft_strcontainstext(char *str);
char	*ft_strcpy(char *src);
void	ft_strcut_toend(char *str, int from);
int		ft_strequals(char *str1, char *str2);
int		ft_strisalnum(char *str);
int		ft_strlen(char *str);
int		ft_strstartwith(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
