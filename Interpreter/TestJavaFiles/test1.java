class test1 {
    public static void main() {
       int x;
       x = 12;
       int y = 14;
       while(x > 0){
          x = x / 2;
          boolean y = true;
          assert(y);
       }
       if (x > 0){
         y = 12;
       } else{
          y = 14;
        }
       assert(y == 14);
       x = true; //exception int <- boolean
    }
}
