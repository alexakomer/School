import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.Buffer;
import java.sql.Array;
import java.util.ArrayList;
/*
Helper function to parse sql commands in txt files
 */
public class parser {
    public static ArrayList<String> sqlParser(String path){
        String line;
        ArrayList<String> parsedOutput = new ArrayList<>();
        try{
            //if the line is not blank then add it to output file
            BufferedReader br = new BufferedReader(new FileReader(path));
            while((line = br.readLine()) != null){
                if(!line.equals("")){
                    parsedOutput.add(line + " ");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return parsedOutput;
    }

    /*
    Helper function to parse csv files
     */
    public static ArrayList<ArrayList<String>> parseCSV(String path){
        String line;
        ArrayList<ArrayList<String>> parsedOutput = new ArrayList<>();
        int i = 0;
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            while ((line = br.readLine()) != null)
            {
                parsedOutput.add(new ArrayList<>());
                //split lines based on regex
                String[] arr = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                for(String s : arr){
                    if(s != ""){
                        //replace unwanted values
                        String parsed = s.replaceAll("[\"$']", "");
                        parsedOutput.get(i).add(parsed);
                    }
                }
                //remove empty lines
                if(parsedOutput.get(i).isEmpty()) {
                    parsedOutput.remove(i);
                }
                else{
                    ++i;
                }
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return parsedOutput;
    }
}
