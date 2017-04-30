//made by Laura
class partyanimal : public werewolf
{
public:
	partyanimal(string nm, place &loc, int thresh) : werewolf(nm, loc, thresh) {};
	virtual void partyanimal::eat_person(person *persn);
};

void partyanimal::eat_person(person *persn)
{
	if (persn->has_thing("beer"))//check if person has beer
	{
		thing* beer = persn->get_thing("beer");
		cout << get_name() << " says OOH, IS THAT BEER?" << endl;
		//drop beer
		persn->drop(beer);
		//party animal picks it up
		take(beer);
		cout << get_name() << " takes your beer and leaves you alone." << endl;	
	}		
	else
	{
		werewolf::eat_person(persn);
	}
}