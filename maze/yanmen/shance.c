#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山侧"NOR);
        set("long", @LONG
这里就是「大宋」军营驻扎地了，远远地可以看见一面大旗，上面书着一个
斗大的隶书「宋」字，再走近些就到军营了，寻常人还是不要靠近的好，省得被
当成细作捉起来。
LONG
);
        set("defence",120);
        set("no_fly", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "south" :   __DIR__"gate",
               "north"  : __DIR__"shibi",
        ]));    

        set("objects", ([

        ]));
    
        setup();
}

              
/*
void init()
{
      object me=this_player();

      if( me->query_temp("jun_quest/party") == "meng" )
       add_action("do_break","break");
       else
      if( me->query_temp("jun_quest/party") == "song" )
      add_action("do_repair","repair");
}
*/

int do_repair()
{
      object room=this_object(),me=this_player();

      if( me->is_busy() )
      return notify_fail("你正忙着呢！\n");

      if( room->query("defence") > 120 )
      return notify_fail("山侧的防御工事已经修理好了！\n");
      else
      {
       message_vision(
       HIW"$N带着一支队伍紧张地抢修着山侧的防御工事！\n"NOR,me);
       room->add("defence",random(me->query_temp("jun_quest/group")));
       me->start_busy(2+random(2));
       return 1;
      }
}

int do_break()
{
      object room=this_object(),me=this_player();

      if( me->is_busy() )        
      return notify_fail("你正忙着呢！\n");

      if( room->query("defence") < 1 )
      {
       room->set("defence",0); 
       write("山侧的的防御已经被击破了，快冲进去啊！\n");
       return 1; 
      }
      else
      {
       message_vision(
       HIY"$N带着一支攻城队伍正加紧攻击着山侧的防御工事！\n"NOR,me);
       room->add("defence",-random(me->query_temp("jun_quest/group")));
       me->start_busy(2+random(2));
       return 1;
      }
}

