class test2 {
    public static void main() {
        A a;
        a = new A();
        a.set(12);
        a.set(13);
        A b;
        b = new A();
        b.set(14);
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