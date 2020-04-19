class test1 {
    public static void main() {
        boolean x;
        int y;
        int z = 12;
        x = (!(true || false) && false); // x is false
        assert(x)
        System.out.println(x);
        y = (13 % z) + 2;               // y is 1
        System.out.println(y);
    }
}
