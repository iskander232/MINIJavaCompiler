class test3 {
    public static void main() {
        A b;
        b = new A();
        int x;
        x = b.nope(1) + b.nope(2);
    }
}

class A{
    public int nope(int a){
        return a;
    }
}
