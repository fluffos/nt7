#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "十二盘");
        set("long", @LONG
这里石阶陡折多弯，号称「十二盘」。由此西上可达华严顶，东
下则到万年庵。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northeast" : __DIR__"shierpan3",
          "westup"    : __DIR__"huayanding",
      ]));
        set("coor/x", -510);
        set("coor/y", -240);
        set("coor/z", 110);
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

                        tell_object(me, HIC "你爬上华严顶，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不动了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}