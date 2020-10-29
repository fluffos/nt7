// Obj /d/ruzhou/npc/obj/jiuxi.c
// llm 99/07/09

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("酒席", ({ "jiuxi" }));
   /*if( clonep() )
       set_default_object(__FILE__);
   else*/
   {
                set("long", "这是一桌五色齐全、香味四溢、丰盛的酒席。\n"
   HIG"八味拼盘(pingpan)  珍品杲羹(guogeng)  红烧蹄膀(tipang)\n"
      "松子桂鱼(guiyu)    香菇菜心(caixing)  清炖甲鱼(jiayu)\n"
      "人参鸡汤(jitang)   翠玉豆腐(doufu)    海参青蟹(qingxie)\n"NOR);
                set("unit", "桌");
                set("value",1000);
set("no_drop",1);
      set("no_get","你也太黑心了吧？竟想扛走这一桌的酒席？弄得动吗？\n");
   }
   setup();
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me=this_player();
   if( me->is_busy() )
      return notify_fail("你上一个动作还没有完成。\n");
   if( query("food", me) >= me->max_food_capacity() )
           return notify_fail("你已经吃太饱了，还想吃什么？\n");
        switch(arg)
   {
           case "pingpan":
         message_vision("$N轻轻挑出一块拼盘冷菜，夹进嘴里津津有味地嚼起来。\n",me);
                   addn("food", 8, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      case "guogeng":
              message_vision("$N舀了一勺珍品果羹，“啊！”真是又香又甜。\n",me);
                   addn("food", 2, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 8, me);
         break;
      case "tipang":
              message_vision("$N叉了一大块的红烧蹄膀，狼吞虎咽地吃了下去。\n",me);
                   addn("food", 20, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "guiyu":
              message_vision("$N夹出一块松子桂鱼，只觉入嘴滑嫩，鲜美无比。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "caixing":
              message_vision("$N细心地挑了一些色香俱全的香菇菜心，慢慢地品味着，真香。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "jiayu":
              message_vision("$N一下子挖出一块甲鱼，急不可耐地塞进嘴里。\n",me);
                   addn("food", 20, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 4, me);
         break;
      case "jitang":
              message_vision("$N凑着香味大大地尝了一口人参鸡汤，果真是鲜美无比。\n",me);
                   addn("food", 2, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 15, me);
         break;
      case "doufu":
              message_vision("$N夹起一筷翠玉豆腐含在嘴里，一脸的幸福满足的神情。\n",me);
                   addn("food", 8, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      case "qingxie":
              message_vision("$N闷着头，剥开青蟹壳，一口一口地吮吸里面鲜美的汁肉。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      default:
              write("你想吃什么？菜上那么多菜都不吃？\n");
         break;
   }
        return 1;
}