#include <ansi.h>
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIB"英雄会"NOR);
        set("long", @LONG
这里是京城的一间豪华大宅，也不知是哪位富贾购置，后来有一天据说这位富
贾昔日乃是一位绿林大盗，从此这位富贾便音讯全无，可是过了不久，这里陆陆续
续多了不少武林人物出入，俨然成了京城中各绿林好汉的汇聚之所。
院子里备有马匹，来往的好汉们可以随时要马(yaoma)离开京城。
LONG
        );
        set("indoors", "city");
        set("exits", ([
                "northeast"  :  __DIR__"dao3",
                "southeast"  :  __DIR__"dao4",
                "northwest"  :  __DIR__"dao9",
                "southwest"  :  __DIR__"dao10",
        ]));

        set("no_fight",1);
        set("no_fly",1);
        setup();
}

void init()
{
       //add_action("do_order","yaoma");
}

int do_order()
{
      object me=this_player(),*ilist;
      int i;

      ilist=all_inventory(me);
      for( i=0;i<sizeof(ilist);i++ )
      if( ilist[i]->is_character() && query_temp("chousha", ilist[i]) )
      delete_temp("chousha", ilist[i]);

      if( query_temp("chousha", me) )
      {
       message("channel:rumor",HIB"【江湖仇杀】风闻"+query("name", me )
       +"在仇杀中临阵脱逃，仓皇离开了紫金城！\n"NOR,users());

       addn("score", -1000, me);
       delete_temp("chousha", me);
      }
      message_vision(YEL"$N一把牵过马匹缰绳，纵身跃上马背，飞奔而去......\n"NOR,me);
      me->move("/d/city/wumiao");

      return 1;
}
