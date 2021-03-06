// a place may contain things and has exits and adjoining places (neighbors)
class place : public named_object
{ public:
    place(string nm) : named_object(nm), things(0), neighbors(NUM_DIRECTIONS,NULL), exits(0) {}
    vector<named_object*> get_things() const {return things;}
    vector<direction> get_exits() const {return exits;}
    vector<place*> get_neighbors() const {return neighbors;}
    place *neighbor_towards(direction dir) const {return neighbors[dir];}
    void add_thing(named_object *thng) {things.push_back(thng);}
    void remove_thing(named_object *thng);
    void add_neighbor(direction dir,place *nbr)
      {neighbors[dir]=nbr; exits.push_back(dir);}
    kind get_kind() {return place_obj;}

	// added by Laura
	bool contains_thing(string thing) const;
	//
	
	
  private:
    vector<named_object*> things;
    vector<place*> neighbors;
    vector<direction> exits;
};

void place::remove_thing(named_object *thng)
{ for (int i=0; i<things.size(); i++)
    if ( things[i]->get_name() == thng->get_name() )
    {   for (int j=i+1; j<things.size(); j++)
          things[j-1] = things[j];
        things.pop_back();
    }
}

place heaven("Heaven");

//implementation for Laura added function
bool place::contains_thing(string name) const
{
	for (int i = 0; i < things.size(); i++)
	{
		if (things[i]->get_name() == name)
			return true;
	}
	return false;
}
//

//added by Danny
bool operator==(place loc1, place loc2)
{
	return loc1.get_name() == loc2.get_name();
}
//
