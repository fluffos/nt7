// Room: /d/xiangyang/juyihuayuan.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "花园");
        set("long", @LONG
这是聚义馆的大花园。园内种着各种各样的花草，清风吹来，你
能闻到股股花香。园内东西两侧各有一排厢房，北面是一湖池水，水
上架着走廊，直通西大街。南面是馆内厨房，东南方向有一间物品房。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"      : __DIR__"juyifemale",
                "west"      : __DIR__"juyimale",
                "south"     : __DIR__"juyichufang",
                "north"     : __DIR__"juyilang",
                "southeast" : __DIR__"juyiwupin",
        ]));
        set("objects", ([
                __DIR__"npc/guofu" : 1,
        ]));
        set("coor/x", -7840);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( query("gender", me) != "男性" && dir == "west" )
                return notify_fail("男女有别，请到对面住！\n");

        if( query("gender", me) != "女性" && dir == "east" )
                return notify_fail("男女有别，请到对面住！\n");

        return ::valid_leave(me, dir);
}