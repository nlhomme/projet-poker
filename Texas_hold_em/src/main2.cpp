
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

string suits[4];
string ranks[13];

class Card{
    public:
    int suit;
    int rank;
};

int compareCards(const void *card1, const void *card2){
    return (*(Card *)card1).rank - (*(Card *)card2).rank;
}

class Deck{
    public:
        Deck(){
            for (int i=0;i<4;i++){
                for (int j=0;j<13;j++){
                    cards[i*13+j].suit = i;
                    cards[i*13+j].rank = j;
                }
            }

            // définition des couleurs
            suits[0] = "D"; // carreau
            suits[1] = "S"; // piques
            suits[2] = "H"; // coeur
            suits[3] = "C"; // trèfles


            // Definition des valeurs
            ranks[0] = "2";
            ranks[1] = "3";
            ranks[2] = "4";
            ranks[3] = "5";
            ranks[4] = "6";
            ranks[5] = "7";
            ranks[6] = "8";
            ranks[7] = "9";
            ranks[8] = "T";
            ranks[9] = "J";
            ranks[10] = "Q";
            ranks[11] = "K";
            ranks[12] = "A";
        }

        void print(){
            cout << "Printing the deck..." << endl;
           // sleep(1);
            for (int i=0;i<52;i++)
                cout << ranks[cards[i].rank] << suits[cards[i].suit] << endl;
            cout << endl;
        }

        void shuffle(){
            top = 51;
            int x;
            Card tempCard;
            for (int i=0;i<4;i++){
                for (int j=0;j<13;j++){
                    cards[i*13+j].suit = i;
                    cards[i*13+j].rank = j;
                }
            }
            cout << "Shuffling the cards and dealing..." << endl << endl;
//            sleep(2);
            for (int i=0;i<52;i++){
                x = rand() % 52;
                tempCard = cards[i];
                cards[i] = cards[x];
                cards[x] = tempCard;
            }
        }

        Card hitme(){
            top--;
            return cards[top+1];
        }

    private:
    int top;
    Card cards[52];
};

class Player{
    public:
    string name;
    int money;
    Card cards[2];
    int playing;
    int round;
    int goodToGo;
    bool amIsmallBlind;
    bool amIbigBlind;
};

class PokerGame{
    public:
    int playersSize;


        void start(string name, int numberOfPlayer){
        playersSize = numberOfPlayer;
        players.resize(playersSize);

            for (int i = 0;i < playersSize; i++){
                players[i].money = 1000;
                players[i].playing = 1;
            }
            players[0].name = name;
            players[1].name = "Florent";
            if(playersSize > 2){
            players[2].money = 1000;
                players[2].playing = 1;
                players[2].name = "Nicolas";
            }
            startGame();
        }


        void deal(){

            for (int i=0;i<playersSize;i++){
                for (int j=0;j<2;j++){
                    if (players[i].playing){
                        players[i].cards[j] = deck1.hitme();
                    }
                }
            }
            for (int i=0;i<5;i++)
                tableCards[i].rank=-1;
        }

        void burnCard(){
            Card cardburnt = deck1.hitme();
            cout << "This CARD HAS BEEN BURNT" <<endl;
            cout << "    ___ " << endl;
                cout << "   | " << ranks[cardburnt.rank] << " |  "<< endl;
                cout << "   | " << suits[cardburnt.suit] << " |  "<< endl;
                cout << "   |___| " << endl << endl;
        }

        void flop(){

            burnCard();
            cout << "this is the flop" <<endl;
            for (int i=0;i<3;i++){
                tableCards[i] = deck1.hitme();
                }
            displayFlop();

        }

        void turn(){
            burnCard();
            tableCards[3] = deck1.hitme();
            displayTurn();
        }

        void river(){
            burnCard();
            tableCards[4] = deck1.hitme();
            displayRiver();

        }

        void displayCards(){
            playersSize = players.size();
            for(int i = 0; i < playersSize; i++){
                cout << players[i].name << "'s hand:" << endl;
                cout << "    ___    ___" << endl;
                cout << "   | " << ranks[players[i].cards[0].rank] << " |  | " << ranks[players[i].cards[1].rank] << " |" << endl;
                cout << "   | " << suits[players[i].cards[0].suit] << " |  | " << suits[players[i].cards[1].suit] << " |" << endl;
                cout << "   |___|  |___|" << endl << endl;

            }
        }

