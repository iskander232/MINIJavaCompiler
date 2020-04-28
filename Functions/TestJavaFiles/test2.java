class test2 {
    public static void main() {
        A a = new A();
        a.set(12);
        a.print();
        a.set(13);
        a.print();
        A b = new A();
        b.set(14);
        a.print();  //a and b are different
        int v = true;
    }
}

class A {
    int a;

    public void set(int b){
        a = b;
    }

    public void print(){
        System.out.println(a);
    }
}