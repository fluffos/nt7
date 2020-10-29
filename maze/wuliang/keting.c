// Room: keting.c
// By River 98/12
#include <wanted.h>
inherit ROOM;
void create()
{
        set("short", "客厅");
        set("long", @LONG
万劫谷的正房，这是一间大客厅，宽敞明亮，青石铺的地，两边靠墙摆着
的刀枪架，十八般兵器样样俱全。正中一张八仙桌，上有清茶一盏。旁边是谷
主坐的太师椅。
LONG
        );
        set("exits", ([
            "east" : __DIR__"xiangfang",
            "north" : __DIR__"guzhong",
        ]));

        set("objects", ([
              __DIR__"npc/zhong_wanchou" : 1,
        ]));

        setup();
}

int valid_leave(object me,string dir)
{ 
	if (dir == "east" && is_wanted(me))
		return 0;
     if( query("gender", me) == "男性"
      && dir == "east"
      && (present("zhong wanchou", environment(me))))
         return notify_fail("钟万仇上前拦住你的去路：你这小白脸要找我夫人作甚？\n");
         return ::valid_leave(me, dir);
}