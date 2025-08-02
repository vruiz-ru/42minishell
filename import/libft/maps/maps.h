/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:45:50 by aghergut          #+#    #+#             */
/*   Updated: 2025/08/02 20:20:31 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include "../strings/strings.h"

size_t	ft_mapsize(char **map);
char	**ft_mapdup(char **map);
void	ft_mapfree(char **map);
int		ft_mapitem_replace(char ***map, char *item, size_t idx);
int		ft_mapitem_del(char ***map_ref, size_t del_idx);
int		ft_mapitem_index(char **map, char *str);
int		ft_mapitem_add(char ***map_ref, char *item);
char	**ft_mapnew(char *item);

#endif