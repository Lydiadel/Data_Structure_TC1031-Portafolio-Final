int reverse(int x){
    int base = abs(x); 
    int xreverse = 0;
    while(base != 0) {
        if (xreverse > INT_MAX/10 || (xreverse == INT_MAX / 10 && base > 7)) return 0;
        if (xreverse < INT_MIN/10 || (xreverse == INT_MIN / 10 && base < -8)) return 0;
        xreverse*=10;
        xreverse += base%10;
        base = base/10;
    }
    if(x < 0) {
        return -xreverse;
    }
    else {
        return xreverse;
    }
} 
        