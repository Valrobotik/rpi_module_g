#include "main.h"
#include <time.h>

/* ask if we have time to continue (within 95 secs ?)*/
/* Le Define STOP_TIME, est defini dans l'include et est en seconde */
/* le * 1000000 est pour convertir les micro secondes en secondes */

int	we_have_time(void)
{
	static int	loop_nbr;
	time_t	tmp;

	if (!loop_nbr)
		loop_nbr = 1;
	else
		loop_nbr++;
	if (clock() - g_time_start > STOP_TIME * 1000000) // time > Stop_time ?
	{
		tmp = time(&tmp);
		ft_putstr("\n----  END MATCH  ----\n");
		ft_putstr(asctime(gmtime(&tmp)));
		ft_putstr("\n");
		ft_putnbr(loop_nbr);
		ft_putstr(" loop done during the match\n");
		return (0); 		//we do not have time
	}	
	return (1);			//we do have time
}

/* stop moving, the match ended, his sight is based on motion */
void	freez_end_match(void)
{
	//send command to motors and actionners to stop, or activate a relay
	//to shut down everything
	write(g_fd, "M18\n", 4); //command to stop motion
	ft_putstr("asking robot to keep quiet\n");
}

void	print_side(void)
{
	g_side = bcm2835_gpio_lev(PINSIDE);	//PINSIDE est le define du pin du szitch size
	ft_putstr("   + On Side: ");
	if (g_side == B_SIDE)
		ft_putstr("BLUE");
	else
		ft_putstr("YELLOW");
	ft_putstr(" +\n");
}

t_pile	*setup_robot(void)
{
	static int	nbr_reset;
	t_pile		*pile;

	nbr_reset = nbr_reset ? nbr_reset + 1 : 1;	//if reset define and not null increment of 1, else set to 1 (ternaire)
	ft_putstr("\e[1;1H\e[2J");	//termcaps pour clear l'ecran
	write(g_fd, "M18\n", 4);	//bloquer les moteurs
	if (nbr_reset > 1) 
	{
		ft_putnbr(nbr_reset);
		ft_putstr(" RESET THIS\n");
	}
	g_side = bcm2835_gpio_lev(PINSIDE);
	pile = build_pile();		//stack the written command on a file, in a pile
	ft_putstr("MATCH DURATION SET TO: ");
	ft_putnbr(STOP_TIME);
	ft_putstr("\n");
	print_side();
	ft_putstr("ROBOT READY, PULL STRING TO START\n");
	return (pile);
}

int	start_robot(void)
{
	int	valueReed;
	int	valueReset;
	int	start;
	time_t	tmp;
	t_pile	*pile;

	start = 0;
	pile = setup_robot();					//set match
	while (1)
	{
		if (start == 1 && !we_have_time())		//si on est en match et que l'on a plus le temps, on freeze
		{
			freez_end_match();			//freez the motors and all actionners
			start  = 2;
		}
		valueReset = bcm2835_gpio_lev(PINRESET);
		valueReed = bcm2835_gpio_lev(PINREED);
		if (detect_falling(valueReed, REED) && !start)	//si le capteur reed est declanche HIGH->LOW (tirette)
		{
			g_time_start = clock();			//acknowledge time
			tmp = time(&tmp);
			ft_putstr("\n----  START MATCH  ----\n");
			write(g_fd, "M19\n", 4);		//unlock motor
			ft_putstr(asctime(gmtime(&tmp)));	//display time
			ft_putstr("\n");
			start = 1;
		}
		if (detect_rising(valueReset, RESET))		//si le bouton reset est appuye
		{
			start = 0;
			pile = setup_robot();			//reset match
		}
		if (start == 1)
			unpile_cmd(&pile);//for each command, send order
			//and wait till it suceed to proceed to the following
	}
	return (0);
}

