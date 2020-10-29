//黄梁枕 (进入梦境所用的道具)
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "黄梁枕" NOR, ({ "huangliang zhen", "zhen" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "据说带着这个枕头睡觉(dream)可以进入梦境。\n" NOR);
                set("unit", "个");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
{
     add_action("have_dream", "dream");
}

int have_dream()
{
   object ob, me = this_player();

   if( !query("sleep_room", environment(me)) )
   {
      write("这里不能睡觉，你怎么做梦呀！\n");
      return 1;
   }

   foreach (ob in deep_inventory(me)) 
   { 
      if (ob->is_character()) 
      {   
         write("你身上带着个大活物怎么做梦呀?\n"); 
         return 1;
      }
   }
   message_vision("\n$N倒头往床上一躺，呼呼大睡起来。\n\n", me);
   message_vision("睡着睡着，$N的身体忽然变得轻飘飘地飞走了。\n\n", me);
   set_temp("dream_place", environment(me), me);
   me->move("/d/reborn/dream");
   message_vision(HIG"一瞬间$N竟飘到了梦境里。\n\n"NOR, me);
   destruct(this_object());
   return 1;
}