bool checkAlive(int x1, int y1, int size1, int x2, int y2) {

    if (abs(x1-x2)+abs(y1-y2)<=size1) return true;
    return false;

}
