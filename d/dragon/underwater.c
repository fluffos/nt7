inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "潭下");
        set("long",
"[1;32m潭水很深，冰凉的潭水浸得你骨头都发麻，一只随你一快儿\n"
"掉下来的朽木一起一伏，在水中荡漾。一线天光从你头顶上射下来，那样\n"
"微弱，你都不知道还有没有生还的机会……不过，还是想法子往上爬(cli\n"
"mb)吧。\n"
);
        set("no_magic", 1);
        setup();
}

void init()
{
   add_action("do_climb", "climb");
   if(interactive(this_player()))
   call_out("do_flush",60,this_player());
}

int do_climb(string arg)
{
   object me, room;

   me = this_player();
   if(me->is_busy())
        return notify_fail("你现在没空！\n");
   switch (random(3)) {
   case 0:
      message_vision("$N手脚并用地往上爬，才爬到一半，一失手又摔了下来。\n", me);
      me->receive_damage("jing",20);
        me->start_busy(5);
      break;
   case 1:
      message_vision("$N手脚并用地往上爬，眼看快到头了，结果一失手又摔了下来。\n", me);
      me->receive_damage("jing",40);
        me->start_busy(5);
      break;
   case 2:
      if(!arg || arg != "上" && arg != "up" ) return 0;
     room = find_object(__DIR__"spirit9");
     if(!objectp(room)) room=load_object(__DIR__"spirit9");
      me->move(room);
      message_vision("$N浑身湿淋淋地从水中爬了上来。\n", me);
      break;
   }
   return 1;
}

void do_flush(object me)
{
   object room;

   if(!me || environment(me) != this_object())
   return;
   tell_object(me,"\n你突然发觉潭里的水居然在流动！\n\n");
   tell_object(me,"水流好象带着你从潭底的一个暗道里涌出……\n");
   tell_object(me,"你陷入一片完全的黑暗之中，心中充满了恐惧……\n\n");
    room = find_object(__DIR__"lake");
    if(!objectp(room)) room= load_object(__DIR__"lake");
   me->move(room);
   tell_object(me,"不知道过了多久，你眼前一亮，被水流带出了湖面。\n\n");
}

