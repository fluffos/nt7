//Room: /d/suzhou/hongniang-zhaung.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

string look_sign(object me);

void create()
{
        set("short", "红娘堂");
        set("long", @LONG
这里就是天下夫妇定约结缘的红娘堂，只有在这里缔结婚约或是
解除婚约才能得到世人的承认。这里是一个不大的门厅，但是经过一
番修整之后，显得十分地气派。厅堂正中挂着一块雕着字的乌木匾牌
(sign)。
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hong-zoulang",
                "east" : "/d/suzhou/yinyuan-tang",
   ]) );

   set("item_desc", ([
           "sign": (: look_sign :),
   ]) );

   set("objects", ([
        "/d/city/npc/meipo" : 1,
      ]) );
   set("coor/x", 230);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
}

string look_sign(object me)
{
        return HIM"劝和不劝分\n"
   "求缘更求份\n"
   "红线前生系\n"
   "姻结一世人\n"NOR;
}

int valid_leave(object me, string dir)
{
         if( dir == "west" && query_temp("pending/pro", me) )
      delete_temp("pending/pro", me);
      return ::valid_leave(me, dir);
}
