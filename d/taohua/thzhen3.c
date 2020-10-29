// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;
#include <localtime.h>

string* dirs = ({
        "east", "southeast", "southeast", "southwest", "northeast", "northeast",
        "west", "south", "south", "northwest", "north", "north",
});

string* dirs2 = ({
        "e", "se", "se", "sw", "ne", "ne",
        "w", "s", "s", "nw", "n", "n",
});

void create()
{

        set("short", "桃花林");
        set("long", @LONG
你走了几步，忽然想到如果岛中有人，不如在原地静坐待变，如此乱
闯终究不是个了局。说也奇怪，开始你无论如何也离不开原地，现在想觅
路回去，却发现自己离原地好象越来越远了。
LONG );

                set("exits", ([
                "east" : __DIR__"thzhen3",
                "south" : __DIR__"thzhen3",
                "west" : __DIR__"thzhen3",
                "north" : __DIR__"thzhen3",
                "northeast" : __DIR__"thzhen3",
                "southeast" : __DIR__"thzhen3",
                "southwest" : __DIR__"thzhen3",
                "northwest" : __DIR__"thzhen3",
                ]));

        set("cost", 25);
        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2700);
        set("coor/z", 0);
        setup();

}

int valid_leave(object me, string dir)
{
  mixed local;
  int count,gain;
  mapping myfam;

  myfam=query("family", me);

  local = localtime(time()*60);

  count = ((local[LT_HOUR]+1)%24)/2;
  gain = random((me->query_skill("qimen-wuxing", 1)) / 30) + 1;
  if (dirs[count] == dir || dirs2[count] == dir) {
        me->move("/d/taohua/xiaojing");
        if (!myfam || myfam["family_name"] == "桃花岛") {
                if( query("combat_exp", me)<20000+random(10000)){
                            addn("combat_exp", gain, me);
                        if( query("potential", me)<query("max_potential", me) )
                                    addn("potential", gain, me);
                }
        }

        me->start_busy(random(3));
                return 1;
  }
  return ::valid_leave(me,dir);
}