#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
int print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // loop through candidates array and check for match to name arg
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // Jason Nancy Tom
    return false;
}

// Print the winner (or winners) of the election
int print_winner(void)
{
    // sort candidate array by votes
    int loops = candidate_count;
    int swapcounter = -1;

    for (int i = 0; i < loops - 1; i++)
    {
        if (swapcounter == 0)
        {
            return 0;
        }

        swapcounter = 0;
        for (int j = 0; j < candidate_count - 1; j++)
        {
            if (candidates[j].votes > candidates[j + 1].votes)
            {
                candidate left = candidates[j];
                candidate right = candidates[j + 1];
                candidates[j] = right;
                candidates[j + 1] = left;
                swapcounter++;
            }
        }
        loops--;
    }

    // define winners
    string winners[candidate_count];
    int last = candidate_count - 1;
    winners[0] = candidates[last].name;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[last].votes == candidates[i].votes)
        {
            winners[i + 1] = candidates[i].name;
        }
    }

    // print winners
    for (int i = 0; i < candidate_count; i++)
        if (winners[i])
        {
            printf("%s\n", winners[i]);
        }
    return 0;
}