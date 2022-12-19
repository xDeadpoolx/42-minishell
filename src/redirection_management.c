/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/19 08:56:24 by mbertin          ###   ########.fr       */
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

	echo 1' '2" "3 Segfault si double execution

*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	rl_decomp je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/
void	execute_redirection(t_vault *data, int i, int j)
{
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if ((ft_strchr(data->rl_decomp[i], '>') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			|| (ft_strchr(data->rl_decomp[i], '<') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '<') == FALSE))
		{
			while (data->rl_decomp[i][j])
			{
				if ((data->rl_decomp[i][j] == '>'
					|| data->rl_decomp[i][j] == '<')
					&& !data->rl_decomp[i][j + 1])
					redir_in_next_array(data, i, &j, data->rl_decomp[i][j]);
				else if (data->rl_decomp[i][j] == '>'
				|| data->rl_decomp[i][j] == '<')
					redir_in_same_array(data, i, &j, data->rl_decomp[i][j]);
				j++;
			}
		}
		j = 0;
		i++;
	}
}

// void	redir_in_same_array(t_vault *data, int i, int *j, char c)
// {
// 	data->flag->chevron = c;
// 	find_redir_in_same_array(data, data->rl_decomp[i]);
// 	clean_redir(data, i);
// 	data->rl_decomp[i] = clean_the_chevron(data, data->rl_decomp[i]);
// 	if (data->rl_decomp[i][0] == '\0')
// 		find_decomposer_to_switch(data, i);
// 	*j = -1;
// 	stdout_redirection(data, data->flag->output);
// }

// void	find_redir_in_same_array(t_vault *data, char *rl_decomp_array)
// {
// 	int	i;
// 	int	len;
//
// 	i = 0;
// 	len = 0;
// 	while (rl_decomp_array[i] != data->flag->chevron)
// 		i++;
// 	i++;
// 	if (rl_decomp_array[i] == '\"' || rl_decomp_array[i] == '\'')
// 	{
// 		data->quote->quote_priority = rl_decomp_array[i];
// 		i++;
// 		while (rl_decomp_array[i] != data->quote->quote_priority)
// 		{
// 			i++;
// 			len++;
// 		}
// 	}
// 	else
// 		len = while_is_not_flag(rl_decomp_array, i) - i;
// 	data->flag->output = ft_calloc(sizeof(char), len + 1);
// 	len = 0;
// 	i = 0;
// 	while (rl_decomp_array[i] != data->flag->chevron)
// 		i++;
// 	i++;
// 	if (rl_decomp_array[i] == '\"' || rl_decomp_array[i] == '\'')
// 	{
// 		data->quote->quote_priority = rl_decomp_array[i];
// 		i++;
// 		while (rl_decomp_array[i] != data->quote->quote_priority)
// 		{
// 			data->flag->output[len] = rl_decomp_array[i];
// 			len++;
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		while (i < while_is_not_flag(rl_decomp_array, i))
// 		{
// 			data->flag->output[len] = rl_decomp_array[i];
// 			len++;
// 			i++;
// 		}
// 	}
// }

// void	clean_redir(t_vault *data, int i)// couper cette fonction en deux et la mettre dans un fichier redir_in_same_array
// {
// 	int		len;
// 	int		temp;
// 	int		begin;
// 	char	*str;
//
// 	len = 0;
// 	str = NULL;
// 	begin = 0;
// 	temp = 0;
// 	len = len_without_redir(data, i, temp, &begin);
// 	str = ft_calloc(sizeof(char), len + 1);
// 	if (begin != 0)
// 	{
// 		str[temp] = data->flag->chevron;
// 		temp++;
// 		while (data->rl_decomp[i][begin] && data->rl_decomp[i][begin] != '\0')
// 		{
// 			str[temp] = data->rl_decomp[i][begin];
// 			temp++;
// 			begin++;
// 		}
// 	}
// 	else
// 	{
// 		while (data->rl_decomp[i][begin] && data->rl_decomp[i][begin] != '\0')
// 		{
// 			while (data->rl_decomp[i][begin] != data->flag->chevron)
// 			{
// 				str[temp] = data->rl_decomp[i][begin];
// 				temp++;
// 				begin++;
// 			}
// 			str[temp] = data->rl_decomp[i][begin];
// 			temp++;
// 			begin++;
// 			if (data->rl_decomp[i][begin] == '\"' || data->rl_decomp[i][begin] == '\'')
// 				begin = while_quote(data, data->rl_decomp[i], begin);
// 			else
// 				begin = while_is_not_flag(data->rl_decomp[i], begin);
// 			if (data->rl_decomp[i][begin])
// 			{
// 				while (data->rl_decomp[i][begin] && data->rl_decomp[i][begin] != '\0')
// 				{
// 					str[temp] = data->rl_decomp[i][begin];
// 					temp++;
// 					begin++;
// 				}
// 			}
// 		}
// 	}
// 	free (data->rl_decomp[i]);
// 	data->rl_decomp[i] = str;
// }

// int	len_without_redir(t_vault *data, int i, int temp, int *begin)
// {
// 	int	len;
//
// 	len = 0;
// 	if (data->rl_decomp[i][temp] == data->flag->chevron)
// 	{
// 		temp++;
// 		len++;
// 		if (data->rl_decomp[i][temp] == '\'' || data->rl_decomp[i][temp] == '\"')
// 			temp = while_quote(data, data->rl_decomp[i], temp);
// 		else
// 			temp = while_is_not_flag(data->rl_decomp[i], temp);
// 		*begin = temp;
// 		if (data->rl_decomp[i][temp])
// 		{
// 			while (data->rl_decomp[i][temp])
// 			{
// 				temp++;
// 				len++;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		temp = while_is_not_flag(data->rl_decomp[i], temp);
// 		len = temp;
// 		if (data->rl_decomp[i][temp])
// 		{
// 			temp++;
// 			len++;
// 			temp = while_is_not_flag(data->rl_decomp[i], temp);
// 			len++;
// 			while (data->rl_decomp[i][temp])
// 			{
// 				temp++;
// 				len++;
// 			}
// 		}
// 	}
// 	return (len);
// }

void	stdout_redirection(t_vault *data, char *redirection)
{
	int	fd;

	fd = 0;
	if (data->flag->chevron == '>')
	{
		fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Probleme avec open sur fd_out\n");
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
	else if (data->flag->chevron == '<')
	{
		fd = open(redirection, O_RDONLY);
		if (fd == -1)
		{
			printf("Probleme avec open sur fd_out\n");
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
	free (redirection);
}
