import java.util.Random;

/**
 * Created by Idan Damri on 07/01/2020.
 */
public class MainProcedureUtils {
    private static int[] years;
    private static final int DATA_SIZE = 3;
    private static final int MAX_DISTANCE = 1;
    private static final int EXPECTED_LIVE_TIME = 85;

    public static Integer mostCommonYear(String[] stringData) {
       Integer[] data = validateAndProcessData(stringData);

       if(data == null)
           return null;
        //unboxing
        int smallestYear = data[0], largestYear = data[1], numberOfParticipants = data[2];

        Participant[] participants = MainProcedureUtils.getParticipants(smallestYear,
                largestYear, numberOfParticipants);

        printParticipants(participants);

        return mostCommonYear(smallestYear, largestYear, participants);
    }

    /**
     *
     * @param smallestYear - the smallest year that's possible
     * @param largestYear - the largest year that's possible
     * @param participants - an array of {@link Participant}
     * @return
     */
    private static Integer mostCommonYear(int smallestYear, int largestYear, Participant[] participants) {int leftIndex, rightIndex;
    //there's a one-to-one mapping between an index to a year in
    //{smallestYear, smallestYear + 1, ..., largestYear}
    years = new int[largestYear - smallestYear + 1];

        for (Participant participant : participants) {
            //compute the one-to-one mapping from a year to an index
            leftIndex = participant.getBirthYear() % smallestYear;
            rightIndex = participant.getDeathYear() % smallestYear;

            while (leftIndex <= rightIndex)
                years[leftIndex++]++;
        }

        return mostCommonYear(smallestYear);
    }

    /**
     * finding the index of the most common year offset
     * @param smallestYear - the smallest year that's possible
     * @return the most common year
     */
    private static int mostCommonYear(int smallestYear) {
        int offset = 0, max = years[0];
        for (int i = 0; i < years.length; i++)
            if (max < years[i]) {
                max = years[i];
                offset = i;
            }

        return smallestYear + offset;
    }

    /**
     *
     * @param smallestYear - the smallest year that's possible
     * @param largestYear - the largest year that's possible
     * @param numberOfParticipants
     * @return an array of randomly chosen {@link Participant's} attributes
     *
     */
    public static Participant[] getParticipants(int smallestYear, int largestYear, int numberOfParticipants) {
        int birthYear, deathYear;

        Random random = new Random();

        Participant[] participants = new Participant[numberOfParticipants];

        for (int i = 0; i < numberOfParticipants; i++) {

            birthYear = random.nextInt(largestYear - smallestYear + 1) + smallestYear;
            deathYear = random.nextInt(Math.min(largestYear - birthYear + 1, EXPECTED_LIVE_TIME + 1)) + birthYear;
            participants[i] = new Participant(birthYear, deathYear);
        }

        return participants;
    }

    public static Integer[] validateAndProcessData(String[] StringData) {
        if(StringData.length != DATA_SIZE)
            return null;

        int smallestYear, largestYear, numberOfParticipants;
        Integer[] data = new Integer[DATA_SIZE];

        try{
           data[0] =  smallestYear = Integer.parseInt(StringData[0].trim());
           data[1] = largestYear = Integer.parseInt(StringData[1].trim());
           data[2] = numberOfParticipants = Integer.parseInt(StringData[2].trim());
        }catch (NumberFormatException e){
            return null;
        }
        if(!(0 < smallestYear && smallestYear <= largestYear && 0 < numberOfParticipants &&
                (largestYear / smallestYear ==  MAX_DISTANCE)))
            return null;

        return data;
    }

    public static void printParticipants(Participant[] participants) {
        int countUntilNewLine = 0;
        System.out.println("Participants' data:");
        for(Participant participant : participants) {
            System.out.print(participant + "\t");
            if(++countUntilNewLine % 7 == 0)
                System.out.println();
        }
    }
}
