#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "戏院后台");
        set("long", @LONG
这里是长安戏院的后台，后台不大，却打扫得很干净。几个戏子
正在后台化妆，看见你来了，都用很奇怪的眼神盯着你。
LONG );
        set("exits", ([
                "south" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 2,
                __DIR__"npc/xizi2" : 1,
                __DIR__"npc/xizi3" : 1,
        ]));

	set("coor/x", -2760);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        int i;
        
        if (dir == "south")
        {
                message_vision(
                        "\n$N一曲唱罢，一揖作礼，身子平飞，从台上跃出，双手兀自\n"+
                        "抱拳向观众行礼，姿态美妙，众人齐声喝采。\n", me);
                        
                i=query("meili", me);
                if (i < 20) 
                {
                        i = i + 10;
                        set("meili", i, me);
                        message_vision(HIC "\n$N的魅力值提高了。\n" NOR, me);
                }
        }
        return ::valid_leave(me, dir);
}