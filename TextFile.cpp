#include <iostream>
#include <string>     //write in files
#include <fstream>    //files
#include <filesystem> //check if files exist
#include <cstdlib>    // For remove and rename functions
#include <limits>     // For numeric_limits

// timer
#include <chrono>
#include <thread>
// timer

using namespace std;

class textEdit
{
private:
    int getChoice;          // choice of opening a file or closing
    string createdFileName; // inputted file name without .txt

    // check if newFileName works with all new creations
    string newFileName;

    int openFilesChoice; // open files or go back to menu
    string getFileName;  // to open file

    string gfnOpenFile; // file name + .txt

    int fileOptionsChoice; // open file or close

    int getEditFileChoice; // edit file

    string sentence; // sentence into new file

    int lineCount;

    int userLineNum; // user edit line #

    string userNewLine; // user new text

public:
    void start()
    {

        Welcome();
    }
    void Welcome()
    {
        system("CLS");

        cout << "--------------------------" << endl;
        cout << "          Welcome         " << endl;
        cout << "--------------------------\n\n"
            << endl;

        cout << "--------------------------" << endl;
        cout << "Creating new file?     (1)" << endl;
        cout << "--------------------------" << endl;
        cout << "Accessing file?        (2)" << endl;
        cout << "--------------------------" << endl;
        cout << "Enter: ";
        cin >> getChoice;

        OpenCloseChoice();
    }

    void OpenCloseChoice()
    {

        switch (getChoice)
        {
        case 1:
            createNewFile();
            break;
        case 2:
            openExistingFile();
            break;
        default:
            incorrectInput();
            break;
        }
    }

    void incorrectInput()
    {
        system("CLS");
        cout << "--------------------------" << endl;
        cout << "Incorrect Direction" << endl;
        cout << "--------------------------" << endl;
        cout << "Sending you back! " << endl;
        cout << "--------------------------" << endl;

        // timer
        chrono::seconds duration(4);
        this_thread::sleep_for(duration);
        // timer

        start();
    }

    void createNewFile()
    {
        system("CLS");

        cout << "--------------------------" << endl;
        cout << "Creating File . . .       " << endl;
        cout << "--------------------------\n\n"
            << endl;

        cout << "--------------------------" << endl;
        cout << "[Enter the name of file   " << endl;
        cout << "without .txt, & spaces   ]" << endl;

        cout << "--------------------------" << endl;

        cout << "Enter name: ";
        cin >> createdFileName;

        validateName();
    }

    void validateName()
    {

        newFileName = createdFileName + ".txt";

        /*
        code snippet here
        check if newFileName == existing filename
        */
        ifstream file;

        file.open(newFileName);

        if (file)
        {
            system("CLS");

            cout << "--------------------------" << endl;
            cout << "       File exists        " << endl;
            cout << "    Create a new name!    " << endl;
            cout << "--------------------------" << endl;

            // timer
            chrono::seconds duration(4);
            this_thread::sleep_for(duration);
            // timer

            createNewFile();
        }
        else
        {
            system("CLS");
            cout << "--------------------------" << endl;
            cout << "File created successfully!" << endl;

            // create file!
            ofstream writeNewFile(newFileName);
            writeNewFile.close();

            // store file name in the main storage
            //
            ofstream myStorage("StoreAllFiles.txt", ios::app);

            if (myStorage.is_open())
            {
                myStorage << createdFileName << endl;
                myStorage.close();
            }
            //
            // store file name in the main storage
        }
        // return to home
        doneCreatingFiles();
    }

    void doneCreatingFiles()
    {

        int doneCF;
        cout << "--------------------------" << endl;
        cout << "Done Creating Files?  " << endl;
        cout << "--------------------------" << endl;
        cout << "Enter : yes(1) no(2)  ";
        cin >> doneCF;

        switch (doneCF)
        {
        case 1:
            start();

            break;
        case 2:
            cout << "--------------------------" << endl;
            cout << "Going to create more files" << endl;
            cout << "--------------------------" << endl;

            createNewFile();

            break;
        default:
            incorrectInput();
            break;
        }
    }

    void openExistingFile()
    {

        system("CLS");
        cout << "--------------------------" << endl;
        cout << "Opening Files . . .       " << endl;
        cout << "--------------------------\n\n"
            << endl;

        ifstream myStorage("StoreAllFiles.txt");
        string textFileNames;

        cout << "Files Names: " << endl;
        cout << "-----------" << endl;
        while (getline(myStorage, textFileNames))
        {
            cout << textFileNames << endl;
        }
        myStorage.close();

        cout << "\n\n";
        cout << "--------------------------" << endl;

        cout << "Open files(1) or go back to home(2)?: ";
        cin >> openFilesChoice;

        if (openFilesChoice == 1)
        {
            cout << "--------------------------"
                << endl;
            cout << "Enter Name: ";
            cin >> getFileName;
        }
        else
        {
            start();
        }

        openFileName();
    }
    // check if file is empty
    bool isFileEmpty(const string& filename)
    {
        ifstream file(filename);
        return file.peek() == ifstream::traits_type::eof();
    }
    // check if file is empty

