inherit ROOM;

void create()
{
        set("short", "洞内");
        set("long", @LONG
这里是山贼的老窝的所在。旁边有一侧洞，里面隐隐传来女子的
哭声。一个粗壮的山贼守卫在这里。
LONG );
        set("exits", ([
                "west"  : __DIR__"cedong",
                "south" : __DIR__"dongkou",
        ]));

        set("objects", ([
                __DIR__"npc/shanzei3" : 1,
        ]));

        set("coor/x", -49950);
        set("coor/y", 20050);
        set("coor/z", 20);
        setup();
        // replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
        object npc;
        
        if ( (dir == "west")
             && objectp(npc = present("shanzei tou", environment(me)))
             && living(npc) )
                return notify_fail("山贼头操起拳头：你想占我老婆的便宜？快滚！\n");
        return ::valid_leave(me, dir);
}