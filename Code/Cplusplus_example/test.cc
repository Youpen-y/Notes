#define Cat(x,y) x##y

int f(int x){
    int a = 1;
    int b = 1;
    int y = Cat(a,b);

    int result = (x / 42);
    return result;
}
