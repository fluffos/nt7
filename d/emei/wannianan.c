#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "万年庵");
        set("long", @LONG
万年庵建在一座突起的山峰上，周围古木森森，清泉淙淙，闲步
无坎，吟游无坷，景色非常迷人。由此西上过十二盘可达华严顶，南
下至白龙洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "southdown" : __DIR__"bailongdong",
          "westup"    : __DIR__"shierpan1",
          "enter"     : __DIR__"wnadian",
      ]));
        set("coor/x", -470);
        set("coor/y", -220);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "westup")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "你爬上十二盘，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不动了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}