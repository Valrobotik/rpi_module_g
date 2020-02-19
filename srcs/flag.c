#include "lidar.h"
#include "main.h"
#include "time.h"
#include <stdlib.h>
#include <unistd.h>

void	get_resp(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;

		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, g_buff, LIDAR_BUFF);
				g_buff[res] = '\0';
			}
		}
}

int	interface_condition(void)
{
	char	buffer[READ_BUFF];
	int	wcount;
	//clock_t	start;

	while (1)
	{
		//wcount = write(g_fd, "M18\n", 4);	//sinon transmet au lidar
		ft_putstr("please enter a command for the robot\n");
		wcount = read(0, buffer, READ_BUFF);
		wcount = write(g_fd, "\n", 1);	//sinon transmet au lidar
		wcount = write(g_fd, buffer, wcount);	//sinon transmet au lidar
		/*
		ft_putstr("send :");
		wcount = write(1, buffer, wcount);	//sinon transmet au lidar
		ft_putstr("<<<\n");
		start = clock();
		while (clock() - start < 3000000)
		{
			wcount = read(g_fd, buffer, READ_BUFF);
			if (wcount > 0)
			{
				ft_putstr("respond :");
				wcount = write(1, buffer, wcount);	//sinon transmet au lidar
				ft_putstr("\n");
			}
		}
		*/
	}
}

int 	real_condition(void)
{
	ft_putstr("start_programm\n");
	start_robot();
	return (1);
}

#define LEN 3000
#include "open.h"

void	max_baudrate(void)
{
	char *buff = "SS115200\n";

	write(g_fd, buff, strlen(buff));		//change baude rate lidar
	set_interface_attribs(g_fd, 115200, 0);		//chage bauderate de l'interfacage
}

int	lidar(int argc, char **argv)
{
	int	wcount;
	char	buffer[READ_BUFF];
	int	res;

	if (g_fd > 0)
	set_interface_attribs(g_fd, 9600, 0);		//setup de l'interfacage
	max_baudrate();
	g_range = (int*)malloc(sizeof(int) * NBR_VAL);
	if (g_fd > 0)
		lidar_get_resp_print(g_fds, g_fd);
	while (1)
	{
		ft_putstr("please enter a command\n");
		wcount = read(0, buffer, READ_BUFF);
		buffer[wcount] = 0;
		if (!(res = lidar_cmd_is_premade(buffer)))
		{	//effectue la fonction si la commande est pre-enregistree
			wcount = write(g_fd, buffer, strlen(buffer));	//sinon transmet au lidar
			if (wcount < 0)
				return (-1);
			lidar_get_resp_print(g_fds, g_fd);
		}
		if (res == 2)
		{
			ft_putstr("disp on\n");
			setup_flag();
			display(argc, argv);
		}
	}
}

int	do_flag(char *str, int argc, char **argv)
{
	if (!strcmp(str, "-m"))
		return (real_condition());
	if (!strcmp(str, "-i"))
		return (interface_condition());
	if (!strcmp(str, "-l"))
		return (lidar(argc, argv));
	return (2);
}
