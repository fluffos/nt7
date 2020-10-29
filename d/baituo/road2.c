// maco 2/17/2000

inherit ROOM;

void create()
{
        set("short", "小径");
        set("long", @LONG
这是条偏僻的小径，蜿蜒地绕入白驼山，四周悄然无声。遥望北
方，是一座深邃的山谷，气氛阴森，那就是白驼山的蛇谷。东边的岔
路通往白驼山庄的蛇场。
LONG );
        set("exits", ([ 
                "east"  : __DIR__"shechang",
                "north" : __DIR__"shegu1",
                "south" : __DIR__"barn",
        ]));
        set("objects",([
                "/clone/beast/jinshe" : random(3),
                "/clone/beast/dushe"  : 1 + random(3),
                "/clone/beast/fushe"  : random(2),
                "/clone/beast/qingshe": random(2),
                "/clone/beast/wubushe": random(3),
        ]));

        set("outdoors","baituo");
        replace_program(ROOM);
        set("coor/x", -49970);
        set("coor/y", 20100);
        set("coor/z", 30);
        setup();
}