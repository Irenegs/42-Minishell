/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   struct.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: irene <irgonzal@student.42madrid.com>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/30 21:50:39 by pablo			 #+#	#+#			 */
/*   Updated: 2024/07/14 14:03:25 by irene			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

static char	**default_env(void)
{
	char	**env;
	char	*aux;

	env = malloc(4 * sizeof(char *));
	if (!env)
		return (write_error_null(1));
	aux = getcwd(NULL, 0);
	if (!aux)
	{
		ft_out(env);
		perror(NULL);
		return(NULL);
	}
	env[0] = create_env_entry("PWD", aux);
	free(aux);
	env[1] = create_env_entry("SHLVL", "1");
	env[2] = create_env_entry("_", "/usr/bin/env");
	env[3] = NULL;
	return (env);
}

static char	**ft_copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		total_variables;

	total_variables = 0;
	while (envp[total_variables])
		total_variables++;
	if (total_variables == 0)
		return (default_env());
	env_copy = (char **)malloc((total_variables + 1) * sizeof(char *));
	if (!env_copy)
		return (write_error_null(1));
	i = 0;
	while (i < total_variables)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			write(2, "Malloc error\n", 13);
			ft_out(env_copy);
			return (default_env());
		}
		i++;
	}
	env_copy[total_variables] = NULL;
	return (env_copy);
}

void	ft_init_mix(t_mix *data, char **envp)
{
	data->exit_status = 0;
	data->m_env = NULL;
	data->heredocs = NULL;
	data->pipesfd = NULL;
	data->m_env = ft_copy_env(envp);
}
