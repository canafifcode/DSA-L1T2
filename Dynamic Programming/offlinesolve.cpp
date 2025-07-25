#include <bits/stdc++.h>
using namespace std;

// longest common sequencal subset

void local_allignment(string seq1, string seq2, int match_score, int mismatch_penalty, int gap_penalty)
{
    int size1 = seq1.length();
    int size2 = seq2.length();
    //(size1 + 1) x (size2 + 1) table because we also consider the empty string

    int table[size1 + 1][size2 + 1];

    // dynamic programming table
    for (int i = 0; i <= size1; i++)
    {
        for (int j = 0; j <= size2; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            }
            else
            {
                // if characters match, add match score, otherwise add mismatch penalty or gap penalty
                // we also consider the case of zeroing out the score if it goes negative
                if (seq1[i - 1] == seq2[j - 1])
                    table[i][j] = table[i - 1][j - 1] + match_score;
                else
                {
                    int max_gap = max(table[i - 1][j] + gap_penalty, table[i][j - 1] + gap_penalty);
                    int compare_zero = max(0, max_gap);
                    table[i][j] = max(table[i - 1][j - 1] + mismatch_penalty, compare_zero);
                }
            }
        }
    }

    // backtrack
    int max_value = 0;
    int max_i = 0, max_j = 0;
    for (int i = 0; i <= size1; i++)
    {
        for (int j = 0; j <= size2; j++)
        {
            max_value = max(max_value, table[i][j]);
            if (table[i][j] == max_value)
            {
                max_i = i;
                max_j = j;
            }
        }
    }

    string ali_seq1 = "", ali_seq2 = "";

    int i = max_i, j = max_j;

    while (i > 0 && j > 0 && table[i][j] > 0)
    {
        if (seq1[i - 1] == seq2[j - 1])
        {
            ali_seq1 = seq1[i - 1] + ali_seq1;
            ali_seq2 = seq2[j - 1] + ali_seq2;
            i--;
            j--;
        }
        else if (table[i - 1][j] + gap_penalty == table[i][j])
        {
            // gap in sq2
            ali_seq1 = seq1[i - 1] + ali_seq1;
            ali_seq2 = '-' + ali_seq2;
            i--;
        }
        else if (table[i][j - 1] + gap_penalty == table[i][j])
        {
            // gap in sq1
            ali_seq1 = '-' + ali_seq1;
            ali_seq2 = seq2[j - 1] + ali_seq2;
            j--;
        }
        else
        {
            ali_seq1 = seq1[i - 1] + ali_seq1;
            ali_seq2 = seq2[j - 1] + ali_seq2;
            i--;
            j--;
        }
    }

    cout << "Local alignment:" << endl;
    cout << ali_seq1 << endl;
    cout << ali_seq2 << endl;

    cout << "Maximum score: " << max_value << endl;
}

void global_allignment(string seq1, string seq2, int match_score, int mismatch_penalty, int gap_penalty)
{
    // Function to perform global alignment
    // cout<< "Global alignment is not implemented in this example." << endl;
    int size1 = seq1.length();
    int size2 = seq2.length();
    //(size1 + 1) x (size2 + 1) table because we also consider the empty string
    int table[size1 + 1][size2 + 1];

    for (int i = 0; i <= size1; i++)
        table[i][0] = i * gap_penalty;
    for (int j = 0; j <= size2; j++)
        table[0][j] = j * gap_penalty;

    // dynamic programming table
    for (int i = 1; i <= size1; i++)
    {
        for (int j = 1; j <= size2; j++)
        {
            if (seq1[i - 1] == seq2[j - 1])
                table[i][j] = table[i - 1][j - 1] + match_score;
            else
                table[i][j] = max(table[i - 1][j - 1] + mismatch_penalty, max(table[i - 1][j] + gap_penalty, table[i][j - 1] + gap_penalty));
        }
    }
    int i = size1, j = size2;
    string ali_seq1 = "", ali_seq2 = "";

    // backtrack
    while (i > 0 || j > 0)
    {
        // matched/unmatched-> diagonal movement
        if (i > 0 && j > 0 && table[i][j] == table[i - 1][j - 1] + ((seq1[i - 1] == seq2[j - 1]) ? match_score : mismatch_penalty))
        {
            ali_seq1 = seq1[i - 1] + ali_seq1;
            ali_seq2 = seq2[j - 1] + ali_seq2;
            i--;
            j--;
        }
        // not matched-> pick the maximum neighbor
        else if (i > 0 && table[i][j] == table[i - 1][j] + gap_penalty)
        {
            ali_seq1 = seq1[i - 1] + ali_seq1;
            ali_seq2 = '-' + ali_seq2;
            i--;
        }
        else if (j > 0 && table[i][j] == table[i][j - 1] + gap_penalty)
        {
            ali_seq1 = '-' + ali_seq1;
            ali_seq2 = seq2[j - 1] + ali_seq2;
            j--;
        }
    }

    cout << "Global alignment:" << endl;
    cout << ali_seq1 << endl;
    cout << ali_seq2 << endl;
    cout << "Maximum score: " << table[size1][size2] << endl;
    
}

int main()
{
    string seq1, seq2;
    cout << "Enter first sequence: ";
    cin >> seq1;
    cout << "Enter second sequence: ";
    cin >> seq2;
    int match_score, mismatch_penalty, gap_penalty;
    cout << "Enter match score: ";
    cin >> match_score;
    cout << "Enter mismatch penalty: ";
    cin >> mismatch_penalty;
    cout << "Enter gap penalty: ";
    cin >> gap_penalty;

    // cout << "Global alignment:" << endl;
    global_allignment(seq1, seq2, match_score, mismatch_penalty, gap_penalty);
    cout << endl;

    // cout << "Local alignment:" << endl;
    local_allignment(seq1, seq2, match_score, mismatch_penalty, gap_penalty);

    return 0;
}