
inherit "/inherit/room/house_base";

void create()
{
    set("short", "清平路西");
    set("long", @LONG
清平路向南，直出福州南门。路面十分地干净，听着街上行人的
闽南话，虽然一个字也听不懂，但总是觉得怪好听的。路的西面座落
着好大的一片宅院，看上去似乎是某个帮会的驻地所在。
LONG);

    set("exits",
    ([
        "east"  : "/d/fuzhou/qingping-lu",
    ]));

    set("outdoors", "fuzhou");
    set("max_build", 1);
    set("can_build", "bang");

    setup();
    restore();
}
