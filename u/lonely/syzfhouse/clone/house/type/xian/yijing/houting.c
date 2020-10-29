// ting.c

inherit "/inherit/room/house_room";

void create()
{
    set("short", "后厅");
    set("long", @LONG
这里是位于花园后侧的一间内厅，是主人招待知交好友的地方，陈设
朴素雅致，打扫得纤尘不染。东面是书斋，西侧是琴房。楼上则是主人的
卧室。
LONG);

    set("exits",
    ([
        "west"  : __DIR__"qinfang",
        "east"  : __DIR__"shuzhai",
        "up"    : __DIR__"wofang",
        "north" : __DIR__"houyuan",
        "south" : __DIR__"huayuan",
    ]));

    set("no_learn", 1);
    set("owner", "OWNER");
    set("owner_name", "某人");
    set("resource/water", "茶水");
    setup();
    restore();
}
