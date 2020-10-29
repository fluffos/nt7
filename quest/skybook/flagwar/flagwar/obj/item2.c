#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIG"抢旗战 - "HIW"五雷轰顶符"NOR, ({"fwar five thunder seal","seal"}) );
        set_weight(300);
        set("unit", "个");
        set("long", "抢旗战专用特殊物品，使用(apply)后可召唤五雷对自身所在地轰顶。\n");
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
  message_vision("$N拿起$n，口中喃喃唸着听不懂的音节，手指着$n胡乱挥舞着。\n突然从$n冒出耀眼的光芒，$n开始燃烧并释放出强大的力量。\n", me, ob);
  me->start_busy(3);
  ob->set("apply_room", base_name(environment(me)));
  SCHEDULE_D->set_event(1, 0, this_object(), "thunder_count", me, 1);

  return 1;
}

int thunder_count(object me, int num)
{
	int damage;
	string *color_str = ({ HIC,HIM,HIB,HIG });
	object ob = this_object();
	
	if(ob->query("apply_room") != base_name(environment(me))) {
		message_vision("$N燃烧怠尽了。\n", ob, me);
		destruct(ob);
		return 1;
	}
	
	if(num >= 5) {
		message_vision(HIR"最强大的一道天雷伴随着强大的能量落下。\n"NOR, ob, me);		
    foreach(object ppl in all_inventory(environment(me))) {
    	if(ppl == me) continue;
    	if(ppl->query_temp("flag_war/guard")) {
    		ppl->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N身上的特殊防护效果发挥效用抵挡天雷的轰击。\n"NOR, ppl);
    	  continue;
    	}
    	damage = 5000*num;
      ppl->receive_damage("qi", damage, me);
      COMBAT_D->report_status(ppl);
      me->want_kill(ppl); 
      me->fight_ob(ppl); 
      ppl->kill_ob(me); 
      if(random(2)) ppl->unconcious();
    }		
		message_vision("$N燃烧怠尽了。\n", ob, me);
		destruct(ob);
		me->start_busy(2);
	} else {
		message_vision(color_str[num-1]+"天空中乌云密布，仿佛受到$N"+color_str[num-1]+"的召引，第"+chinese_number(num)+color_str[num-1]+"道天雷疯狂的落下。\n"NOR, ob, me);
    foreach(object ppl in all_inventory(environment(me))) {
    	if(ppl == me) continue;
    	if(ppl->query_temp("flag_war/guard")) {
    		ppl->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N身上的特殊防护效果发挥效用抵挡天雷的轰击。\n"NOR, ppl);
    	  continue;
    	}
    	damage = 5000*num;
      ppl->receive_damage("qi", damage, me);
      COMBAT_D->report_status(ppl);
      me->want_kill(ppl); 
      me->fight_ob(ppl); 
      ppl->kill_ob(me); 
    }
		num++;
		SCHEDULE_D->set_event(1, 0, this_object(), "thunder_count", me, num);
	}
	me->start_busy(3);
	return 1;
}