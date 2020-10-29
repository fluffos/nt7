// Room: /d/shaolin/wuxing3.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIR "五行洞" NOR);
        set("long", @LONG
[1；31m这是五行洞。进来顿觉一股热浪扑面而来，冲得你差点晕了过去。
四周一片通红，地面上冒着丝丝白气，脚底剧烈的炙痛使你几乎立脚
不住。热风带着隆隆巨响冲击着耳鼓，令你觉得置身洪炉之中，全身
的水分都在被一滴滴地烤干。墙角上几具枯柴般的干尸就证明了这一
点。[2；37；0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing2",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing4",
        ]));
        set("no_clean_up", 0);
        setup();
}

int check_out(object me)
{
        int metal, wood, water, fire, earth;

        metal=query_temp("wuxing/金", me);
        wood=query_temp("wuxing/木", me);
        water=query_temp("wuxing/水", me);
        fire=query_temp("wuxing/火", me);
        earth=query_temp("wuxing/土", me);

        if ( metal > 0 &&
                metal == wood && metal == water &&
                metal == fire && metal == earth )
        {
                delete_temp("wuxing", me);
                me->move(__DIR__"andao2");
                return (1);
        }
        return (0);
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "north")
                {
//                        write("*火生土*\n");
                        count=query_temp("wuxing/土", me);
                        count++;
                        set_temp("wuxing/土", count, me);
                        if (check_out(me))
                        {
                                write("你顺利地走出了五行迷宫。\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*火克金*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("你掉进机关，落入僧监。\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
