// Room: northroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
这里一条北大街横贯东西。望向北边，是出城的北门。号称 "天
下幽" 的青城山，就是从这里出去。这里地当当道，行人却都过往匆
匆，小心翼翼，恨不得销声匿迹。因为南边一幢古色古香的建筑，就
是让天下武林闻风色变的川中唐门。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"   : __DIR__"northroad3",
            "west"   : __DIR__"northroad1",
            "south"  : __DIR__"tanggate",
            "north"  : __DIR__"northgate",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        me = this_player();
        if (dir == "south")
        return notify_fail("你一抬足，发现地上有毒，忙抽腿退回。\n");
        else  return 1;
}