/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:41:27 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:03:39 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <fcntl.h>
/* "<<" 

Feeds a block of text as stdin to a command.

Edge Cases:

    Delimiters: The ending delimiter (EOF or any chosen word) must appear alone on a line with no leading/trailing spaces.

    Quoting delimiter: If you quote the delimiter (e.g., <<'EOF'), variable and command expansion inside the here-doc is suppressed. Unquoted, expansions occur.

    Leading tabs: <<-EOF (dash/hyphen) strips leading TABs from the here-doc body, allowing you to indent here-doc blocks.

    Multiple here-docs: You can have several here-docs in the same command line (cat <<A <<B ...).

    Accidental file overwrite: Here-doc does NOT itself overwrite files, but if combined with redirection, order matters (e.g., cat <<EOF >file is safe; file is truncated before reading the here-doc).

    Command substitution: If expansions inside the here-doc cause errors (referencing unset vars, for example), it might affect the script’s flow.

    EOF conflicts: If "EOF" (or the delimiter word) appears by chance in the data, the here-doc ends prematurely.

*/

static void	write_to_tmp(int fd, char *line)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}

/* Bucle principal del heredoc */
int	ft_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	// 1. Abrir archivo temporal oculto para escribir
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc open"), -1);
	
	while (1)
	{
		line = readline("> "); // Prompt secundario
		if (!line) // Si el usuario pulsa Ctrl+D (EOF)
			break ;
		// Si la línea es EXACTAMENTE el delimitador, paramos
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		write_to_tmp(fd, line);
	}
	close(fd);
	
	// 2. Abrir el mismo archivo para lectura y devolver ese FD
	fd = open(".heredoc_tmp", O_RDONLY);
	
	// 3. Borrar el archivo del sistema (el FD sigue abierto para nosotros)
	unlink(".heredoc_tmp"); 
	
	return (fd);
}