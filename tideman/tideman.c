#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle_check(int winner, int loser);
int find_source(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    printf("preferences:\n");
    for (int k = 0; k < candidate_count; k++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            printf("%i ", preferences[k][l]);
        }
        printf("\n");
    }
    printf("\n");

    add_pairs();
    sort_pairs();

    printf("sorted pairs:");
    for (int k = 0; k < pair_count; k++)
    {
        printf("%i%i ", pairs[k].winner, pairs[k].loser);
    }
    printf("\n");

    lock_pairs();
    print_winner();
    printf("\n");
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // loop through candidates and find match to (name)
    for (int i = 0; i < candidate_count; i++)
    {
        // if match - update ranks (ranks[i] is the voters ith preference of candidate(index))
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // if no match - don't update
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count - 1; j++)
        {
            int winner = ranks[i];    ////loop 1a (0) loop 1b (0)//loop 2a (1) loop 2b (1)
            int loser = ranks[j + 1]; // loop 1a (0+1) loop 1b (1+1)//loop 2a (1+1)
            preferences[winner][loser]++;
            // loop 1a preferences[0][1];
            // loop 1b preferences[0][2];
            // loop 2a preferences[1][2];

            // int preferedWinner[candidate_count][candidate_count];
            // int preferedLoser[candidate_count][candidate_count];
            // preferedWinner[winner][loser]++;
            // preferedLoser[loser][winner]++;

            // preferences[winner][loser] = preferedWinner[winner][loser] - preferedLoser[loser][winner];
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // for each block (preferences[i][j])
    // compare preferences[i][j] to [j][i]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // loop 1a (i = 0)(j = 0)//loop 1b (i = 0)(j = 1)//loop 2a (i = 1)(j = 1) loop 2b (i = 1)
            if (preferences[i][j] > preferences[j][i])
            {
                printf("%i has an edge over %i \n", i, j);
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                printf("%i has an edge over %i \n", j, i);
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    printf("\n");
    printf("unsorted pairs:");
    for (int k = 0; k < pair_count; k++)
    {
        printf("%i%i ", pairs[k].winner, pairs[k].loser);
    }
    printf("\n");

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // where i is a pair's winner and j is a pair's loser
    // loop through pairs and get strength of victory (value of preferences[i][j])
    // compare values and sort pairs array

    // set swap counter to non-zero value
    // repeat until swap counter is zero:
    //       reset swap counter to zero
    //       look at each ajacent pair
    //           if two adjacent elements are not in order, swap them and add 1 to swap counter
    int loops = pair_count;
    int last = pair_count - 1;

    int swapcounter = -1;

    for (int i = 0; i < loops; i++)
    {
        if (swapcounter == 0)
        {
            return;
        }

        swapcounter = 0;
        for (int j = last; j != 0; j--)
        {
            int wR = pairs[j].winner;     // winnerRight
            int lR = pairs[j].loser;      // loserRight
            int wL = pairs[j - 1].winner; // winnerLeft
            int lL = pairs[j - 1].loser;  // loserLeft

            int sR = preferences[wR][lR]; // StrengthRight
            int sL = preferences[wL][lL]; // strengthLeft
            // pairs[j] < pairs[j + 1]
            if (sR > sL)
            {
                pair right = pairs[j];
                pair left = pairs[j - 1];
                pairs[j] = left;
                pairs[j - 1] = right;
                swapcounter++;
            }
        }
        loops--;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop through pairs and check for cycle
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        bool cycle = cycle_check(winner, loser);

        if (!cycle)
        {
            locked[winner][loser] = true;
        }
    }

    // print locked[][] array
    printf("\n");
    printf("locked array:\n");
    for (int r = 0; r < candidate_count; r++)
    {
        for (int s = 0; s < candidate_count; s++)
        {
            printf("%i", locked[r][s]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
// 0 = Bob; 1 = Tom; 2 = Jerry
// if argument loser is already found in graph as a winner over the argument winner,
// then there is a cycle
bool cycle_check(int winner, int loser)
{
    while (winner != -1 && winner != loser)
    {
        bool found = false;

        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][winner] == true)
            {
                found = true;
                winner = i;
            }
        }

        if (!found)
        {
            winner = -1;
        }
    }

    if (winner == loser)
    {
        return true;
    }

    return false;
}

int find_source(void)
{
    int set_candidate = -1;
    // for candidate i..
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_pointed_to = false;
        // is candidate j pointing at them?
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                is_pointed_to = true;
            }
        }
        // if candidate i is not pointed to, then return as winner
        if (!is_pointed_to)
        {
            set_candidate = i;
            return set_candidate;
        }
    }
    return set_candidate;
}

// Print the winner of the election
void print_winner(void)
{
    int winner = find_source();
    printf("%s\n", candidates[winner]);
    return;
}