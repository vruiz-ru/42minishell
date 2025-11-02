/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:34:49 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "structs.h"
#include "macros.h"
#include "import/libft/libft.h"
#include "../input/input.h"
#include "../builtins/builtins.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// HANDLERS
void		ft_sigint(int sig);
// UTILS
void	    ft_clear_strtok(void);
int			init_parent(t_process **parent, char *name, char *envp[]);
t_process	*init_child(t_process *parent);
char	    *ft_construct(t_list *tokens, char *str);
void	    free_process(t_process *proc);
#endif