/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablgarc <pablgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:50:39 by pablo             #+#    #+#             */
/*   Updated: 2024/06/23 16:33:17 by pablgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
	{
		free(env[i]);
	}
	*env = NULL;
	free(env);
}

//inicializar la struct
void	ft_init_mix(t_mix *data)
{
	data->exit_status = 0;
    data->m_argc = 0;
	data->m_env = NULL;
	data->m_argv = NULL;


}

//hace una copia del entorno
char	**ft_copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (envp[j])
		j++;
	env_copy = (char **)malloc((j + 1) * sizeof(char *));
	if (!env_copy)
		return (ft_free_env(env_copy), NULL);
	 while (i < j)
    {
        env_copy[i] = strdup(envp[i]);
        if (!env_copy[i])
        {
            while (i--)
                free(env_copy[i]);
            free(env_copy);
            return NULL;
        }
        i++;
    }
    env_copy[j] = NULL;
    return env_copy;
}

//hace copia de argumentos
char  **ft_copy_argv(int argc, char **argv)
{
    char **new_argv;
    int i;

    new_argv = (char **)malloc((argc + 1) * sizeof(char *));
    if (!new_argv)
    {
        perror("Error en la asignación de memoria");
        return (NULL);
    }
    i = 0;
    while ( i < argc)
    {
        new_argv[i] = strdup(argv[i]);
        if (!new_argv[i])
        {
            while (i--)
                free(new_argv[i]);
            free(new_argv);
            return NULL;
        }
        i++;
    }
    new_argv[argc] = NULL;
    return (new_argv);
}

//pasamos los datos a la struct
void	ft_fill_struct(t_mix *data, int argc, char **argv, char **envp)
{
	data->m_env = ft_copy_env(envp);
    data->m_argv = ft_copy_argv(argc, argv);
    data->m_argc = argc; 
}