    void openFileName()
    {

        /*open file with file name */

        gfnOpenFile = getFileName + ".txt";

        system("CLS");
        cout << "Here is the contents of your txt file: \n"
            << endl;

        if (isFileEmpty(gfnOpenFile))
        {
            cout << "The file is empty . . ." << endl;
            fileOptions();
        }
        else
        {
            cout << "--------------------------" << endl;

            // display txt
            ifstream readFile(gfnOpenFile);

            string readString;
            while (getline(readFile, readString))
            {
                cout << readString << endl;
            }
            readFile.close();
            // display txt
            cout << "--------------------------" << endl;

            fileOptions();
        }
    }
    void fileOptions()
    {
        /*
        edit, close, next line, Display new Content
        */
        cout << "\n\n";
        cout << "Edit(1) Close(2)" << endl;
        cout << "Enter: ";
        cin >> fileOptionsChoice;

        switch (fileOptionsChoice)
        {
        case 1:
            editFIle();
            break;
        case 2:
            openExistingFile();
            break;

        default:
            break;
        }
    }
    void editFIle()
    {
        lineCount = 0;
        system("CLS");

        cout << "        CONTENTS         " << endl;
        cout << "--------------------------" << endl;

        // display txt
        ifstream readFile(gfnOpenFile);

        string readString;
        while (getline(readFile, readString))
        {
            cout << readString << endl;
        }
        readFile.close();
        // display txt
        cout << "--------------------------\n\n"
            << endl;

        cout << "Add text in the new line (1)" << endl;
        cout << "Edit existing line       (2)" << endl;
        cout << "Delete a line            (3)" << endl;
        cout << "Close File               (4)" << endl;
        cout << "----------------------------" << endl;
        cout << "Enter: ";
        cin >> getEditFileChoice;

        switch (getEditFileChoice)
        {
        case 1:
            textToNewLine();
            break;
        case 2:
            editExistingLine();
            break;
        case 3:
            deleteCurrentLine();
            break;
        case 4:
            start();
        default:
            break;
        }
    }
    void deleteCurrentLine()
    {
        system("CLS");

        cout << "        CONTENTS         " << endl;
        cout << "--------------------------" << endl;

        // display txt
        ifstream readFile(gfnOpenFile);
        if (!readFile.is_open())
        {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        string readString;
        int lineNumber = 1; // Line number counter

        while (getline(readFile, readString))
        {
            cout << readString << endl;
            lineNumber++; // get line # count
        }
        readFile.close();
        cout << "--------------------------\n\n"
            << endl;
        // display txt

        // Clear any remaining characters from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int lineToDelete;
        cout << "Enter the line # to delete: ";
        cin >> lineToDelete;

        ifstream inputFile(gfnOpenFile);
        ofstream tempFile("temp.txt");

        lineNumber = 1;
        // loops to reach each line form original file
        // if line # matches userInput
        // it skips writing that file to the temp file
        while (getline(inputFile, readString))
        {
            if (lineNumber != lineToDelete) // checks if line# matches userLine#
            {
                tempFile << readString << endl;
                // if does not match it skips it
            }
            lineNumber++; // line# increments to keep track of next line
            // until match
        }

        inputFile.close();
        tempFile.close();

        // Delete the original file and rename the temporary file
        // original file is delete using the remove() func
        // temp file is renamed to the original file using rename() func
        if (remove(gfnOpenFile.c_str()) != 0)
        {
            // remove(gfnOpenFile.c_str()), func removes original file
            // c_start() convert string into c-style string to use func
            cerr << "Error: Unable to delete the original file." << endl;
            return;
        }
        // renames temp file to old file
        if (rename("temp.txt", gfnOpenFile.c_str()) != 0)
        {
            cerr << "Error: Unable to rename the temporary file." << endl;
            return;
        }

        cout << "Line " << lineToDelete << " deleted successfully." << endl;

        // timer
        chrono::seconds duration(3);
        this_thread::sleep_for(duration);
        // timer

        editFIle();
    }

    void editExistingLine()
    {
        system("CLS");

        cout << "        CONTENTS         " << endl;
        cout << "--------------------------" << endl;

        // display txt
        ifstream readFile(gfnOpenFile);
        if (!readFile.is_open())
        {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        string readString;
        while (getline(readFile, readString))
        {
            cout << readString << endl;
        }
        readFile.close();
        cout << "--------------------------\n\n"
            << endl;
        // display txt

        // Clear any remaining characters from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Which line would you like to edit ?" << endl;
        cout << "Enter #: ";
        cin >> userLineNum;

        cout << "Enter new content for line " << userLineNum << ": ";
        cin.ignore(); // Clear the input buffer
        getline(cin, userNewLine);

        ifstream inputFile(gfnOpenFile);
        ofstream tempFile("temp.txt");

        string line;
        while (getline(inputFile, line))
        {
            lineCount++;
            if (lineCount == userLineNum)
            {
                tempFile << userNewLine << endl;
            }
            else
            {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove(gfnOpenFile.c_str());
        rename("temp.txt", gfnOpenFile.c_str());

        cout << "Line #: " << userLineNum << " edited Successfully" << endl;

        // timer
        chrono::seconds duration(3);
        this_thread::sleep_for(duration);
        // timer

        editFIle();
    }
    void textToNewLine()
    {
        system("CLS");

        cout << "        CONTENTS         " << endl;
        cout << "--------------------------" << endl;

        // display txt
        ifstream readFile(gfnOpenFile);
        if (!readFile.is_open())
        {
            cerr << "Error: Unable to open the file." << endl;
            return;
        }

        string readString;
        while (getline(readFile, readString))
        {
            cout << readString << endl;
        }
        readFile.close();
        cout << "--------------------------\n\n"
            << endl;
        // display txt

        // Clear any remaining characters from the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Write here: ";

        ofstream writeSentence(gfnOpenFile, ios::app);
        if (writeSentence.is_open())
        {
            // loop for # of lines

            getline(cin, sentence);
            writeSentence << sentence << endl;
        }
        writeSentence.close();

        cout << "Going to Display . . ." << endl;
        // timer
        chrono::seconds duration(3);
        this_thread::sleep_for(duration);
        // timer

        editFIle();
    }
};

int main()
{

    textEdit t;

    t.start();
}
