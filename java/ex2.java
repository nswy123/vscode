import java.util.ArrayList;
import java.util.Scanner;

//import javax.sound.midi.SysexMessage;

import java.security.*;

public class ex2 {
    public static void main(String[] args) {
        System.out.println("hello world!");//println with newline
        System.out.println(
            "integer:" + 10 +
            "double:" + 3.14 +
            "boolean:" + true);
        System.out.print("hello ");
        System.out.print("world!\n");//print without newline
        System.out.printf("pi=%.5f", Math.PI);//print with formatted
        
        /*
         * input
        */

        // use scanner to read input
        // must import java.util.Scanner;
        Scanner scanner = new Scanner(System.in);
        //read string input
        String name = scanner.next();
        //read byte input
        byte numByte = scanner.nextByte();
        //read int input
        int numInt = scanner.nextInt();
        //read long input
        float numFloat = scanner.nextFloat();
        //read double input
        double numDouble = scanner.nextDouble();
        //read boolean input
        boolean bool = scanner.nextBoolean();

        ///////////////////////////
        //variables
        ///////////////////////////

        /*
        * variable declaration
        */
        int fooInt;
        // 





    }
}