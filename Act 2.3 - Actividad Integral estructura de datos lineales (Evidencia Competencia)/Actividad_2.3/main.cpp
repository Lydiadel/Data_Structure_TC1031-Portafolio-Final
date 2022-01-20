/* 
* Autor: Cristian Javier Cázares Molina A01741952
* Autor: Carlo Angel Lujan Garcia A01639847
* Autor: Lydia Delgado Uriarte A01740532
* 5/09/2021
* Actividad 2.3: Actividad Integral de Estructura de Datos Lineales (Evidencia Competencia)
* Se abre el archivo de entrada llamado "bitacora.txt, es leido y se almacenan 
* los datos en un vector. Se ordena la información por fecha para la realización 
* de las búsquedas. Y se solicita al usuario las fechas de inicio y fin de búsqueda 
* de información. Se despliegan los registros correspondientes a esas fechas. Y por 
* ultimo se almacenan en un archivo los resultados del ordenamiento. 
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "Node.h"

using namespace std;

/*
The object entry represents an entry of the Bitacora text file,
this object has a date, an IP, and a status
*/
class Entry{
    public:
        int month, day, hour, minute, second;
        string ip, status, date;

        string getDate(){
          date = "";
          date += to_string(month)  + "/" + to_string(day) + " ";

          return date;
        }

        void showDate(){
            cout << "-Date: " << month << "/" << day << " " ;
            cout << hour << ":" << minute << ":" << second;
            cout << "\t (mm/dd hh:mm:ss)" << endl;
        }
        void showIP(){
            cout << "-IP: " << ip << endl;
        }
        void showStatus(){
            cout << "-Status:" << status << endl;
        }
        void show(){
            showDate();
            showIP();
            showStatus();
            cout << endl;
        }
};
    
vector<string> read(string);
Entry line2data(string);
void loadEntries(vector<Entry> &, vector<string>);
int month2number(string);
string number2month(int);
bool isGraterDate(Entry, Entry);
bool isLessDate(Entry, Entry);
void merge(vector<Entry> &, int, int, int);
void mergeSortByDate(vector<Entry> &, int, int);
void writeFile(string, vector<Entry>);
void bubbleSortByDate(vector<Entry> &entryVec);
vector<Entry> searchFirstAndLast(vector<Entry> entryVec, string firstMonth, 
                int firstDay, string lastMonth, int lastDay);
void compressFilteredEntries(vector<Entry>, CustomLinkedList<string>*);

void clearScreen();

/* 
 * The function the app uses to run
*/
int main(){
    clearScreen();
    vector<Entry> entries;

    //Look for a sorted  file
    string sortedFileName = "bitacora_sorted.txt";
    fstream sortedFile;
    sortedFile.open(sortedFileName, ios::in);

    /*If a sorted does not file exists: create one
      else: use the already sorted file.*/
    if(!sortedFile){
        //Load text file to a string vector of lines
        vector<string> rawFile = read("bitacora.txt");
        
        //Convert vector of lines to a vector of class Entry
        cout << "Loading entries..." << endl;
        loadEntries(entries, rawFile);
        cout << "Entries loaded " << "(" << entries.size() << ")." << endl << endl;
        
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

        //Sort Entry vector by date
        cout << "Sorting entries..." << endl;
        //In case you want to try Bubble sort instead of Merge sort uncomment the line below
        //Our merge sort algorithm is x516.66 times faster than the normal bubble sort 
        //Bubble sort aprox. 1:33min
        //Merge sort aprox. 0.18s
        mergeSortByDate(entries, 0, entries.size() - 1); //bubbleSortByDate(entries);
        cout << "Entries sorted" << endl;
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Time difference (sec) = " <<  (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<endl;

        cout << "Saving all entries..." << endl;
        writeFile("bitacora_sorted.txt", entries);
        sortedFile.close();
        cout << "Sorted entries saved successfully, check your folder" << endl << endl;
    }else{
        //Load already existing sorted file
        vector<string> rawFile = read("bitacora_sorted.txt");
        cout << "Loading entries..." << endl;
        loadEntries(entries, rawFile);
        cout << "Entries loaded " << "(" << entries.size() << ")." << endl << endl;
    }

    ///////////////////////////////////////////////////////////////
    //AQUI EMPIEZAN LAS BUSQUEDAS. UTILIZANDO EL VECTOR "entries".
    ///////////////////////////////////////////////////////////////
    
    string firstMonth , lastMonth;
    int firstDay, lastDay;
    cout << "Enter the first month to start (Jun, Jul, Aug, Sep, Oct, etc.)" << endl;
    cin >> firstMonth;
    cout << "Enter the first day to search (1, 2, 3, 4, etc.)" << endl;
    cin >> firstDay;
    cout << "Enter the last month to finish (Jun, Jul, Aug, Sep, Oct, etc.)" << endl;
    cin >> lastMonth;
    cout << "Enter the last day to filter (1, 2, 3, 4, etc.)" << endl;
    cin >> lastDay;
    
    vector<Entry> filteredEntries = searchFirstAndLast(entries, firstMonth, firstDay, lastMonth, lastDay);
    if (filteredEntries.size() != 0) {
        cout << "Saving selected entries..." << endl;
        writeFile("bitacora_sorted_" + firstMonth + "_" + to_string(firstDay) + "_" + lastMonth + "_" + to_string(lastDay) + ".txt", filteredEntries);
        cout << "Sorted entries saved successfully, check your folder" << endl << endl;
        CustomLinkedList<string>* doubleLinkedList = new CustomLinkedList<string>;
        compressFilteredEntries(filteredEntries, doubleLinkedList);
        cout << "Compression done." << endl << endl;
        doubleLinkedList->print_list();
    } else {
        cout << "The specified date is invalid." << endl << endl;
    }
    return 0;
}


