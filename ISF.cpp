#include <iostream> 
#include <time.h> 
#include <fstream> 
#include <stdlib.h> 
#include <sstream> 
using namespace std;
class Session
{
public:
  int course_id;
  int number_of_professors;
  int number_of_classes;
  float number_of_lectures_per_week;
  int minimum_number_of_days;
  int* professors;
  int* classes;
};
ifstream Data;
long GlobalSeed = rand();

/*
  preprocessed data is all constant data that's difficult to read it dynamically from an input file 
*/
int Number_of_Professors = 100; 
int Profs_Memo[100][36]; 
string Prof[] = { "t000", "t001", "t002", "t003", "t004", "t005", "t006", "t007", "t008", "t009", "t010", "t011", "t012", "t013", "t014", "t015", "t016", "t017", "t018", "t019", "t020", "t021", "t022", "t023", "t024", "t025", "t026", "t027", "t028", "t029", "t030", "t031", "t032", "t033", "t034", "t035", "t036", "t037", "t038", "t039", "t040", "t041", "t042", "t043", "t044", "t045", "t046", "LinTed1", "AlfInf", "LetIta1", "FilTesItaCS", "LinGreA", "LinLatA", "LinLetGre1", "LinLetLat1", "LetCriAnt", "Papiro", "EpiGre", "StoMod1", "StoCon", "Geo2", "AntCul1", "StoFil1", "StoCriChi", "StoSci", "MetRicArc", "ArcCla1", "LinLatB", "Numism", "PrePro", "StoVicOriAnt", "ArcEge", "FilSem", "LegBenCul1", "Bibeco", "ConBenArcLib", "ResBenArcLib", "InfArcBib", "TeoTecCatCla", "StoArtMed1", "IcoIcoA", "StoArtMod1", "MetRicStoArt", "StoArtLatAmeA", "StoArtCon1", "PsiArt", "ArcPae", "LetIta4CS", "StoGreCS", "StoMedCS", "BioArcCS", "Antrop", "LegBenCul2", "StoArtMed2CS", "ChiAppBenCul", "StoArc", "StoArt", "FonSocAntCulI", "Bibgra", "BibgraCS"}; 
int Profs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}; 
int Number_of_Rooms = 9; 
int Rooms_Memo[9][36]; 
int Room_Capacity[] = { 130, 50, 50, 48, 65, 60, 30, 200, 450}; 
int Number_of_Classes = 193; 
int Number_of_Groups = 193; 
int Number_of_Sections = 193; 
int Sections_Memo[193][36]; 
int Number_of_Courses = 54; 
Session sessions[54]; 
int Table[304]; 
int Number_of_Slots = 36; 


/*
  Fetching works a post porocessing unit to fetch the course data that's not been fetched in the preprocessed section
  Data Fetched is the sessions affiliation
*/
void Fetch()
{
  Data.open("rawdata.in");
  cout << "Fetching File Opened" << endl;
  for (int i = 0 ; i < Number_of_Courses ; i++)
    {
      Session session;
      Data >> session.course_id;
      Data >> session.number_of_professors;
      Data >> session.number_of_classes;
      Data >> session.number_of_lectures_per_week;
      Data >> session.minimum_number_of_days;
      session.professors = new int[session.number_of_professors];
      for (int p = 0 ; p < session.number_of_professors ; p++)
        {
          int temp;
          Data >> temp;
          session.professors[p] = temp;
          cout << "Professor " << temp << " Added to session " << i << endl;
        }
      session.classes = new int[session.number_of_classes];
      for (int c = 0 ; c < session.number_of_classes ; c++)
        {
          int temp;
          Data >> temp;
          session.classes[c] = temp;
        }
      sessions[i] = session;
      cout << "Session : " << i << " => " << " Added " << endl;
    }
  
}

void print()
{
  ofstream test("test.text");
  for (int i = 0; i < Number_of_Courses; i++)
  {
    for (int k = 0; k < Number_of_Slots; k++)
    {
      test << Sections_Memo[i][k] << " ";
    }
    test << endl;
  }
  test << "==========================================================================================================================================" << endl;
}

int tablesession = 0;
int TableSession()
{
	return tablesession++;
}
/*
  Generate is responsible for generating the table by firstly allocating slots to sessions, then allocating rooms to slots
*/

void Generate()
{
  srand(GlobalSeed++);
  for (int i = 0; i < Number_of_Courses; i++)
  {
    cout << "In Session " << i << "That Has " << sessions[i].number_of_lectures_per_week << " Lectures Per Week and " << sessions[i].number_of_classes << " Classes to take " << endl;
    for (int s = 0; s < sessions[i].number_of_lectures_per_week; s++)
    {
      cout << " Into Lecture " << s + 1 << endl;

      int slot = 0;
      int trial = 0;
      while (true)
      {
        srand(GlobalSeed++);
        slot = rand() % Number_of_Slots + 1;
        cout << "Trial number : " << trial++ << " , Try Slot : " << slot << endl;
        if (trial > 10000)
        {
          print();
          break;
        }
        int flag = 0;
        for (int k = 0; k < sessions[i].number_of_classes; k++)
        {
          if (Sections_Memo[sessions[i].classes[k]][slot] != 0)
          {
            flag = 1;
            break;
          }
        }
        if (flag == 1)
        {
          continue;
        }
        else
        {
          Table[TableSession()] = slot;
          for (int k = 0; k < sessions[i].number_of_classes; k++)
          {
            Sections_Memo[sessions[i].classes[k]][slot] = 1;
            cout << "slot "<< slot << " reserved for course " << sessions[i].course_id << endl;
          }
          break;
        }
      }
    }
  }

  cout << tablesession << endl << "Population : ";
  for (int i = 0; i < tablesession; i++)
  {
    cout << Table[i] << " ";
  }
  for (int i = 0; i < tablesession; i++)
  {
    int room = 0;
    while(true)
    {
    	room = rand() % Number_of_Rooms + 1;
    	if (Rooms_Memo[room][Table[i]] != 1)
    	{
    		if()
    		{
    			
    			break;
    		}
    	} 
    }
  }
}

int main()
{
  srand(time(NULL));
  GlobalSeed = rand();
  Fetch();
  Generate();
  cout << endl << "table is generated and can be found at population.table file" << endl;
  return 0;
}
