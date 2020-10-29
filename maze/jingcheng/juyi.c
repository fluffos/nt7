#include <ansi.h>
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"聚义厅"NOR);
        set("long", @LONG
这里是京城的一间豪华大宅，据说曾经是一位与江湖白道颇有渊源的富贾购置，
这位富贾为了广结白道人士，经常在这里礼宴迎宾，久而久之，这里竟成了京城中
白道人士的暂居之所。
院子里备有马匹，来往的侠士们可以随时要马(yaoma)离开京城。
LONG
        );
        set("indoors", "city");
        set("exits", ([
                "northeast"  :  __DIR__"dadao27",
                "southeast"  :  __DIR__"dadao28",
                "northwest"  :  __DIR__"dadao33",
                "southwest"  :  __DIR__"dadao34",
        ]));

        set("no_fight",1);
        set("no_fly",1);
        setup();
}

void init()
{
//       add_action("do_order","yaoma");
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
                delete_temp("chousha", me);
                addn("score", -1000, me);
        }
        message_vision(YEL"$N一把牵过马匹缰绳，纵身跃上马背，飞奔而去......\n"NOR,me);
        me->move("/d/city/wumiao");
        return 1;
}
