// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "东厢");
    set("long", @LONG
这是一间位于东侧的厢房，西面通往正厅。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"qianting",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
