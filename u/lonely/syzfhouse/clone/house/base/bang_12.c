
inherit "/inherit/room/house_base";

void create()
{
    set("short", "北市口外");
    set("long", @LONG
北市口外行人十分稀少，南面经北市口东行，可通往地安门西大
街，同样也是人迹罕至。一片气派不凡的宅院座落于此，看上去似乎
是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "south" : "/d/beijing/beishi-kou",
    ]));

    set("outdoors", "beijing");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
