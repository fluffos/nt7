inherit ROOM;

void create()
{
        set("short", "武器库");
        set("long", @LONG
这里是白驼山弟子的武器库，白驼山弟子可以到此拿取练功用的
各种武器。不过别派弟子是不允许进来的。
LONG );
        set("exits", ([
                "east" : __DIR__"yuanzi",
        ]));
        set("objects", ([
                __DIR__"npc/shiwei" : 1,
                __DIR__"obj/zheng" : 1,
                "/clone/weapon/gangzhang" : 2,
        ]));
        set("coor/x", -49980);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}