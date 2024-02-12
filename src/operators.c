#include "_sh.h"

static int colon_operator(c_list *commands);
static int single_right_redirect(c_list *commands);
static int double_right_redirect(c_list *commands);
static int single_left_redirect(c_list *commands);
static int double_left_redirect(c_list *commands);

/**
 * route_operators - manages command launches when operators present
 * @commands: head of linked list of commands
 * Return: 0 upon success
*/

int route_operators(c_list *commands)
{
	c_list *tmp = NULL;
	int last = 0x0;

	for (
		tmp = commands;
		tmp;
		tmp = tmp->next, cmd_dt.op_index++, cmd_dt.cmd_index++
	)
	{
		if (tmp->command[0])
		{
			if (cmd_dt.op_array[cmd_dt.op_index] == 0x1)
				colon_operator(tmp), last = 0x1;
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x2)
			{
				if (!colon_operator(tmp))
					break;
			}
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x3)
				continue;
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x4)
			{
				if (colon_operator(tmp))
					break;
			}
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x5)
				single_right_redirect(tmp), last = 0x5;
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x6)
				double_right_redirect(tmp), last = 0x6;
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x7)
				single_left_redirect(tmp), last = 0x7;
			else if (cmd_dt.op_array[cmd_dt.op_index] == 0x8)
				double_left_redirect(tmp), last = 0x8;
			else if (tmp->cmd_index == cmd_dt.cmd_count && last <= 0x4 && last != 0x3)
				colon_operator(tmp);
		}
	}
	return (0);
}

/**
 * colon_operator - function for handling colon command operator
 * @commands: selected command segment input
 * Return: 1 on success, otherwise returns 0
*/

static int colon_operator(c_list *commands)
{
	int launch_error = 0;

	if (!commands)
		return (0);
	launch_error = launch_manager(commands->command);
	if (launch_error == 2 || launch_error == 13 || launch_error == 127)
	{
		error_processor(commands->command, launch_error);
		return (0);
	}
	return (1);
}

/**
 * single_right_redirect - function for handling single right redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

static int single_right_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_out = dup(STDOUT_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		fflush(stdout);
		close(fd);
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	else
		return (-1);
	return (0);
}

/**
 * double_right_redirect - function for handling double right redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

static int double_right_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_out = dup(STDOUT_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		fflush(stdout);
		close(fd);
		dup2(redir_out, STDOUT_FILENO);
		close(redir_out);
	}
	else
		return (-1);
	return (0);
}

/**
 * single_left_redirect - function for handling single left redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

static int single_left_redirect(c_list *commands)
{
	int fd = 0, launch_error = 0;
	int redir_in = dup(STDIN_FILENO);

	if (!commands || !commands->next->command[0] || commands->next->command[1])
		return (-1);
	fd = open(commands->next->command[0], O_RDONLY, 0644);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		launch_error = launch_manager(commands->command);
		if (launch_error == 13 || launch_error == 127)
			error_processor(commands->command, launch_error);
		close(fd);
		dup2(redir_in, STDIN_FILENO);
		close(redir_in);
	}
	else
		return (-1);
	return (0);
}

/**
 * double_left_redirect - function for handling double left redirects
 * @commands: selected command segment input
 * Return: 0 on success, otherwise returns -1
*/

static int double_left_redirect(c_list __attribute__((unused)) *commands)
{
	return (0);
}
