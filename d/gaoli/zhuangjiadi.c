
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "庄稼地");
        set("long", @LONG
这里是一片庄稼地。田地不大，但是庄稼看起来长的很好。有几个
小孩在旁边玩耍。远处有几个农夫在那里种田。一阵清风吹来，田野的
气息不禁让你心旷神怡。田地旁边放着几个草人，不知道踢几下会怎么
样。
LONG
);
        set("exits",([
        "southup" : __DIR__"xiaolu2",
        
        ]));
set("outdoors","gaoli");
        setup();
//        replace_program(ROOM);
}

void init()
{
   add_action("do_ci","ti");
}

int do_ci(string arg)
{
   object me;
   me=this_player();
   if(!arg||arg!="草人")
   return notify_fail("你要踢什么？\n");
  
   if(me->query("sen")<20)
   return notify_fail("你精神太差了！\n");
   if(me->query_skill("leg",1)>=101)
   return notify_fail("一个农夫跑了过来：嘿，不要乱碰我的草人！\n");
   if(me->is_busy())
   return notify_fail("你正忙着呢！\n");
   
   message_vision(YEL"$N一转身，然后抬腿朝草人踢去！\n"NOR,me);
   me->improve_skill("leg",me->query_int()/2+20+random(5));
   me->add("sen",-20);
   if(me->query_skill("leg",1)<50)
   message_vision("$N下盘不稳，险些跌倒！\n",me);
   else if(me->query_skill("leg",1)<100)
   message_vision("$N收势站好，微微一笑。\n",me);
   else if(me->query_skill("leg",1)<150)
   message_vision("$N潇洒的一个转身，轻轻收势站好！\n",me);
  
   return 1;
}
