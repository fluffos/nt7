// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "前厅");
    set("long", @LONG
这里是主人迎接八方来客的地方。大凡客人来拜见主人，少不得在这
里寒暄叙话，了尽仰慕之情。东西两侧各是一间厢房。
LONG);

    set("exits",
    ([
        "east"  : __DIR__"dongxiang",
        "west"  : __DIR__"xixiang",
        "south" : __DIR__"qianyuan",
        "north" : __DIR__"huayuan",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");
    set("resource/water", "茶水");
    setup();
    restore();
}
