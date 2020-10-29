#include <ansi.h>
#include <room.h>;
inherit ROOM;

void create()
{
  set("short","百丈桥");
  set("long",@LONG
一座长长的索桥，桥身是用树藤和木板连起来的，一阵风吹来，
桥摇摇欲坠。你小心翼翼的走在桥上，抓紧两边的绳索，掂着脚踩着
桥板，这桥显得又远又长，你的心"砰砰砰"直跳。
LONG);
     set("outdoors", "天龙寺");
     set("exits",([
           "south" : __DIR__"bzqs",
           "north" : __DIR__"bzqn",
     ]));

     set("coor/x",-390);
  set("coor/y",-280);
   set("coor/z",30);
   setup();
}
void init()
{
    object me = this_player();
    if (random(100) > me->query_skill("dodge", 1)){
         message_vision(HIR"一阵大风吹来，$N不小心，从桥上掉了下去。\n"NOR, me);
    if(me->query_skill("dodge", 1) < 30){
       me->receive_damage("qi", 50);
       me->receive_wound("qi",  50);
       } 
    me->set_temp("last_damage_from", "失足从桥上掉下");
    me->move(__DIR__"goudi");
    tell_room(environment(me), "一阵大风吹过，"+me->name()+"失足从桥上掉了下来！\n",({ me }));
    }
}