/** This function creates a Double Linked List that contains each date with the total 
   * of access of each IP of that day.
   * Read each entry and separate them creating new nodes applying recursion.
   * Creates a new node with the current date that contains the IPS accessed
   * that day and the number of times they accessed, if the next date is different
   * from the current a new node is created with the next date now this being named
   * the current date. 
   * O(N) complexity because it goes through each of the objects in the vector.
   * @param entriesToCompress Vector of entries that are going to be separated.
   * @param doubleLinkedList double linked list which  will be stored in the list
   * including all the entries arranged by date with IP num accessed that day.
  */ 
void compressFilteredEntries(vector<Entry> entriesToCompress, CustomLinkedList<string>* doubleLinkedList){
  
  cout << "Starting compression..." << endl << endl;
  string currentDate = entriesToCompress[0].getDate();
  doubleLinkedList->add_end(currentDate);
    for(int i = 0; i < entriesToCompress.size()-1; i++) {
      if(currentDate != entriesToCompress[i].getDate()) {
        currentDate = entriesToCompress[i].getDate();
        doubleLinkedList->add_end(currentDate);            
      } else {
        doubleLinkedList->tail->ipsNRep[entriesToCompress[i].ip]++;
      }
  }
}
        

/** This function searches for the beginning of a month and a day and traverses 
 * a vector of entries until the end date selected by the user is found, returning 
 * a vector between this two dates , if the dates are not found within the vector 
 * of Entry objects then it will return an empty list
 * O(N) complexity because it goes trough each of the objects in the list
 * @param entryVec vector of Entry objects.
 * @param firstMonth The first month to search for.
 * @param firstDay The first day to search for.
 * @param lastMonth The last month to search for.
 * @param lastDay the last day to finish.
*/
vector<Entry> searchFirstAndLast(vector<Entry> entryVec, string firstMonth, 
                int firstDay, string lastMonth, int lastDay){
    vector<Entry> subEntries;
    int firstIndex = 0, lastIndex = -1, count = 0;
    bool firstDayFound = false, firstMonthFound = false, lastMonthFound = false;

    while (count < entryVec.size() ) {
        if((number2month(entryVec[count].month).compare(firstMonth) == 0) && !firstMonthFound){
            firstMonthFound = true;
        }
        if (firstMonthFound && !firstDayFound) {
            if (entryVec[count].day == firstDay) {
                firstDayFound = true;
                firstIndex = count;
            } 
        }
        if (firstDayFound && firstMonthFound) {
            if((number2month(entryVec[count].month).compare(lastMonth) == 0) && !lastMonthFound){
                lastMonthFound = true;
            }
        }
        if (lastMonthFound) {
            if (entryVec[count].day == lastDay && (number2month(entryVec[count].month).compare(lastMonth) == 0)) {
                lastIndex = count;
            }
        }
        count++;
    }
    if (lastIndex != -1) {
        for (int i = firstIndex; i <= lastIndex ; i++) {
            subEntries.push_back(entryVec[i]);
        }
    }
    return subEntries;
}

/** This function reads each of the lines in a file and converts them into a string vector
 * O(N) complexity because it goes trough each of the lines in the file
 * @param path the path of the file to read.
 * @returns a string vector including all the lines in the file
*/
vector<string> read(string path){
    vector<string> lines;
    string line;
    ifstream inFile(path);
    while(getline(inFile,line)){
        lines.push_back(line);
    }
    inFile.close();
    return lines;
}

