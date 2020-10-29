#define ROOM_TYPE       1 

inherit F_DBASE;

int ob_type() {return ROOM_TYPE;}

int query_max_encumbrance() { return 100000000000; }

void create()
{
}
