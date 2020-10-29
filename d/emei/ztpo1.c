#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "钻天坡");
        set("long", @LONG
莲花石与洗象池之间，道路陡绝石栈若齿，直上蓝天，石蹬达一
千三百多级，是在陡峭山壁上开凿出来的坡道。人行其上，前后顶踵
相接，一如登天。这段路叫「鹁鸽钻天」，这段陡坡也因此而叫「钻
天坡」。这里西上坡顶便到洗象池，东下可达莲花石。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"lianhuashi",
          "westup"    : __DIR__"ztpo2",  
      ]));
      set("no_clean_up", 0);
        set("coor/x", -540);
        set("coor/y", -240);
        set("coor/z", 140);
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

                        tell_object(me, HIC "你爬上钻天坡，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不动了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}