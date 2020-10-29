// wofang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "卧房");
    set("long", @LONG
这是偏处西侧的一间卧房，是帮中弟子休息之处。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"wofang",
        "south" : __DIR__"xixiang",
    ]));

    set("sleep_room", 1);
    set("no_fight", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
