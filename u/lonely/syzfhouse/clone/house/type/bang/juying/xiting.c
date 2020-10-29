// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "议事厅");
    set("long", @LONG
这是帮主和帮内重要人物商量大事之处，摆着不少桌椅。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"xiaoting",
        "north" : __DIR__"xixiang",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
