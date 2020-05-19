class test2 {
    public static void main() {
        A a;
        a = new A();
        a.set(12);
        a.set(13);
        A b;
        b = new A();
        b.set(14);
        int c;
        System.out.println(b.get());
    }
}

class A {
    int a;

    public void set(int b){
        a = b;
    }
    public int get(){
        return a;
    }

    public void print(){
        System.out.println(a);
    }
}