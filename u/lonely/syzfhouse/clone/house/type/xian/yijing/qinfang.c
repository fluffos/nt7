// xixiang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "琴房");
    set("long", @LONG
这里是主人闲来弹琴之处，房内陈设甚为简单，一角置着琴榻琴凳，
另一角放着香炉。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"houting",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
