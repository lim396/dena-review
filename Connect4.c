#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW	6
#define	COL	7
#define EMPTY 0
#define BLACK 1
#define WHITE 2

int		lane;
int		stack_pos;
int		board[ROW][COL];
int		which_turn = BLACK;


void	print_board(void)
{
	char	lanes[30] = "  0   1   2   3   4   5   6  ";
	char	frame[30] = "|---|---|---|---|---|---|---|";
	int		x;
	int		y;
	
	printf("%s\n", lanes);
	printf("%s\n", frame);
	for (y = 0; y < ROW; y++)
	{
		for (x = 0; x < COL; x++)
			printf("| %s ", (board[y][x] == BLACK) ? "●" : (board[y][x] == WHITE) ? "○" : " ");
		printf("|\n");
		printf("%s\n", frame);
	}
}

void	stack_stone(void)
{
	static int	stack_pos_index[7] = {5, 5, 5, 5, 5, 5, 5};
	
	stack_pos = stack_pos_index[lane];
	if (stack_pos >= 0)
	{
		board[stack_pos][lane] = which_turn;
		stack_pos_index[lane]--;
	}
}

void	choose_lane(void)
{
	int	i;
	
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
		if ((0 <= lane && lane <= 6) && (board[0][lane] == EMPTY))
			break ;
		printf("\nCan't stack this lane! Choose different lane!\n");
	}
}

void change_turn(void)
{
	which_turn = (which_turn == BLACK) ? WHITE : BLACK;
}

bool	check_len(int which_turn)
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
			if ((stack_pos + j * y_move_way[i]) < 0 || ROW <= (stack_pos + j * y_move_way[i]))
				continue ;
			if((lane + j * x_move_way[i]) < 0 || COL <= (lane + j * x_move_way[i]))
				continue ;
			if (board[stack_pos + j * y_move_way[i]][lane + j * x_move_way[i]] != which_turn)
				break ;
			count += 1;
		}
		if (count >= 4)
			return (true);
		if (i % 2)
			count = 1;
	}
	return (false);
}

bool	is_draw()
{
	if (board[0][0] != EMPTY && board[0][1] != EMPTY && board[0][2] != EMPTY && board[0][3] != EMPTY
		&& board[0][4] != EMPTY && board[0][5] != EMPTY && board[0][6] != EMPTY)
		return (true);
	return (false);
}

int	main(void)
{
	system("clear");
	print_board();

	while (1)
	{
		printf("\n%s turn!  ", (which_turn == BLACK) ? "●" : "○");
		choose_lane();
		stack_stone();
		system("clear");
		print_board();
		if (is_draw())
		{
			printf("draw!\n");
			break ;
		}
		if (check_len(which_turn))
		{
			printf("Player %s wins!\n", (which_turn == BLACK) ? "●" : "○");
			break ;
		}
		change_turn();
	}
	return (0);
}
