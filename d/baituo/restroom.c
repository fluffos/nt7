inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
这是一家药铺，一股浓浓的药味让你几欲窒息，那是从药柜上的
几百个小抽屉里散发出来的。神医平一指坐在茶几旁独自喝着茶，看
也不看你一眼。
LONG );
        set("exits",([
                "south" : __DIR__"changlang",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);

        set("coor/x", -49990);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}