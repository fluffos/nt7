// Room: /d/shaolin/wuxing1.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIG "五行洞" NOR);
        set("long", @LONG
[1；32m这是五行洞。这里地面相对比较干燥些，四壁由宽厚的木板严严
实实的地封了起来，叩上去发出沉闷的笃笃声，看来不是实心的就是
有几尺厚，没有斧凿等利器休想劈开它们。不过你还是想下手试一试，
希望能从这里打开缺口。[2；37；0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing0",
                "south" : __DIR__"wuxing3",
                "west" : __DIR__"wuxing4",
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
                if (dir == "south")
                {
//                        write("*木生火*\n");
                        count=query_temp("wuxing/火", me);
                        count++;
                        set_temp("wuxing/火", count, me);
                        if (check_out(me))
                        {
                                write("你顺利地走出了五行迷宫。\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*木克土*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("你掉进机关，落入僧监。\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
