#include <iostream>
#include <vector>

void ProcessBallots(std::vector<int> &votes, int &valid_ballots, int all_ballots);

bool IsBallotValid(int &number_of_party);

void DisplayNumbersOfSelectedParties(std::vector<int> &votes, int valid_ballots);

int main() {
    int parties;
    int all_ballots;

    std::cin >> parties >> all_ballots;

    std::vector<int> votes(parties);
    int valid_ballots;

    ProcessBallots(votes, valid_ballots, all_ballots);

    DisplayNumbersOfSelectedParties(votes, valid_ballots);

    return 0;
}

void ProcessBallots(std::vector<int> &votes, int &valid_ballots, const int all_ballots) {

    for (int i = 0; i < all_ballots; ++i) {

        int number_of_party;

        if (IsBallotValid(number_of_party)) {
            ++votes[number_of_party];
            ++valid_ballots;
        }
    }
}

bool IsBallotValid(int &number_of_party) {

    std::string ballot;
    std::cin >> ballot;
    bool is_already_one_vote = false;

    for (int i = 0; i < ballot.length(); ++i) {

        if (ballot[i] == '+') {
            if (!is_already_one_vote) {
                number_of_party = i;
                is_already_one_vote = true;
            } else {
                return false;
            }

        }

    }
    return is_already_one_vote;
}

void DisplayNumbersOfSelectedParties(std::vector<int> &votes, int valid_ballots) {
    for (int i = 0; i < votes.size(); ++i) {
        if (votes[i] != 0 && votes[i] / static_cast<double>(valid_ballots) >= 0.07)
            std::cout << i + 1 << ' ';
    }
}