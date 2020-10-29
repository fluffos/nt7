// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "黄药师居处");
        set("long", @LONG
这是桃花岛主黄药师的卧室，一张竹榻靠在屋东北角，窗前一几，几
上一张瑶琴，一本琴谱。瑶琴颜色黯旧，琴尾已完全烧焦，琴谱里夹着一
张纸，可以看见一些字迹。向窗外望去，隐隐可以看见一座坟茔。
LONG );
        set("objects", ([
                // __DIR__"obj/paper2"       : 1,
                CLASS_D("taohua") + "/huang" : 1,
                "/d/taohua/npc/shitong" : 2,
        ]));
         set("exits", ([
                "south" : __DIR__"wofang",
                "east" : __DIR__"changlang2",
        ]));
        
        set("coor/x", 8970);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
         "/clone/board/taohua_b"->foo();
}
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("huang yaoshi", this_object())))
        {
                return 1;
        }

        if (dir == "south")
                return guarder->permit_pass(me, dir);

        return 1;
}
