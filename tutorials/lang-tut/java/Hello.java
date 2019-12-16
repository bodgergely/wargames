public class Hello {
    public static void main(String[] args) {
        int result = 0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 10000; j++) {
                for (int k = 0; k < 10000; k++) {
                    int t = 1;
                    if(result % 2 == 1) {
                        t *= -1;
                    }
                    result +=1; 
                } 
            } 
        } 
        System.out.println("Done!"); 
    }
}

