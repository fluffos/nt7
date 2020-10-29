// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "西厢");
    set("long", @LONG
这是一间位于西侧的厢房，东面通往正厅。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"qianting",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
