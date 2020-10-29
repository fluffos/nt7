inherit ROOM;

void create()
{
        set("short", "练功房");
        set("long", @LONG
这里是白驼山弟子的练功房。里面有几个单间，是练功室。第子
们在里边砌磋武艺，绝对不允许外人打搅。
LONG );
        set("exits",([
                "west" : __DIR__"liangong",
                "1"    : __DIR__"room1",
                "2"    : __DIR__"room2",
                "3"    : __DIR__"room3",
        ]));

        set("objects",([
                __DIR__"npc/trainer" : 1,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}