// adventure.cpp  a basic text adventure game using objects and inheritance

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int NUM_DIRECTIONS = 6;

enum direction {north, south, east, west, up, down};

string dirstrings[NUM_DIRECTIONS] = {"north","south","east","west","up","down"};

string direction_to_string(direction dir)
{ return dirstrings[dir];
}

direction string_to_direction(string s)
{ for (int i=0; i<NUM_DIRECTIONS; i++)
    if (dirstrings[i]==s)
       return static_cast<direction>(i);
  cout << "Error: invalid string given to string_to_direction";
  exit(1);
}

enum kind {named_obj, thing_obj, place_obj, person_obj};

#include "named_obj.h"
#include "thing.h"
#include "place.h"
#include "person.h"
#include "werewolf.h"
#include "partyanimal.h"

vector<thing*> all_things;
vector<person*> all_people;

void can_go(place &from, direction dir, place &to)
{ from.add_neighbor(dir,&to);
}

void install_thing(thing &thng, place &loc)
{ all_things.push_back(&thng);
  loc.add_thing(&thng);
}

thing *string_to_thing(string s)
{ for (int i=0; i<all_things.size(); i++)
    if (all_things[i]->get_name()==s)
       return all_things[i];
  cout << "Error: invalid string given to string_to_thing";
  exit(1);
}

void install_person(person &persn)
{ all_people.push_back(&persn);
}

void clock()
{ for (int i=0; i<all_people.size(); i++)
    all_people[i]->clock();
}

int main()
{ place mccormick("McCormick Hall Lobby");
  place bakeless("Bakeless Hall Lobby");
  place computer_lab("Computer Lab");
  place bakeless_basement("Basement");
  place professors_office("Professor's Office");
  //created by Danny
  place bakeless_roof("Bakeless Roof");
  place professors_office_roof("Computer Lab Roof");
  place quad("Quad");

  can_go(mccormick,south,bakeless);
  can_go(bakeless,north,mccormick);
  can_go(bakeless,up,computer_lab);
  can_go(computer_lab,down,bakeless);
  can_go(bakeless,down,bakeless_basement);
  can_go(bakeless_basement,up,bakeless);
  can_go(mccormick,up,professors_office);
  can_go(professors_office,down,mccormick);
  //created by Laura
  can_go(bakeless, up, bakeless_roof);
  can_go(bakeless_roof, down, bakeless);
  can_go(computer_lab, up, professors_office_roof);
  can_go(professors_office_roof, down, computer_lab);
  can_go(mccormick, south, quad);
  can_go(quad, south, bakeless);
  can_go(bakeless, north, quad);
  can_go(quad, north, mccormick);

  person me("Launy",mccormick,10000);
  install_person(me);
  person veronica("Veronica",mccormick,2);
  install_person(veronica);
  //UNCOMMENT AND PUT WEREWOLVES IN THEIR PROPER PLACES/////////////////////////////////////////////////////
  werewolf cujo("Cujo",professors_office_roof,3);
  install_person(cujo);
  partyanimal spuds("Spuds", bakeless_basement, 9);
  install_person(spuds);
 // werewolf charlie("Charlie", bakeless_basement, 5);
 // install_person(charlie);
  //werewolves do not stay in places like they are supposed to

  thing disk("disk");
  install_thing(disk,computer_lab);
  thing beer("beer");
  install_thing(beer,professors_office);
  //created by Danny
  thing jetpack("jetpack");
  install_thing(jetpack,bakeless_basement);

  //main loop
  char line[99];
  string command, arg;
  me.look();

  while (true)
  {  cout << "> ";
     gets(line);
     command = strtok(line," \n");
     if (command == "quit")
       return 0;
     else if (command == "look")
       me.look();
     else if (command == "go")
     {  
		arg = strtok(NULL," \n");
        me.go_look(string_to_direction(arg));
     }
     else if (command == "take")
     { 
	   arg = strtok(NULL," \n");
	   if (me.same_room(arg))
		   me.take(string_to_thing(arg));
	   else
		   cout << "There is no such thing here." << endl;
     }
	 else if (command == "inventory")
	 {
		 me.inventory();
	 }
	 else if (command == "drop")
	 {
		 arg = strtok(NULL, " \n");
		 me.drop(string_to_thing(arg));
	 }
	 //added by Danny
	 else if (command == "fly") {
		 place* plc = me.get_location();
		 if (*plc == bakeless_roof && jetpack.owned())
			 me.move_to(&professors_office_roof);
		 else if (*plc == professors_office_roof && jetpack.owned())
			 me.move_to(&bakeless_roof);
		 else
			 cout << "You flap your arms hard and think light thoughts, but you move nowhere!" << endl;
	 }
	 else if (command == "wait")
       cout << "Time passes" << endl;
     else
       cout << "Unknown command (ignored)." << endl;
	 //Danny and Laura
	 //win condition check
	 if (jetpack.owned()&&jetpack.get_owner()->get_name() == "Launy") {
		 const vector<named_object*>::iterator itr = professors_office.get_things().begin();
		 bool disk_check;
		 bool person_check;
		 while (itr != professors_office.get_things().end()) {
			 if ((*itr)->get_name() == "disk")
				 disk_check = true;
			 if ((*itr)->get_name() == "Launy")
				 person_check = true;
		 }
		 if (disk_check && person_check)
			 cout << "Your jetpack malfunctions and rockets you upwards. " << endl;
			 cout << "You crash through the roof of the professor's office, sailing through the air. " << endl;
			 cout << "Bloomsburg students search against the harsh rays of the noon - day sun trying to find the source of the commotion." << endl;
		     cout << "They spot a lone adventurer, having bested the odds, soaring higher and higher." << endl;
			 cout << "After the students look little more than tiny specks of dust, you notice your trajectory is headed towards something." << endl;
			 cout << "After what seems minutes, the clouds clear and the target is clear.The Moon.That\'s the next chapter in this saga." << endl;
			 cout << "Congratulations, you won!" << endl;
			 char c;
			 cin >> c;
			 exit(0);
	 }
     clock();
  }
}