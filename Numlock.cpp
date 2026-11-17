//
// Created by Jamayah Walker on 11/14/26.
//
#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Player {
    string name;
    int Value;
};

struct Boss_Number {
    int Value;
};


struct Wizard {
    int Value;
};

void initializeGame(Player &player);
int generateNextValue();
void playGame(Player &player);
Wizard spawnWizard(int playerVal);

int main() {
    Player player;
    cout << "Welcome to the game!" << endl;

    cout << "Enter your name: " << endl;
    cin  >> player.name;

    bool gameRunning = true;
    int choice;

    while (gameRunning) {
        cout << "\n=== NUMELOCK ===" << endl;
        cout << "\n=== MAIN MENU ===" << endl;
        cout << "\n1. Play Game";
        cout << "\n2. Quit Game";
        cout << "\nEnter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Choice! We NEED a player for this game to run!" << endl;
            continue;
        }

        if (choice == 1) {
            playGame(player);
        } else if (choice == 2) {
            cout << "You chose to quit the game!" << endl;
            cout << "Bye-Bye!" << endl;
            gameRunning = false;
        }
        else {
            cout << "Invalid Choice!" << endl;
        }
    }
    return 0;
}

void initializeGame(Player &player) {
    player.Value = 10;
}

int generateNextValue() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-10, 15);
    return dis(gen);
}

//function for a boss
Boss_Number spawnBoss(int bossCount) {
    Boss_Number boss;
    random_device rd;
    mt19937 gen(rd());
    //uniform_int_distribution<> dis(10, 750);
    int minVal = 20 + (bossCount * 30);
    int maxVal = 50 + (bossCount * 70);
    uniform_int_distribution<> dis(minVal, maxVal);
    boss.Value = dis(gen);
    return boss;
}

//function for the wizard
Wizard spawnWizard(int playerVal) {
    Wizard wizard;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> percentDis(25, 75);
    int randomPercent = percentDis(gen);
    wizard.Value = (playerVal * randomPercent) / 100;
    return wizard;
}

void playGame(Player &player) {
    initializeGame(player);
    char op;
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));
    //char ops[] = {'+', '-', '*', '/', '%'};
    //int operand;
    //int choice;
    int successful_rounds = 0;
    int boss_encounters = 0;
    int wizard_encounters = 0;
    cout << "\n--- NUMELOCK ---" << endl;
    cout << "\n--- GAME STARTED ---" << endl;
    cout << "Hello, " << player.name << "! Keep your value above 0." << endl;
    //cout << "Target Boss Value: " << currentBoss.Value << endl;

    while (player.Value >= 0) {
        int incoming = generateNextValue();
        cout << "\nYour Current Value: " << player.Value << endl;
        cout << "Incoming Value: " << incoming << endl;
        //char operators[std::rand() % 4];
        cout << "Choose an operation (+, -, *): ";
        //cout << "Choose an operation:  " << endl;
        //cout  << "1. " << op << endl;
        //cout  << "2. " << op << endl;
        //cout  << "3. " << op << endl;

        //cin >> choice;
        //if (choice == 1) {
        cin >> op;
        if (op == '+') {
            player.Value += incoming;
            successful_rounds++;
        } else if (op == '-') {
            player.Value -= incoming;
            successful_rounds++;
        } else if (op == '*') {
            player.Value *= incoming;
            successful_rounds++;
        } else {
            cout << "Invalid operation! You lose points for messing up." << endl;
            player.Value -= 5;
            successful_rounds--;
        }

        //Summons the boss
        if (successful_rounds > 0 && successful_rounds % 5 == 0) {
            cout << "INCOMING BOSS (Boss # " << (boss_encounters + 1) << ") " << endl;

            Boss_Number currentBoss = spawnBoss(boss_encounters);
            cout << "The Boss requires a value of at least: " << currentBoss.Value << endl;
            cout << "Your Current Value: " << player.Value << endl;

            if (player.Value > currentBoss.Value) {
                cout << "WOW!" << endl;
                cout << "You won by a LARGE margin" << endl;
                cout << "You CRUSHED Boss #" << (boss_encounters + 1) << endl;
                successful_rounds++;
                player.Value += currentBoss.Value;
                boss_encounters++;
            } else if (player.Value == currentBoss.Value) {
                cout << "It was a close match..." << endl;
                cout << "But it was JUST enough" << endl;
                successful_rounds++;
                boss_encounters++;
            } else if (player.Value < currentBoss.Value) {
                cout << "DEFEAT!" << endl;
                cout << "The boss was just too strong..." << endl;
                break;
            }
        }

        if (successful_rounds > 0 && successful_rounds % 7 == 0) {
            cout << "INCOMING WIZARD" << endl;
            Wizard current_Wizardval = spawnWizard(player.Value);
            cout << "WIZARD: IT IS I, THE DASTARDLY WIZARD" << endl;
            if (wizard_encounters == 0) {
                cout << "The wizard is NO GOOD" << endl;
                cout << "He shows up and replaces YOUR value with HIS own" << endl;
                cout << player.name << ", be on guard!" << endl;
            }
            cout << "WIZARD: What a nice " << player.Value << " You have!" << endl;
            cout << "WIZARD: Let's trade! My chunk (" << current_Wizardval.Value << ") for your loot !" << player.Value << "!" << endl;
            player.Value = current_Wizardval.Value;
            cout << "WIZARD: TOODLES!" << endl;
            cout << player.Value << endl;
            wizard_encounters++;
            successful_rounds++;
        }

        //Shows the players standing every 10 or so rounds
        if (successful_rounds > 0 && successful_rounds % 10 == 0) {
            cout << "\n--- NUMELOCK ---" << endl;
            cout << "\n--- TOTAL STANDINGS---" << endl;
            cout << player.name << endl;
            cout << player.Value << endl;
            cout << successful_rounds << endl;
            cout << boss_encounters << endl;
        }

        if (player.Value < 0) {
            cout << "\nYour value dropped below 0! Game Over." << endl;
            break;
        }
    }
}