#include <stdio.h>
#include <stdbool.h>
#include<string.h>
int binamount[] = {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 0};
bool playing = true;
bool playerOne = true;
int messageCode = 0;
int giveawayPile = -1;
int lastRecipient = -1;
int chosenBin = -1;

int main() {
    while (playing) {
        char* message = "";
        if (playerOne && messageCode == 0) {
            message = "player 1's turn";
        } else if (!playerOne && messageCode == 0) {
            message = "player 2's turn";
        } else if (playerOne && messageCode == -2) {
            message = "Invalid input. Try again, player 1";
        } else if (!playerOne && messageCode == -2) {
            message = "Invalid input. Try again, player 2";
        } else if (playerOne && messageCode == -1) {
            message = "You must choose a non-empty bin, player 1";
        } else if (!playerOne && messageCode == -1) {
            message = "You must choose a non-empty bin, player 2";
        }
        printf("\n%s\n\n", message);
        messageCode = 0;
        int i = 0;
        printf("\n");

        if (!playerOne) {
            printf("        a    b    c    d    e    f\n");
        }
        printf("+----+----+----+----+----+----+----+----+\n");
        printf("|    | %d  | %d  | %d  | %d  | %d  | %d  |    |\n", binamount[12], binamount[11], binamount[10], binamount[9], binamount[8], binamount[7]);
        printf("| %d  |----+----+----+----+----+----| %d  |\n", binamount[13], binamount[6]);
        printf("|    | %d  | %d  | %d  | %d  | %d  | %d  |    |\n", binamount[0], binamount[1], binamount[2], binamount[3], binamount[4],binamount[5]);
        printf("+----+----+----+----+----+----+----+----+\n");
        if (playerOne) {
            printf("        f    e    d    c    b    a\n");
        }
        char userInput[10];
        printf("Enter 'q' to quit the game: ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strlen(userInput) - 1] = '\0'; 

        if (strcmp(userInput, "q") == 0) {
            playing = false;
        } else if (playerOne && strcmp(userInput, "a") == 0) {
            chosenBin = 5;
        } else if (playerOne && strcmp(userInput, "b") == 0) {
            chosenBin = 4;
        } else if (playerOne && strcmp(userInput, "c") == 0) {
            chosenBin = 3;
        } else if (playerOne && strcmp(userInput, "d") == 0) {
            chosenBin = 2;
        } else if (playerOne && strcmp(userInput, "e") == 0) {
            chosenBin = 1;
        } else if (playerOne && strcmp(userInput, "f") == 0) {
            chosenBin = 0;
        } else if (!playerOne && strcmp(userInput, "a") == 0) {
            chosenBin = 12;
        } else if (!playerOne && strcmp(userInput, "b") == 0) {
            chosenBin = 11;
        } else if (!playerOne && strcmp(userInput, "c") == 0) {
            chosenBin = 10;
        } else if (!playerOne && strcmp(userInput, "d") == 0) {
            chosenBin = 9;
        } else if (!playerOne && strcmp(userInput, "e") == 0) {
            chosenBin = 8;
        } else if (!playerOne && strcmp(userInput, "f") == 0) {
            chosenBin = 7;
        } else {
            chosenBin = -2;
            messageCode = -2;
        }

        if (chosenBin >= 0) {
            giveawayPile = binamount[chosenBin];
            binamount[chosenBin] = 0;
            if (giveawayPile <= 0) {
                messageCode = -1;
            }

            int recipient = chosenBin + 1;
            while (giveawayPile > 0) {
                if (playerOne && recipient == 13) {
                    recipient = 0;
                }
                if (!playerOne && recipient == 6) {
                    recipient = 7;
                }
                binamount[recipient] += 1;
                giveawayPile -= 1;
                recipient = recipient;
                if (recipient>=13){
                    recipient=0;
                }
                else if (giveawayPile == 0) {
                    lastRecipient = recipient;
                }
                else{
                    recipient=(recipient)+1;
                    if (recipient>13)
                        recipient=0;
                }
            }

            if (playerOne && lastRecipient == 6) {
                playerOne = true;  
            } 
            else if (playerOne && binamount[lastRecipient] == 1 && lastRecipient < 6) {
                printf("AYA %d\n",lastRecipient);
                binamount[6] += binamount[lastRecipient] + binamount[12 - lastRecipient];
                binamount[lastRecipient] = 0;
                binamount[12 - lastRecipient] = 0;
                playerOne = !playerOne;
            } 
            else if (!playerOne && lastRecipient == 13) {
                playerOne = false; 
            } 
            else if (!playerOne && binamount[lastRecipient] == 1 && lastRecipient > 6) {
                binamount[13] += binamount[lastRecipient] + binamount[12 - lastRecipient];
                binamount[lastRecipient] = 0;
                binamount[12 - lastRecipient] = 0;
                playerOne = !playerOne;
            } 
            else if (messageCode >= 0) {
                playerOne = !playerOne;  
            }



            int sideOne = 0;
            int sideTwo = 0;
            for (int j = 0; j < 6; j++) {
                sideOne += binamount[j];
                sideTwo += binamount[j + 7];
            }

            if (sideOne == 0 || sideTwo == 0) {
                playing = false;
                binamount[6] += sideOne;
                binamount[13] += sideTwo;
                for (int k = 0; k < 6; k++) {
                    binamount[k] = 0;
                    binamount[k + 7] = 0;
                }
            }
        }
    }
    printf("\nthe game is over\n");
    if (binamount[6] > binamount[13]) {
        printf("Player 1 has won the game...\n");
    } else if (binamount[6] < binamount[13]) {
        printf("Player 2 has won the game...\n");
    } else {
        printf("The game ended in a tie...\n");
    }
    return 0;
}
