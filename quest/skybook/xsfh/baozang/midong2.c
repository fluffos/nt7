// by tangfeng 8/2004

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "密洞");
        set("long", @LONG
洞内深窈无比，神秘难测。你一走进来，便发觉洞中叉洞多如迷宫，怪异
莫测，似乎黝黑无底。
LONG);
        set("exits", ([
                "east" : __FILE__,
                "south" : __FILE__,
                "west" : __FILE__,
                "north" : __FILE__,
        ]));
   set("quest", 1);
   set("baozang",1);
   setup();

}
void init()
{
   add_action("do_use", "use");
}
int do_use(string arg)
{
   object ob, me;
   me = this_player();
   if(!living(me) ) return 0;
   if (me->is_busy() || me->is_fighting())
      return notify_fail("你正忙着哪！\n");
   if(!objectp(ob = present("fire", me)))
      return notify_fail("你手中没有火折。\n");
   if( !arg || arg=="" ) return 0;
   if( arg == "fire" ) {
      message_vision(BLU"$N点燃火折，把洞内照亮了一些，微弱的火光一闪一闪的。\n"NOR, me);
      message_vision(BLU"$N似乎看出密洞的一些门道。\n"NOR, me);
      me->set_temp("baozang/north_",2+random(8));//北
      me->set_temp("baozang/south_",2+random(8));//南
      me->set_temp("baozang/east_",2+random(8));//东
      me->set_temp("baozang/west_",2+random(8));//西
      tell_object(me,HIY"你又暗里推算一番，原来如此：东行"+chinese_number(me->query_temp("baozang/east_"))+"步，西行"+chinese_number(me->query_temp("baozang/west_"))
                        +"，北折"+chinese_number(me->query_temp("baozang/north_"))+"，南回"+chinese_number(me->query_temp("baozang/south_"))+"即可！\n"NOR);
      return 1; 
   }
}
int valid_leave(object me, string dir)
{
        if ( dir == "north")
              if(userp(me)) me->add_temp("baozang/north",1);
        if ( dir == "south")
              if(userp(me)) me->add_temp("baozang/south",1);         
        if ( dir == "east")
              if(userp(me)) me->add_temp("baozang/east",1);
        if ( dir == "west")
              if(userp(me)) me->add_temp("baozang/west",1);         

        if (me->query_temp("baozang/north") >= 13||me->query_temp("baozang/south") >= 13
           ||me->query_temp("baozang/east") >= 13||me->query_temp("baozang/west") >= 13)
        {
         	  message_vision(HIG"$N像没头苍蝇一样在洞里瞎钻，结果一头撞在洞壁上。你觉得你晕乎乎的，似乎撞傻了。\n"NOR, me);
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->start_busy(1);
            return notify_fail(HIB"你吃惊地发现，你现在的位置竟然就是最初的位置。\n"NOR);
        }  
        if (me->query_temp("baozang/north") == 10 && me->query_temp("baozang/south") == 10
          && me->query_temp("baozang/east") == 10 && me->query_temp("baozang/west") == 10)
        {
         	  message_vision(HIC"$N像没头苍蝇一样在洞里瞎钻，结果一头撞在洞壁上。你觉得你晕乎乎的，似乎撞傻了。\n"NOR, me);
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->delete_temp("baozang/north_");
            me->delete_temp("baozang/south_");
            me->delete_temp("baozang/east_");
            me->delete_temp("baozang/west_");
            me->move(__DIR__"jinku");
            tell_room(environment(me), me->name()+"从西边的密洞走了过来。\n", ({ me }));
            return notify_fail(HIB"你吃惊地发现，你终于走出了密洞。\n"NOR);
        } 
        if (me->query_temp("baozang/north_") 
            && me->query_temp("baozang/north") == me->query_temp("baozang/north_") 
            && me->query_temp("baozang/south") == me->query_temp("baozang/south_") 
            && me->query_temp("baozang/east") == me->query_temp("baozang/east_") 
            && me->query_temp("baozang/west") == me->query_temp("baozang/west_") )
        {
            me->delete_temp("baozang/north");
            me->delete_temp("baozang/south");
            me->delete_temp("baozang/east");
            me->delete_temp("baozang/west");
            me->delete_temp("baozang/north_");
            me->delete_temp("baozang/south_");
            me->delete_temp("baozang/east_");
            me->delete_temp("baozang/west_");
            me->move(__DIR__"jinku");
            tell_room(environment(me), me->name()+"从西边的密洞走了过来。\n", ({ me }));
            return notify_fail(HIC"你累得半死，终於走出了密洞。\n"NOR);
        }                          
        return ::valid_leave(me,dir);
}
 
