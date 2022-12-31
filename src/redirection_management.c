/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/31 15:59:23 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
echo test 1 > test > test1 > test2
echo test 2 >1 >2 >3
echo test 3> test> test1> test2
echo test 4>test>test1>test2
echo test 5>1 > 2> 3 >4 > 5
echo "test 6">"test" > "test1"
echo "test 7">"test" >"test1"
echo "test 8">"test"> "test1"> "test2"
echo "test 9">"test">"test1">"test2"
echo "test 10" > "test"> "test1" >"test2">"test3"> "test4"
echo "test 11" >test 4
echo test 12 > "tes>t" 
echo test 13 > "tes>t">test1
echo test 14 > 1> 2
echo test 15 >"tes>t">test1
echo test 16>"tes>t">test1

echo test 1 >> test >> test1 >> test2
echo test 2 >>1 >>2 >>3
echo test 3>> test>> test1>> test2
echo test 4>>test>>test1>>test2
echo test 5>>1 >> 2>> 3 >>4 >> 5
echo "test 6">"test" > "test1"
echo "test 7">"test" >"test1"
echo "test 8">"test"> "test1"> "test2"
echo "test 9">"test">"test1">"test2"
echo "test 10" > "test"> "test1" >"test2">"test3"> "test4"
echo "test 11" >test 4
echo test 12 > "tes>t"
echo test 13 > "tes>t">test1
echo test 14 > 1> 2
echo test 15 >"tes>t">test1
echo test 16>"tes>t">test1
*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	tab_arg je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/

void	execute_redirection(t_vault *data, int line, int j)
{
	while (data->tab_arg[line][j])
	{
		if (data->tab_arg[line][j] == '>' || data->tab_arg[line][j] == '<') // Vérifier si le </> est entre quote
			redir_in_same_array(data, line, &j, data->tab_arg[line][j]);
		j++;
	}
}

void	redirection(t_vault *data, char *redirection)
{
	if (data->flag->chevron == '>')
		stdout_redirection(data, redirection);
	else if (data->flag->chevron == '<')
		stdin_redirection(data, redirection);
}

void	stdout_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd != 0)
		close (data->flag->fd);
	if (data->flag->append == TRUE)
		data->flag->fd = open(redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->flag->fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->flag->fd == -1)
	{
		g_error_code = 1;
		error_message(data, "FD error");
	}
	if (dup2(data->flag->fd, STDOUT_FILENO) == -1)
	{
		g_error_code = 1;
		error_message(data, "FD error");
	}
	data->flag->append = FALSE;
}

void	stdin_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd != 0)
		close (data->flag->fd);
	if (data->flag->heredoc_delimiter == FALSE)
	{
		data->flag->fd = open(redirection, O_RDONLY);
		if (data->flag->fd == -1)
		{
			g_error_code = 1;
			error_message(data, "no such file or directory");
			ft_exit(data);
		}
		else
		{
			if (dup2(data->flag->fd, STDIN_FILENO) == -1)
			{
				g_error_code = 1;
				error_message(data, "FD error (dup2)");
			}
		}
	}
	else if (data->flag->heredoc_delimiter == TRUE)
	{
		data->flag->heredoc_fd = open("temp_heredoc", O_RDONLY);
		if (data->flag->heredoc_fd == -1)
		{
			g_error_code = 1;
			error_message(data, "heredoc - no such file or directory");
//			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		if (dup2(data->flag->heredoc_fd, STDIN_FILENO) == -1)
		{
			g_error_code = 1;
			error_message(data, "heredoc - I/O error (dup2)");
		}
		data->flag->heredoc_delimiter = FALSE;
	}
	//ne pas oublier le unlink du heredoc temp.
}