        void displayPlayers(){

        //playersSize = (sizeof(players)/sizeof(*players));
        playersSize = players.size();
        cout << "Nombre de joueurs " << playersSize << endl;
        for(int i = 0; i < playersSize; i++){
        cout << players[i].name << players[i].money << endl;
        }



        }

        void displayFlop(){
        cout << "     ___   ___   ___ " << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? ranks[tableCards[0].rank] : " ") << " | | " << ((tableCards[1].rank)>=0 ? ranks[tableCards[1].rank] : " ") << " | | " << ((tableCards[2].rank)>=0 ? ranks[tableCards[2].rank] : " ") << " |  "
            << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? suits[tableCards[0].suit] : " ") << " | | " << ((tableCards[1].rank)>=0 ? suits[tableCards[1].suit] : " ") << " | | " << ((tableCards[2].rank)>=0 ? suits[tableCards[2].suit] : " ") << " |  "
            << endl;
            cout << "    |___| |___| |___|" << endl;
        }

        void displayTurn(){
        cout << "     ___   ___   ___   ___  " << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? ranks[tableCards[0].rank] : " ") << " | | " << ((tableCards[1].rank)>=0 ? ranks[tableCards[1].rank] : " ") << " | | " << ((tableCards[2].rank)>=0 ? ranks[tableCards[2].rank] : " ") << " | | " << ((tableCards[3].rank)>=0 ? ranks[tableCards[3].rank] : " ") << " |  "
            << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? suits[tableCards[0].suit] : " ") << " | | " << ((tableCards[1].rank)>=0 ? suits[tableCards[1].suit] : " ") << " | | " << ((tableCards[2].rank)>=0 ? suits[tableCards[2].suit] : " ") << " | | " << ((tableCards[3].suit)>=0 ? suits[tableCards[3].suit] : " ") << " |  "
            << endl;
            cout << "    |___| |___| |___| |___|" << endl;

        }

        void displayRiver(){
             cout << "     ___   ___   ___   ___   ___  " << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? ranks[tableCards[0].rank] : " ") << " | | " << ((tableCards[1].rank)>=0 ? ranks[tableCards[1].rank] : " ") << " | | " << ((tableCards[2].rank)>=0 ? ranks[tableCards[2].rank] : " ") << " | | "
            << ((tableCards[3].rank)>=0 ? ranks[tableCards[3].rank] : " ") << " | | " << ((tableCards[4].rank)>=0 ? ranks[tableCards[4].rank] : " ") << " | " << endl;
            cout << "    | " << ((tableCards[0].rank)>=0 ? suits[tableCards[0].suit] : " ") << " | | " << ((tableCards[1].rank)>=0 ? suits[tableCards[1].suit] : " ") << " | | " << ((tableCards[2].rank)>=0 ? suits[tableCards[2].suit] : " ") << " | | "
            << ((tableCards[3].rank)>=0 ? suits[tableCards[3].suit] : " ") << " | | " << ((tableCards[4].rank)>=0 ? suits[tableCards[4].suit] : " ") << " | " << endl;
            cout << "    |___| |___| |___| |___| |___| " << endl;
        }



    private:
        //Player players[3];
        std::vector<Player> players;
        Deck deck1;
        int bind;
        Card tableCards[5];
        int pot,action,bet,betOn,winner,maxPoints,roundWinner;
        int handPoints[6];
        int bestHand[6][3];
        //int playersSize = sizeof(players);
        int playersLeft(){
            int count = 0;
            for (int i = 0; i < playersSize; i++)
                if (players[i].money>0)
                    count++;
            return count;
        }

        /*int computerAction(int playerNum){
            if (players[playerNum].cards[0].rank < 8 && players[playerNum].cards[1].rank < 8){
                if (players[playerNum].cards[0].rank!=players[playerNum].cards[1].rank)
                    return 0;
                else
                    return 1;
            }

            else if (players[playerNum].cards[0].rank < 10 && players[playerNum].cards[1].rank < 10){
                if (players[playerNum].cards[0].rank!=players[playerNum].cards[1].rank)
                    return 1;
                else
                    return 2;
            }
            else{
                return 2;
            }
        }*/

        /*checks if someone still got bet/call*/
        int playersToBet(){
        playersSize = sizeof(players);
            for (int i = 0;i<playersSize;i++)
                if (players[i].round==1&&players[i].goodToGo==0)
                    return 1;

            return 0;
        }

        void takeBets(){
            betOn = 0;

            for (int k=0;k<playersSize;k++)
                players[k].goodToGo = 0;


            for (int k=0;k<playersSize;k++){

                if (players[k].round){
                    if (betOn){
                        cout << players[k].name << "'s action: (1) FLOP (3) BET/CALL ";
                        cin >> action;
                        while (action!=1&&action!=3){
                            cout << "Invalid number pressed." << endl;
                            cout << players[k].name << "'s action: (1) FLOP (3) BET/CALL ";
                            cin >> action;
                        }
                    }
                    else{
                        cout << players[k].name << "'s action: (1) FLOP (2) CHECK (3) BET/CALL ";
                        cin >> action;
                        while (action<1||action>3){
                            cout << "Invalid number pressed." << endl;
                            cout << players[k].name << "'s action: (1) FLOP (2) CHECK (3) BET/CALL ";
                            cin >> action;
                        }
                    }
                    cout << endl;
                    if (action==1)
                        players[k].round = 0;
                    else if(action==2)
                        continue;
                    else{
                        if (betOn){
                            pot+=betOn;
                            players[k].money-=betOn;
                            players[k].goodToGo = 1;
                        }
                        else{
                            cout << "How much do you want to bet: ";
                            cin >> bet;
                            while (bet>players[k].money||bet<1){
                                cout << "Invalid number to bet." << endl;
                                cout << "How much do you want to bet: ";
                                cin >> bet;
                                cout << endl << endl;
                            }
                            pot+=bet;
                            players[k].money-=bet;
                            betOn = bet;
                            players[k].goodToGo = 1;
                        }
                    }
                }


            }

            if (betOn&&playersToBet()){
                for (int k=bind+1;k<bind+playersSize+1;k++){
                    if (k%playersSize==0){
                        if (players[0].round&&players[0].goodToGo==0){
                            cout << players[k].name << "'s action: (1) FLOP (3) BET/CALL ";
                            cin >> action;
                            while (action!=1&&action!=3){
                                cout << "Invalid number pressed." << endl;
                                cout << players[k].name << "'s action: (1) FLOP (3) BET/CALL ";
                                cin >> action;
                                cout << endl << endl;
                            }
                            if (action==1)
                                players[0].round = 0;
                            else{
                                pot+=betOn;
                                players[0].money-=betOn;
                                players[0].goodToGo = 1;
                            }
                        }
                    }

                    else{
                        if (players[k%playersSize].round==0||players[k%playersSize].goodToGo==1)
                            continue;
                        action = rand() % 2;
                        if (action==0){
                            players[k%playersSize].round=0;
                            cout << players[k%playersSize].name << " flops..." << endl << endl;
                        }
                        else{
                            pot+=betOn;
                            players[k%playersSize].money -= betOn;
                            cout << players[k%playersSize].name << " calls!" << endl << endl;
                            players[k%playersSize].goodToGo = 1;
                        }
                    }
                }
            }
        }

        int oneLeft(){
            int count = 0;
            for (int k=0;k<playersSize;k++)
                if (players[k].round)
                    count++;
            if (count==1)
                return 1;
            else
                return 0;
        }

        int getWinner(){
            int winner;
            for (int k=0;k<playersSize;k++)
                if (players[k].round)
                    winner = k;
            return winner;
        }

        int getScore(Card hand[]){
            qsort(hand,5,sizeof(Card),compareCards);
            int straight,flush,three,four,full,pairs,high;
            int k;

            straight = flush = three = four = full = pairs = high = 0;
            k = 0;

            /*checks for flush*/
            while (k<4&&hand[k].suit==hand[k+1].suit)
                k++;
            if (k==4)
                flush = 1;

            /* checks for straight*/
            k=0;
            while (k<4&&hand[k].rank==hand[k+1].rank-1)
                k++;
            if (k==4)
                straight = 1;

            /* checks for fours */
            for (int i=0;i<2;i++){
                k = i;
                while (k<i+3&&hand[k].rank==hand[k+1].rank)
                    k++;
                if (k==i+3){
                    four = 1;
                    high = hand[i].rank;
                }
            }

            /*checks for threes and fullhouse*/
            if (!four){
                for (int i=0;i<3;i++){
                    k = i;
                    while (k<i+2&&hand[k].rank==hand[k+1].rank)
                        k++;
                    if (k==i+2){
                        three = 1;
                        high=hand[i].rank;
                        if (i==0){
                            if (hand[3].rank==hand[4].rank)
                                full=1;
                        }
                        else if(i==1){
                            if (hand[0].rank==hand[4].rank)
                                full=1;
                        }
                        else{
                            if (hand[0].rank==hand[1].rank)
                                full=1;
                        }
                    }
                }
            }

            if (straight&&flush)
                return 170 + hand[4].rank;
            else if(four)
                return 150 + high;
            else if(full)
                return 130 + high;
            else if(flush)
                return 110;
            else if(straight)
                return 90 + hand[4].rank;
            else if(three)
                return 70 + high;

            /* checks for pairs*/
            for (k=0;k<4;k++)
                if (hand[k].rank==hand[k+1].rank){
                    pairs++;
                    if (hand[k].rank>high)
                        high = hand[k].rank;
                }

            if (pairs==2)
                return 50 + high;
            else if(pairs)
                return 30 + high;
            else
                return hand[4].rank;
        }

        int tryHand(int array[],int player){
            Card hand[5];

            /* get cards from table and player */
            for (int i=1;i<4;i++)
                hand[i-1] = tableCards[array[i]];

            for (int i=0;i<2;i++)
                hand[i+3] = players[player].cards[i];

            return getScore(hand);

        }

        void evaluateHands(){
            int stack[10],k;
            int currentPoints;

            for (int q=0;q<playersSize;q++){
                if (players[q].round){
                    stack[0]=-1; /* -1 is not considered as part of the set */
                    k = 0;
                    while(1){
                        if (stack[k]<4){
                            stack[k+1] = stack[k] + 1;
                            k++;
                        }

                        else{
                            stack[k-1]++;
                            k--;
                        }

                        if (k==0)
                            break;

                        if (k==3){
                            currentPoints = tryHand(stack,q);
                            if (currentPoints>handPoints[q]){
                                handPoints[q] = currentPoints;
                                for (int x=0;x<3;x++)
                                    bestHand[q][x] = stack[x+1];
                            }
                        }
                    }

                }
            }
        } /*end of evaluateHands() */

        void printWinningHand(int winner){
            Card winningHand[5];
            for (int i=0;i<3;i++)
                winningHand[i] = tableCards[bestHand[winner][i]];

            for (int i=0;i<2;i++)
                winningHand[i+3] = players[winner].cards[i];

            qsort(winningHand,5,sizeof(Card),compareCards);

            cout << "   The winning hand:" << endl;
            cout << "   ___   ___   ___   ___   ___" << endl;
            cout << "  | " << ranks[winningHand[0].rank] << " | | " << ranks[winningHand[1].rank] << " | | " << ranks[winningHand[2].rank] << " | | " << ranks[winningHand[3].rank] << " | | " << ranks[winningHand[4].rank] << " |" << endl;
            cout << "  | " << suits[winningHand[0].suit] << " | | " << suits[winningHand[1].suit] << " | | " << suits[winningHand[2].suit] << " | | " << suits[winningHand[3].suit] << " | | " << suits[winningHand[4].suit] << " |" << endl;
            cout << "  |___| |___| |___| |___| |___|" << endl;
            cout << endl << endl;
//            sleep(3);
        }

        /* main gameplay function*/
        void startGame(){
            int i = 0;

            while(playersLeft()>1){
                /* starting default values*/
                for (int z=0;z<playersSize;z++)
                    if (players[z].money<1){
                        players[z].playing = 0;
                        players[z].round = 0;

                    }
                for (int z=0;z<playersSize;z++){
                    if (players[z].playing)
                        players[z].round = 1;
                    handPoints[z]=-1;

                }
                for (int x=0;x<playersSize;x++){
                    for (int y=0;y<3;y++){
                        bestHand[x][y] = -1;

                    }
                }

                /* checking for game over*/
                if(players[0].playing==0){
                    cout << "You are out of money, sorry." << endl;
                    cout << "Game over." << endl;
                    break;
                }

                bind = i % playersSize;

                 /* paying bind */
                cout << players[bind].name << " is the dealer"  << endl;

                int playerSmallBind = (bind+1)%playersSize;
                int playerBigBind = (bind+2)%playersSize;

                if (players[playerSmallBind].money>=20){
                cout << "Dealing small blind to :" << players[playerSmallBind].name << endl << endl;
                players[bind+1].money-=20;
                } else {
                players[bind+1].money -= players[bind+1].money;
                cout << "Player with small blind is all in " << endl;
                }
                 if (players[playerBigBind].money>=40){
                cout << "Dealing big blind to :" << players[playerBigBind].name << endl << endl;
                players[playerBigBind].money-=40;
                } else {
                players[playerBigBind].money -= players[playerBigBind].money;
                cout << "Player with big blind is all in " << endl;
                }

                pot = 60;






                cout << "Get ready for round " << (i+1) << "..." << endl;
//                sleep(1);
                deck1.shuffle();

                /* pre-flop */
                deal();

                //printTable();
                displayCards();

                displayPlayers();

                takeBets();

                if (oneLeft()){
                    winner = getWinner();
                    cout << players[winner].name << " wins $" << pot << endl << endl;
                    i++;
                    continue;
                }

                /* flop */
                flop();
                cout << endl;
                //printTable();
                displayCards();
                takeBets();
                if (oneLeft()){
                    winner = getWinner();
                    cout << players[winner].name << " wins $" << pot << endl << endl;
                    i++;
                    continue;
                }

                /* turn */
                turn();
                cout << endl;
                //printTable();
                displayCards();
                takeBets();
                if (oneLeft()){
                    winner = getWinner();
                    cout << players[winner].name << " wins $" << pot << endl << endl;
                    i++;
                    continue;
                }

                /* river */
                river();
                cout << endl;
                //printTable();
                displayCards();
                takeBets();

                evaluateHands();

                /*find and declare round winner*/
                maxPoints = 0;
                for (int q=0;q<playersSize;q++){
                    if(players[q].round){
                        if (handPoints[q]>maxPoints){
                            maxPoints = handPoints[q];
                            roundWinner = q;
                        }
                    }
                }
                cout << endl;
                cout << players[roundWinner].name << " wins $" << pot << " with ";
                if (maxPoints<30)
                    cout << "HIGH CARD";
                else if (maxPoints<50)
                    cout << "SINGLE PAIR";
                else if (maxPoints<70)
                    cout << "TWO PAIRS";
                else if (maxPoints<90)
                    cout << "THREE OF A KIND";
                else if(maxPoints<110)
                    cout << "STRAIGHT";
                else if(maxPoints<130)
                    cout << "FLUSH";
                else if(maxPoints<150)
                    cout << "FULL HOUSE";
                else if(maxPoints<170)
                    cout << "FOUR OF A KIND";
                else
                    cout << "STRAIGHT FLUSH";
                cout << endl << endl;

                printWinningHand(roundWinner);

                players[roundWinner].money+=pot;

                i++;
            }
        }
};


int main(){
    string name;
    int numberOfPlayer;
    PokerGame game1;

    srand(time(NULL));

    cout << "Welcome to..." << endl << endl;
//    sleep(1);
    cout << "#######                        ###### " << endl;
    cout << "   #    ###### #    # #####    #     #  ####  #    # ###### #####" << endl;
    cout << "   #    #       #  #    #      #     # #    # #   #  #      #    #" << endl;
    cout << "   #    #####    ##     #      ######  #    # ####   #####  #    #" << endl;
    cout << "   #    #        ##     #      #       #    # #  #   #      #####" << endl;
    cout << "   #    #       #  #    #      #       #    # #   #  #      #   #" << endl;
    cout << "   #    ###### #    #   #      #        ####  #    # ###### #    #" << endl << endl;

    cout << "Please enter the number of players : ";

    cin >> numberOfPlayer;

    cout << "Please type your name: ";

    cin >> name;
//    sleep(2);

    game1.start(name,numberOfPlayer);

    return 0;
}
