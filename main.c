#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void difficulty();
void Beginner();
void Intermediate();
void Expert();
void blank_board_function();
void first_guess();
void mineboard(int x, int y);
void print_board();
void mines_count();
void victory();
void lost();
void play_again();
void reveal(int i, int j);
void part_status(int x, int y);

int column;
int row;
int number_of_mine;
int mines;
int mines_left;
char part_situation;

int board[100][18];
int blank_board[100][18];

int main()
{
    printf("Welcome!\nLets play!\nPlease make Terminal Full Screen for better experience\n");
    difficulty();
    return 0;
}

void difficulty (){                         //a function for choosing difficulty level.

    printf("Difficulty Levels:\n\t1.Beginner 9*9 with 10 mine\n\t2.Intermediate 16*16 with 40 mine\n\t3.Expert 30*16 with 99 mine\n\t4.Your own sizes\n\tPlease Choose a difficulty level:");
    int difficulty_level = 0;
    scanf("%d", &difficulty_level);
    while(difficulty_level != 1 && difficulty_level != 2 && difficulty_level!= 3 && difficulty_level != 4){
        printf("\tError!\n\tPlease choose a number from 1 to 4!");
        printf("\n\tPlease Choose a difficulty level:");
        scanf("%d", &difficulty_level);
    }
    if(difficulty_level == 1){
        Beginner();
    }
    else if(difficulty_level == 2){
        Intermediate();
    }
    else if(difficulty_level == 3){
        Expert();
    }
    else if(difficulty_level == 4){
        personalized();
    }
}

void personalized(){
    printf("Please enter Number of rows(Maximum size is 100):");
    scanf("%i", &row);
    printf("please enter Number of Columns(Maximum size is 18):");
    scanf("%i", &column);
    printf("Please enter Number of mines(it must be maximum %i):", row * column / 2);
    scanf("%i", &number_of_mine);
    mines = 0;
    blank_board_function();
    first_guess();

}
void Beginner (){
    row = 9;
    column = 9;
    number_of_mine = 10;
    mines = 0;
    blank_board_function();
    first_guess();
}

void Intermediate (){
    row = 16;
    column = 16;
    number_of_mine = 40;
    mines = 0;
    blank_board_function();
    first_guess();
}

void Expert (){
    row = 30;
    column = 16;
    number_of_mine = 99;
    mines = 0;
    blank_board_function();
    first_guess();

}

void blank_board_function(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            blank_board[i][j] = '-';
            board[i][j] = blank_board[i][j];
        }
    }
    mines_left = number_of_mine;
    printf("\n\t");
    for(int i = 0; i < column ; i++){
        printf("|%d|\t", i);
    }
    printf("\n\n");
    for(int i = 0 ; i < row ; i++){
        printf("|%d|\t", i);
        for(int j = 0 ; j < column ; j++){
            printf("[%C]\t", blank_board[i][j]);
        }
        printf("\n\n");
     }
     mines_count();
}

void first_guess(){
    int x, y;
    printf("\nPlease enter first value for row a space and second value for column: ");
    scanf("%d%d", &x, &y);
    if((x < 0) || (x >= row) || (y < 0) || (y >= column)){
        printf("\nPlease enter values inside the Table!\n");
        first_guess();
    }
    if(board[x][y] != '-' && board[x][y] != '?'){
        printf("\nPlease enter values that didn't entered before!\n");
        first_guess();
    }
    part_status(x, y);
    if(part_situation == '?'){
        board[x][y] = '?';
        print_board();
    }
    if(part_situation == '+'){
        if(board[x][y] == '?'){
            board[x][y] = '-';
        }
        mineboard(x, y);
    }
}

void mineboard(int x, int y){
    srand( time( NULL ) );
    while( mines < number_of_mine ){
        int i = rand() % (row);
        int j = rand() % (column);
        if( blank_board[i][j] == '-' && (i != x && j != y)){
            blank_board[i][j] = '*';
            mines++;
        }
    }
    for(int i = 0 ; i < row ; i++ ){
        for(int j = 0 ; j < column ; j++){
            if( blank_board[i][j] != '*'){
                blank_board[i][j] = 0;
            }
            for(int k = -1 ; k <= 1 ; k++){
                for(int z = -1 ; z <= 1 ; z++){
                    if( i+k < row && i+k >=0 && j+z < column && j+z >= 0){
                        if((blank_board[i][j] != '*') && (blank_board[i+k][j+z] == '*')){
                            blank_board[i][j]++;
                        }
                    }
                }
            }
        }
    }
    reveal(x, y);
    print_board();
}

