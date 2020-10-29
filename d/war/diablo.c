#include <ansi.h>

string *elements = ({"earth","fire","water","light"});

void set_coor()
{
        mapping coor;
	if( query("zone") )
	        coor="/d/war/diabloroom"->zone_range()[query("zone")];

	set("coor/x",coor["x1"]+random(coor["x2"]-coor["x1"]));
	set("coor/y",coor["y2"]+random(coor["y1"]-coor["y2"]));
	set("coor/z",coor["z1"]+random(coor["z2"]-coor["z1"]));
        return;
}

string *elements(string act)
{
        if(act=="act1") elements=({"earth"});
	if(act=="act2") elements=({"fire"});
        if(act=="act3") elements=({"water"});
	if(act=="act4") elements=({"light"});
	if(act=="act5") elements=({"earth","fire"});
	if(act=="act6") elements=({"water","light"});
	return elements;	
}