/** This function sorts an Entry vector via reference in descending order. 
 * The algorithm compares each of the entries using the dates.
 * O(N^2) complexity because it compares each of the entries in the vector 
 * with each of the entries in the vector with no exception.
*/
void bubbleSortByDate(vector<Entry> &entryVec){
    int n = entryVec.size();
    //Bubble sort algorithm
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(isGraterDate(entryVec[j], entryVec[j+1])){
                Entry temp = entryVec[j];
                entryVec[j] = entryVec[j + 1];
                entryVec[j + 1] = temp;
            }
        }
    }
}

/** This function creates an Entry object based on a received line of text (string)
 * O(N) complexity because it goes through each of the characters in the line
 * @param line A string line containing all the Entry data in a certain order 
 * @returns an Entry object with the data of the received line of text
*/
Entry line2data(string line){
    //Temporal string to devide each line into substrings
    string substr = "";
    //Temporal strings for integer data of Entry object
    string monthStr = "", dayStr = "", timeStr = "";
    string hourStr = "", minuteStr = "", secondStr = "";
    //String data of Entry object
    string ip = "", status = "";

    /*
      PARSING/FORMATING A LINE:
      Go through each character of the line. And keep count
      of the spaces it goes trough.
    */
    int spaces = 0;
    for(int i = 0; i < line.length(); i++){
        /*If the character isn't a space, keep adding characters
          to the temporal substring*/
        if(line[i] != ' ' && spaces < 4){
            substr += line[i];

        /*If it is a space, assign substring to the propper value
          of the Entry object according to its space numberer*/
        }else if(line[i] == ' ' && spaces < 4){
            spaces++;
            switch(spaces){
                case 1:
                    monthStr = substr;
                    break;
                case 2:
                    dayStr = substr;
                    break;
                case 3: {
                        //Time also requires it's own parsing/formatting
                        timeStr = substr;
                        int colons = 0;
                        for(int j = 0; j < timeStr.length(); j++){
                            if(timeStr[j] != ':' && colons == 0){
                                hourStr += timeStr[j];
                            }else if(timeStr[j] != ':' && colons == 1){
                                minuteStr += timeStr[j];
                            }else if(timeStr[j] != ':' && colons == 2){
                                secondStr += timeStr[j];
                            }else if(timeStr[j] == ':'){
                                colons++;
                            }
                        }
                        break;
                    }
                case 4:
                    ip = substr;
                    break;
            }
            substr = "";
        }else{
            status += line[i];
        }

    }

    /*
      CREATION OF Entry INSTANCE
      Assign both integer and string values while converting
      those that aren't strings on Entry's attributes.
    */
    Entry temp;
    temp.month  = month2number(monthStr);
    temp.day    = stoi(dayStr);
    temp.hour   = stoi(hourStr);
    temp.minute = stoi(minuteStr);
    temp.second = stoi(secondStr);
    temp.ip     = ip;
    temp.status = status;

    return temp;
}

/** This function uses the 'line2data' function to fill a vector of Entry objects
 * based on a string vector that includes 'Entry' objects data inside each string
 * in it.
 * O(N) complexity because it goes trough each of the string lines in the fileVector
 * @param entriesVector a vector passed by reference that will be filled with
 * Entry objects. 
 * @param fileVector A string vector which each of its lines contains 
 * all the Entry object data in a certain order.
 * @returns an Entry object with the data of the received line of text
*/
void loadEntries(vector<Entry> &entriesVector, vector<string> fileVector){
    for(int i = 0; i < fileVector.size(); i++){
        entriesVector.push_back(line2data(fileVector[i]));
    }
}

//From month to number
int month2number(string initials){
    if(initials == "Jan")
        return 1;
    else if(initials == "Feb")
        return 2;
    else if(initials == "Mar")
        return 3;    
    else if(initials == "Apr")
        return 4;
    else if(initials == "May")
        return 5;
    else if(initials == "Jun")
        return 6;
    else if(initials == "Jul")
        return 7;
    else if(initials == "Aug")
        return 8;
    else if(initials == "Sep")
        return 9;
    else if(initials == "Oct")
        return 10;
    else if(initials == "Nov")
        return 11;
    else if(initials == "Dec")
        return 12;
    else
        return -1;
}

//From number to month
string number2month(int number){
    switch (number)
    {
    case 1: 
        return "Jan";
        break;
    case 2: 
        return "Feb";
        break;
    case 3: 
        return "Mar";
        break;
    case 4: 
        return "Apr";
        break;
    case 5: 
        return "May";
        break;
    case 6: 
        return "Jun";
        break;
    case 7: 
        return "Jul";
        break;
    case 8: 
        return "Aug";
        break;
    case 9: 
        return "Sep";
        break;
    case 10: 
        return "Oct";
        break;
    case 11: 
        return "Nov";
        break;
    case 12: 
        return "Dec";
        break;
    default:
        return "ERROR_MONTH";
        break;
    }
}

