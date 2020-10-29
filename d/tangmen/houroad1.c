//houroad1.c                四川唐门—青石小路

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青石小路");
        set("long",
"这里是后宅西侧的青石小路。隐隐的可以听到远处传来清脆的流水声\n"
"，展目望去已经可以看见在风中摇摆的片片荷叶。一阵清风吹过带来一股\n"
"荷花清香。\n"
);
        set("exits", ([
                        "west" : __DIR__"houroad2",
                        "south" : __DIR__"nzlangw1",
                        "north" : __DIR__"yaotian2",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 1,
        ]));
        set("area", "tangmen");
        set("outdoors", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if ( ( (dir == "north") || (dir == "west") )&& 
                (query("family/family_name", me) != "唐门世家") && 
                !wizardp(me) && (objectp( present("jia ding", environment(me)) ) ))
                return notify_fail("家丁一伸手，说道：“你不是唐门中人，不能再向前走了！”\n");

        if ( ((dir == "north") || (dir == "west")) && !wizardp(me) && 
                (objectp( present("jia ding", environment(me)) ) ) && 
                !query_temp("tangmen", me) )
                return notify_fail("家丁一恭身，说道：“没有任务你是不能进入这里的！”\n");

        if ( (dir == "north") && !wizardp(me) && 
                (objectp( present("jia ding", environment(me)) ) ) && 
                !query_temp("yao", me) )
                return notify_fail("家丁一恭身，说道：“没有任务你是不能进入药圃的！”\n");

                return ::valid_leave(me, dir);
}