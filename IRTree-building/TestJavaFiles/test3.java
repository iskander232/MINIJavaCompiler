class test3 {
    public static void main() {
        my_class x;
        x = new my_class();
        x.print();
        GCD y;
        y = new GCD();
        System.out.println(y.gcd(43256, 2138154));
    }
}

class my_class{
    int z;
    public void print(){
        z = 12;
        System.out.println(z);
    }
}

class GCD{
    public int gcd(int a, int b){
        if (a == 0){
            return b;
        }
        return this.gcd(b % a, a);
    }
}