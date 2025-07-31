/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:49:41 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/31 15:38:20 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


#define PROMPT		" 👉 "
#define REPLY	"💬"
#define WRONG		"❓"

#define CLEAR	"\e[1;1H\e[2J"	// \033[H\033[J"

typedef struct Shell_utils
{
	char	**tokens;
	char	*line;
	char	*prompt;
	char	*res;
	bool	running;
}	t_utils;


// char    *current_prompt(char *cwd);

char	*get_prompt(void);
char	*get_variable(char *envp[], char *var_name);
char	*get_cwd(char *flags);
void	get_env(char *envp[]);

int		is_variable(char *envp[], char *var_name);

void	handle_sigint(int sig);

void	free_map(char **map);
void	free_main(t_utils *main);
#endif