/*Compares each parameter related to time in Entry Class
  and returns True if a > b*/
bool isGraterDate(Entry a, Entry b){
    if(a.month > b.month){
        return true;
    }else if(a.month == b.month){
        if(a.day > b.day){
            return true;
        }else if(a.day == b.day){
            if(a.hour > b.hour){
                return true;
            }else if(a.hour == b.hour){
                if(a.minute > b.minute){
                    return true;
                }else if(a.minute == b.minute){
                    if(a.second > b.second){
                        return true;
                    }else if(a.second == b.second){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

/*Compares each parameter related to time in Entry Class
  and returns True if a < b*/
bool isLessDate(Entry a, Entry b){
    if(a.month < b.month){
        return true;
    }else if(a.month == b.month){
        if(a.day < b.day){
            return true;
        }else if(a.day == b.day){
            if(a.hour < b.hour){
                return true;
            }else if(a.hour == b.hour){
                if(a.minute < b.minute){
                    return true;
                }else if(a.minute == b.minute){
                    if(a.second < b.second){
                        return true;
                    }else if(a.second == b.second){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

/**
 * This function is in charge of mixing two sublists (one left and one right) by ordering them
 * from lowest to highest using the issLessDate(...) function modifying the values ​​of an Entry 
 * object vector passed by reference.
 * Computational complexity O(n) due to the fact that it runs through each of the values ​​of the sublists 
 * only once.
 * @param vec vector of type Entry passed by reference in which the values ​​to be mixed will be searched
 * @param l integer that will be used to know the beginning of the left subvector
 * @param m integer that will be used to know where the left subvector ends
 * @param r integer that will be used to know where the right subvector ends
*/
void merge(vector<Entry> &vec, int l, int m, int r){
    //First index of each half (of original array)
    int n1 = m - l + 1;
    int n2 = r - m;

    //Create temporary vectors for each half
    /*vector<Entry> L(n1);
    vector<Entry> R(n2);*/
    auto *L = new Entry[n1], *R = new Entry[n2];

    //Fill each half
    for(int i = 0; i < n1; i++){
        L[i] = vec[l + i];
    }
    for(int i = 0; i < n2; i++){
        R[i] = vec[m + 1 + i];
    }
    //L[0].showDate;
    //Compare halves with each other
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2){
        if(isLessDate(L[i], R[j])){
            vec[k] = L[i];
            i++;
        }else{
            vec[k] = R[j];
            j++;
        }

        k++;
    }

    //Fill with the rest of the half (if it exists)
    while(i<n1){
        vec[k] = L[i];
        i++;
        k++;
    }
    while(i<n2){
        vec[k] = R[i];
        i += 1;
        k += 1;
    }
    

}

/**
* This function is in charge of sorting a list in ascending order by the mergesort method,
* using recursion.
* Computational complexity O(nlog(n)) because the merge sort method splits the original list into two parts
* For each of the iterations O(log(n)) and the mixlist function has complexity o(n), the product
* tells us that for each iteration log(n) will have to do it O(n) times resulting in the complexity O(nlog(n))
* @param list vector of type Entry passed by reference which seeks to sort ascending
* using merge sort
* @param ini integer that will be used to know the start of the vector
* @param end integer that will be used to know where the vector ends
*/
void mergeSortByDate(vector<Entry> &vec, int l, int r){
    if(l < r){
        //Calculate middle index (floor)
        int m = (l + r) / 2;
        
        //Divide
        mergeSortByDate(vec, l, m);
        mergeSortByDate(vec, m + 1, r);

        //Merge
        merge(vec, l, m, r);
    }
}

/** This function writes a file containing all the entries in an Entry object vector
 * as plain text.
 * O(N) complexity because it goes trough each of the entries in the vector
 * @param fileName Name of the file that will store the data
 * @param entries The Entry object vector containing the entries to be stored in the
 * file
*/
void writeFile(string fileName, vector<Entry> entries){
    fstream file;
    file.open(fileName, fstream::in | fstream::out | fstream::app);
    for(int i = 0; i < entries.size(); i++){
        file << number2month(entries[i].month) << " " << entries[i].day << " ";
        file << entries[i].hour << ":" << entries[i].minute << ":" << entries[i].second << " ";
        file << entries[i].ip << " " << entries[i].status << endl;
    }
    file.close();
}

/** This function clears the screen
 * O(1) complexity
*/
void clearScreen(){
    if (system("CLS")) system("clear");
}