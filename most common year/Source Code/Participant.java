
public class Participant {
    //We're interested only in the year of birth and year of death
    private int mBirthYear;
    private int mDeathYear;

    public Participant(int birthYear , int deathYear){
        mBirthYear = birthYear;
        mDeathYear = deathYear;
    }

    public int getBirthYear () {
        return mBirthYear;
    }

    public int getDeathYear(){
        return mDeathYear;
    }

    public String toString(){
        return "(" + mBirthYear + "," + mDeathYear + ")";
    }
}
