#include <ansi.h>

inherit ITEM;
int do_eat(string);
void init();

void init(){
  if (!wizardp(this_player())) {
    set("no_get","你手里一松，内丹从指间滑落！\n");
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+query("name", this_object())+"的价值？还是自己留着吧。\n");
  }
  add_action("do_eat", "eat");
}
void create(){
    set_name( HIY "内丹" NOR , ({"nei dan", "dan"}));
  set_weight(90);
  /*if (clonep())
    set_default_object(__FILE__);
  else*/ {
    set("unit", "颗");
    set("long", "一颗金黄色的丹丸，略微能闻到些许香气。\n");
    set("value", 0);
    set("drug_type", "补品");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg){
  object me = this_player();
  if (arg!="dan" && arg!="nei dan")   return 0;

   addn("max_neili", random(30), me);
  addn("max_jing", random(30), me);
  addn("max_qi", random(30), me);
  addn("combat_exp", random(1000), me);
  message_vision(HIG "$N轻轻掰开一颗内丹送入嘴中，一时间香气四溢。
只见$N脸慢慢变得通红，好象非常痛苦的样子，一会儿，\n 看起来充满了力量！\n" NOR, me);
  destruct(this_object());
  return 1;
}