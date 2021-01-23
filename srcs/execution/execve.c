/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramella <pramella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:47:14 by pramella          #+#    #+#             */
/*   Updated: 2020/06/16 02:25:24 by pramella         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **create_envp(t_env *env)
{
    int     i;
    size_t  len;
    char    **envp;

    if (!(envp = malloc(sizeof(*envp) * (env_size(env) + 1))))
        return (NULL);
    i = 0;
    while (env)
    {
        len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
        if (!(envp[i] = malloc(len)))
        {
            ft_fprintf(2, "minishell: malloc: %s\n", strerror(errno));
            break ;
        }
        ft_bzero(envp[i], len);
        ft_strlcat(envp[i], env->key, len);
        ft_strlcat(envp[i], "=", len);
        ft_strlcat(envp[i++], env->value, len);
        env = env->next;
    }
    envp[i] = NULL;
    return (envp);
}

static char **create_argv(t_list *tkn)
{
    size_t  i;
    size_t  len;
    char    **argv;

    len = ft_lstsize(tkn);
    if (!(argv = malloc(sizeof(*argv) * (len + 1))))
    {
        ft_fprintf(2, "minishell: malloc: %s\n", strerror(errno));
        return (NULL);
    }
    i = 0;
    while (i < len + 1 && tkn)
    {
        if (!(argv[i] = ft_strdup(tkn->content)))
            break ;
        tkn = tkn->next;
        ++i;
    }
    argv[i] = NULL;
    return (argv);
}

static void exec(t_shell *sh, char *path, char **av, char **ev)
{
    if (execve(path, av, ev) == -1)
    {
        ft_fprintf(2, "minishell: execve: %s\n", strerror(errno));
        free(path);
        ft_split_free(av);
        ft_split_free(ev);
        free_all(sh);
        exit(1);
    }
}

static void parent_code(t_shell *sh, t_cmd *cmd, pid_t pid)
{
    set_cmd_pipe(cmd);
    sig_child(pid);
    signal(SIGINT, sig_child);
    signal(SIGQUIT, sig_child);
    waitpid(pid, &sh->last_exit, 0);
    signal(SIGINT, sig_main);
    signal(SIGQUIT, sig_quit);
    sh->last_exit = WEXITSTATUS(sh->last_exit);
}

/*
** Sets terminal to canonical, forks parent process and sets up necessary pipe
** ends. Child constructs arguments and environment variables and execve's.
** Parents waits for child to terminate and saves its exit status.
*/

void        handle_execve(t_shell *sh, t_cmd *cmd, char *path)
{
    pid_t   pid;
    char    **ev;
    char    **av;

    tcsetattr(0, 0, &(sh->old_term));
    if ((pid = fork()) == -1)
        ft_fprintf(2, "minishell: fork: %s\n", strerror(errno));
    else if (pid > 0)
        parent_code(sh, cmd, pid);
    else
    {
        set_read_write_pipe(cmd);
        av = create_argv(cmd->token);
        ev = create_envp(sh->env);
        exec(sh, path, av, ev);
    }
    free(path);
    tcsetattr(0, 0, &(sh->new_term));
}
