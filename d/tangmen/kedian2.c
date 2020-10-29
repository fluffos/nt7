// Room: /city/kefang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
        set("short", "唐门客店二楼");
        set("long",
"这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，不少\n"
"客人正和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，你蹑手\n"
"蹑脚地走了过去。\n"
);

        
        set("valid_startroom", 1);
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);

        set("exits", ([
                "down" : __DIR__"kedian",
        ]));

        set("area", "汴梁");

        setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "down")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}


