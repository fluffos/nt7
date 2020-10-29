// dongxiang.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "书斋");
    set("long", @LONG
这里是主人平素读书写字的地方，干净明亮。文房四宝整整齐齐的摆
在桌子上面。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"houting",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");

    setup();
    restore();
}
