import java.util.Scanner;

/**
 * Created by Idan Damri 07/01/2020.
 */
public class MainProcedure {


    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        System.out.println("Choose the smallest year, largest year and the number of participants, separated by space."
        + "\nThe largest year should be less than (2 * the smallest year)");

        String[] stringData = in.nextLine().split(" ");

       Integer mostCommonYear =  MainProcedureUtils.mostCommonYear(stringData);
        if(mostCommonYear == null)
            System.out.println("bad input/s");
        else
            System.out.println("\nMost common year: " + mostCommonYear);


    }


}
