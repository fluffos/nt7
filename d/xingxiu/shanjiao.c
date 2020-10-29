// tianshan: /d/xingxiu/shanjiao.c
// Last Modified by Lonely on Feb. 28 2001
inherit ROOM;

void create()
{
        set("short", "天山脚下");
        set("long", @LONG
这里是天山脚下，西面是高耸入云的天山。天晴的时候可以看到山
顶上的冰川。一道天山将西域分为两半。北疆是西域各族的聚居区，南
疆是无边的塔克拉马干大沙漠。西南是通向天山南路回疆大草原的戈壁
沙漠。
LONG );
        set("outdoors", "xiyu"); 
        set("region", "xiyu"); 
        set("exits", ([
                "westup"    : __DIR__"tianroad1",
//                "east"      : "/d/gaochang/road",
                "east"      : "/d/hasake/senlin1",

                "southwest" : "/d/huijiang/gebi1",
                "northeast" : __DIR__"yilihe",
                "southeast" : __DIR__"silk5",
        ]));
//        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/trader" : 1,
                __DIR__"npc/hkid" : 1,
                __DIR__"npc/xxdizi1" : 1,
        ]));
        set("coor/x", -40000);
        set("coor/y", 10000);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        int current_water;
        object ob;
        if (dir == "southwest")
        {
                if (!userp(me)) return 0;
                current_water=query("water", me);
                if (current_water==0)
                {
                }

                if (current_water>0 && current_water<20)
                {
                        set("water", 0, me);
                }
                if (current_water>20)
                {
                        if( !objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
                        set("water", current_water-20, me);
                }
                return ::valid_leave(me, dir);
        }
        if( query_temp("wait_target", me) && 
                objectp(present("anran zi", environment(me))))
                return notify_fail("黯然子闪身拦在你面前，喝道：临阵想溜？给我滚回来！\n");
        if( query_temp("xx_rob", me) && 
                objectp(ob = present("hubiao biaoshi", environment(me))) &&
                query("target", ob) == me )
                return notify_fail("护镖镖师闪身拦住你的去路，看来是想把你给废了！\n");  
        if( query_temp("xx_rob", me) && objectp(present("shangdui",environment(me))) )
                return notify_fail("商队在这里呢，快抢(qiang)啊！\n");  
        return ::valid_leave(me, dir);
} 
