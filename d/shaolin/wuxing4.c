// Room: /d/shaolin/wuxing4.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIW "五行洞" NOR);
        set("long", @LONG
[1；37m这是五行洞。地面是泥洼地，踩上去凹凸不平。四壁也都是土墙
筑成，摸上去相当干燥，时而还会掉下一大块灰土来。从墙角还能看
到一些老鼠洞。地面有时会隆起一长条，似乎有什么东西从土下钻了
过去。[2；37；0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing3",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing2",
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
                if (dir == "west")
                {
//                        write("*土生金*\n");
                        count=query_temp("wuxing/金", me);
                        count++;
                        set_temp("wuxing/金", count, me);
                        if (check_out(me))
                        {
                                write("你顺利地走出了五行迷宫。\n");
                                return 1;
                        }
                }
                else if (dir == "north")
                {
//                        write("*土克水*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("你掉进机关，落入僧监。\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
