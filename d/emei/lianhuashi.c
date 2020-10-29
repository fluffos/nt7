#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "莲花石");
        set("long", @LONG
这是莲花石。此处岩石纹理纵横，形似莲花颜如芙蓉，仿佛萼瓣
层叠，细蕊欲绽。上有一庵，叫「莲花社」。由此往西上直达洗象池，
东下左通华严顶，右通九老洞。
LONG );
      set("objects", ([
           CLASS_D("emei") + "/su" : 1,
           CLASS_D("emei") + "/ling" : 1,
      ]));
      set("outdoors", "emei");
      set("exits", ([
          "southeast" : __DIR__"jldongkou",
          "eastdown"  : __DIR__"huayanding",
          "westup"    : __DIR__"ztpo1",  
      ]));
        set("coor/x", -530);
        set("coor/y", -240);
        set("coor/z", 130);
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