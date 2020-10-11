double sqrt (double v){
    const float delta = 1e-7;

    double L = 0.0, R = v;
    double M = (L + R) /2.0;
    while(R - L > delta){
        if(M * M <= v){
            L = M;
        }
        else{
            R = M;
        }
        M = (L + R)/2.0;
    }
    return R;
}

double pow(double value, int st) {
    double  result = 1;
    for(int i = 0; i < st; i++)
        result *= value;

    return result;
}