/*

		Author: Kalashnikov Ivan

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //For uint8_t and so on...
#include <stddef.h> //For size_t, ptrdiff_t and so on...

typedef struct team
{
	uint8_t name[50UL];
	uint16_t games;
	uint32_t points;
	uint32_t fund;
} team;


//---------------Functions-----------------
void readTeam(team *pt_team);
static int cmd(const void *p1, const void *p2);


int main(void) 
{
	uint32_t q_teams = 0;
	printf("Enter quantity of teams: ");
	scanf("%d", &q_teams);

	team **teams = (team**)malloc(sizeof(team*) * q_teams);
	if (teams == NULL)
	{
		fprintf(stderr, "\nERROR: cannot allocate memory\n");
		exit(-1);
	}
	for (size_t i = 0; i < q_teams ; i++)
	{
        teams[i] = (team*)malloc(sizeof(team));
		if (teams[i]== NULL)
		{
			fprintf(stderr, "\nERROR: cannot allocate memory\n");
			exit(-1);
		}

        readTeam(teams[i]);
    } 

	printf("You input:\n");
	for (size_t i = 0; i < q_teams; i++)
	{
		printf("%d team: %s\n", i + 1, teams[i]->name);
			printf("\t %d games\n", teams[i]->games);
			printf("\t %d points\n", teams[i]->points);
			printf("\t %d fund\n", teams[i]->fund);
	}

	qsort(teams, q_teams, sizeof(team*), cmd);

	printf("\nSort by ascending prize pool\n");
	for (size_t i = 0; i < q_teams; i++)
	{
		printf("%s team:\n", teams[i]->name);
			printf("\t prize pool = %d\n", teams[i]->fund);
	}

	for (size_t i = 0; i < q_teams; i++)
		free(teams[i]);

	free(teams);

	printf("----Programm is finished----\n");
	return 0;
}

//---------------Functions-----------------
void readTeam(team *pt_team)
{
	printf("\nEnter name of team: ");
	scanf("%s", pt_team->name);
	printf("Enter number of games %s team: ", pt_team->name);
	scanf("%d", &pt_team->games);
	printf("Enter number of points %s team: ", pt_team->name);
	scanf("%d", &pt_team->points);
	printf("Enter fund size %s team: ", pt_team->name);
	scanf("%d", &pt_team->fund);
}

static int cmd(const void *p1, const void *p2)
{
	team *tm1 = *(team**)p1;
    team *tm2 = *(team**)p2;
    return tm1->fund - tm2->fund;
}