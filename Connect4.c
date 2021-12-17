#include <stdio.h>

#define ROW	6
#define	COL	7

int		lane = 0;
char	which_turn = 'X';
char	board[ROW][COL];

void	init_board(void)
{
	int	y;
	int	x;

	for (y = 0; y < ROW; y++)
	{
		for (x = 0; x < COL; x++)
			board[y][x] = ' ';
	}
}

void	print_board(void)
{
	char	lanes[30] = "  0   1   2   3   4   5   6  ";
	char	frame[30] = "|---|---|---|---|---|---|---|";
	int		y;
	int		x;
	
	printf("%s\n", lanes);
	printf("%s\n", frame);
	for (y = 0; y < ROW; y++)
	{
		for (x = 0; x < COL; x++)
			printf("| %c ", board[y][x]);
		printf("|\n");
		printf("%s\n", frame);
	}
}

int	stack_stone(void)
{
	static int	stack_pos_index[7] = {5, 5, 5, 5, 5, 5, 5};
	int			row_pos;
	
	row_pos = stack_pos_index[lane]; 
	if (stack_pos_index[lane] >= 0)
	{
		//board[stack_pos_index[lane]][lane] = which_turn;
		board[row_pos][lane] = which_turn;
		stack_pos_index[lane]--;
	}
	return (row_pos);
}

int	choose_lane(void)
{
	int	stack_pos;
	int	i;
	
	if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' && board[0][3] != ' '
		&&board[0][4] != ' ' && board[0][5] != ' ' && board[0][6] != ' ')
		return (-1);
	//i = 0;
	while (1)
	{
		printf("Choose lane: ");
		i = scanf("%d", &lane);
		if (i == 0)
		{
			scanf("%*s");
			printf("\nInvalid input! input only number!\n");
			continue ;
		}
		//else 
		if ((0 <= lane && lane <= 6) && (board[0][lane] == ' '))
		{
			stack_pos = stack_stone();
			break ;
		}
		else
			printf("\nCan't stack this lane! Choose different lane!\n");
	}
	return (stack_pos);
}

void change_turn(void)
{
	if (which_turn == 'X')
		which_turn = 'O';
	else
		which_turn = 'X';
}

int	check_len(char c, int stack_pos)
{
	int	i;
	int	j;
	int	count;
	int	x_move_way[8] = { 0,  0, 1, -1, 1, -1, -1,  1};
	int	y_move_way[8] = { 1, -1, 0,  0, 1, -1,  1, -1};

	count = 1;
	for (i = 0; i < 8; i++)
	{
		for (j = 1; j <= 3; j++)
		{
			if (((0 <= stack_pos + j * y_move_way[i]) && (stack_pos + j * y_move_way[i] < ROW))
				&& ((0 <= lane + j * x_move_way[i]) && (lane + j * x_move_way[i] < COL)))
			{
				if (board[stack_pos + j * y_move_way[i]][lane + j * x_move_way[i]] != c)
					break ;
				else	
					count += 1;
			}
		}
		if (count >= 4)
			return (1);
		if (i % 2)
			count = 1;
	}
	return (0);
}

int	main(void)
{
	int	stack_pos;

	init_board();
	print_board();

	while (1)
	{
		printf("\n%c turn!  ", which_turn);
		stack_pos = choose_lane();
		if (stack_pos == -1)
		{
			printf("draw!");
			break ;
		}
		print_board();
		if (check_len(which_turn, stack_pos))
		{
			printf("Player %c wins!\n", which_turn);
			break ;
		}
		change_turn();
	}
	return (0);
}