void print_board(){
    printf("\t");
    for(int i = 0 ; i < column ; i++){
        printf("|%d|\t", i);
    }
    printf("\n\n");
    for(int i = 0 ; i < row ; i++){
        printf("|%d|\t", i);
        for(int j = 0; j < column; j++){
            if(board[i][j] == '-' || board[i][j] == '?'){
                printf("[%C]\t", board[i][j]);
            }
            else if(board[i][j] == 0){
                printf("[%c]\t", ' ');
            }
            else{
                printf("[%d]\t", board[i][j]);
            }
        }
        printf("\n\n");
     }
     mines_count();
     if(mines == 0){
        first_guess();
     }
     else{
        guess();
     }
}

void guess(){
    int victory_test = 0;
    int victory_test_flag = 0;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(board[i][j] == blank_board[i][j]){
                victory_test++;
            }
            if(board[i][j] == '?' && blank_board[i][j] == '*'){
                victory_test_flag++;
            }
        }
    }
    if(victory_test == (row * column) - number_of_mine || (victory_test_flag == number_of_mine && mines_left == 0)){
        victory();
    }
    int x, y;
    printf("\nPlease enter first value for row a space and second value for column: ");
    scanf("%d%d",&x , &y);
    if((x < 0) || (x >= row) || (y < 0) || (y >= column)){
        printf("\nPlease enter values inside the Table!\n");
        guess();
    }
    if((board[x][y] != '-') && (board[x][y] != '?')){
        printf("\nPlease enter values that didn't entered before!\n");
        guess();
    }
    part_status(x, y);
    if(part_situation == '?'){
        board[x][y] = '?';
    }
    else if(part_situation == '+'){
        if(blank_board[x][y] == '*'){
            printf("\nOh!\nYou hit a mine in row %d and column %d!\n\n", x, y);
            lost();
        }
        if(board[x][y] == '?'){
            board[x][y] = '-';
        }
        reveal(x, y);
    }
    print_board();
}

void reveal(int i,int j){
    if(board[i][j] != '-' && board[i][j] != '?'){
        return blank_board[i][j];
    }
    board[i][j] = blank_board[i][j];
    if(board[i][j] == 0){
        for(int x = -1 ; x <= 1 ; x++){
            for(int y = -1 ; y <= 1 ; y++){
                if(i + x >= 0 && i + x < row &&  j + y >= 0 && j + y < column){
                    reveal(i+x, j+y);
                }
            }
        }
    }
}

void mines_count (){
    int flag;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(board[i][j] == '?'){
                flag++;
            }
        }
    }
    mines_left = number_of_mine - flag;
    printf("Mines left:%d\n\n", mines_left);
}

void victory(){
    printf("\n\n");
    for(int i = 1;i <= column * 4 ; i++){
        printf("<");
    }
    printf("!VICTORY!");
    for(int i = 1;i <= column * 4 ; i++){
        printf(">");
    }
    printf("\n\n");
    play_again();
}

void lost(){
    final_board();
    printf("\n\n");
    for(int i = 1;i <= column * 4 ; i++){
        printf("<");
    }
    printf("!YOU LOST!\nGAME OVER!\a");
    for(int i = 1;i <= column * 4 ; i++){
        printf(">");
    }
    printf("\n\n");
    play_again();
}

void play_again(){
    char play_status;
    printf("Do you want to play again(Y for yes And N for No)? ");
    scanf("%s", &play_status);
    if(play_status == 'Y' || play_status == 'y'){
        difficulty();
    }
    else if(play_status == 'N' || play_status == 'n'){
        printf("\nGood game!\nI wish see you soon!\n");
        exit('n');
        exit('N');
    }
    else{
        printf("Choose between Y and N Please!\n");
        play_again();
    }
}

void final_board(){
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < column ; j++){
            if(blank_board[i][j] == '*' || board[i][j] == '?'){
                board[i][j] = blank_board[i][j];
            }
        }
    }
    printf("\t");
    for(int i = 0 ; i < column ; i++){
        printf("|%d|\t", i);
    }
    printf("\n\n");
    for(int i = 0 ; i < row ; i++){
        printf("|%d|\t", i);
        for(int j = 0; j < column; j++){
            if(board[i][j] == '*' || board[i][j] == '-'){
                printf("[%c]\t", board[i][j]);
            }
            else if(board[i][j] == 0){
                printf("[%c]\t", ' ');
            }
            else{
                printf("[%d]\t", board[i][j]);
            }
        }
        printf("\n\n");
     }

}

void part_status(int x, int y){
    printf("Please enter (?) for put flag OR put (+) to choose part of table:");
    scanf("%s", &part_situation);
    if((part_situation != '+') && (part_situation != '?')){
        printf("Please enter a value between (?) AND (+) !!!\n");
        part_status(x, y);
    }
}
