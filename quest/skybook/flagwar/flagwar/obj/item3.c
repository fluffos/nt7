#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIG"抢旗战 - "HIW"五行反制符"NOR, ({"fwar give block seal","seal"}) );
        set_weight(300);
        set("unit", "个");
        set("long", "抢旗战专用特殊物品，使用(apply)后可增加一次特殊防护效果。\n");
        set("value", 1);
        set("can_be_applied", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

int do_apply(object me) {
	object ob;
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"不在你身上。\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"只能在抢旗战的时候使用。\n");
  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"只能在抢旗战场使用。\n");
  message_vision("$N拿起$n，口中喃喃唸着听不懂的音节，手指着$n胡乱挥舞着。\n突然从$n冒出微微的光芒，$N看起来不知道那里变的有些不同了。\n", me, ob);
	me->add_temp("flag_war/guard", 1);
  destruct(ob);
  return 1;
}