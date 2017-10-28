char board[4][4];
int sign(int x) {
    return ( (x == 0) ? 0 : (x / abs(x) ) );
}
// Checks if a line has 4 player cells or 3 player cells and one T.
// Coordinates of the cells in the line are:
// (x0,y0), (x0+sx, y0+sy), (x0+2*sx, y0+2*sy), (x0+3*sx, y0+3*sy)
// Where sx = sign(x1 - x0), sy = sign(y1 - y0).
bool lineCheck(int x0, int x1, int y0, int y1, char p) {
    map<char, int> c;
    int y = y0;
    int x = x0;
    for (int i=0; i< 4; i++) {
        c[ board[x][y] ]++;
        x += sign(x1 - x0);
        y += sign(y1 - y0);
    }
    return (c['T'] + c[p]) == 4; 
}
string solve() {
    // count empty cells:
    int e = 0; 
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            e += (board[i][j] == '.');
        }
    }
    // Find out if any player wins:
    bool wins[2] = {false, false};
    string p     = "XO";   // for i=0, check X, for i=1 check O
    for (int i=0; i<2; i++) {
        // diagonal
        wins[i] |= lineCheck(0,4, 0,4, p[i]);
        // anti diagonal
        wins[i] |= lineCheck(3,-1, 0,4, p[i]); //My mistake was 4,0 instead of 3,-1
        for (int j=0; j<4; j++) {
            //horizontal lines (four of them):
            wins[i] |= lineCheck(0,4, j,j, p[i]);
            // vertical lines
            wins[i] |= lineCheck(j,j, 0,4, p[i]);
        }
    }
    if (wins[0]) {
        return "X won";
    } else if (wins[1]) {
        return "O won";
    } else if (e > 0) {
        return "Game has not completed";
    } else {
        return "Draw";
    }
}