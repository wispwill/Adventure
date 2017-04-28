//made by Laura
class partyanimal : public werewolf
{//BROKEN FIX THIS
public:
	partyanimal(string nm, place &loc, int thresh) : werewolf(nm, loc, thresh) {};
	virtual void partyanimal::eat_person(person *persn);
};
//beautiful
//const string werewolf::greeting = " grrr ... I'm gonna *HIC* eat yah ";

void partyanimal::eat_person(person *persn)
{
	if (persn->has_thing("beer"))//check if person has beer
	{
		cout << get_name() << " says \"OOH, IS THAT BEER?\"" << endl;
		//drop beer
		persn->drop(persn->get_thing("beer"));
		//party animal picks it up
		take(persn->get_thing("beer"));
		cout << get_name() << " takes your beer and leaves you alone." << endl;	
	}		
	else
	{
		werewolf::eat_person(persn);
	}
}