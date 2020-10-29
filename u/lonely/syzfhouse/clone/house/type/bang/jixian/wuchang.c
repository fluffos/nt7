// xiaoyuan.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "练武场");
    set("long", @LONG
一块平整的场地，是帮中弟子练武的地方。
LONG);

    set("exits",
    ([
        "south" : __DIR__"xiaoyuan",
        "north" : __DIR__"xiaoting",
    ]));

    set("owner_name", "某人");
    set("owner", "OWNER");
    set("outdoors", "OUTDOORS");

    setup();
    restore();
}
