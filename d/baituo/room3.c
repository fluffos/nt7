//room3.c

inherit ROOM;
void create()
{
        set("short","练功室");
        set("long", @LONG
这里是白驼山弟子的练功室。有几个制作精致的木人陪你练功。
LONG );
        set("exits",([
                "out" : __DIR__"fang",
        ]));

        set("objects",([
                "/clone/npc/mu-ren" : 3,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
}