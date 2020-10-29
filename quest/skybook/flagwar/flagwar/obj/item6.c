#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"抢旗战 - "HIW"定身符"NOR, ({"fwar ding seal","seal"}) );
        set_weight(300);
        set("unit", "个");
        set("long", "抢旗战专用特殊物品，使用(shoot seal on <目标>)后令目标无法行动。\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

void init() 
{
   add_action("do_shoot","shoot");
}
int do_shoot(string arg) {
	object me, ob, target;
	string id;
	int damage;
	me = this_player();
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"不在你身上。\n");
  if(me->is_busy()) return notify_fail("你上一个动作还没有完成。\n");

  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"只能在抢旗战场使用。\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"只能在抢旗战的时候使用。\n");
  if(!arg || sscanf(arg, "seal on %s", id) != 1) return notify_fail("指令格式：shoot seal on <目标>。\n");
  if(!target = present(id, environment(me))) return notify_fail("这里没有这个人。\n");
  if(target == me) return notify_fail("你只能射别人。\n");
  if(!target->query_temp("flag_war")) return notify_fail("你只能对抢旗战的人使用。\n");
  message_vision("$N拿着$n对准"+target->name()+"，嘴中唸出喃喃之声。\n$n化作一道白光直扑"+target->name()+"而去。\n", me, ob);
  me->want_kill(ob);
  damage = 1000+random(2000);
  target->receive_damage("qi", damage, me);
  COMBAT_D->report_status(target);
  me->fight_ob(target); 
  target->kill_ob(me);
  me->start_busy(1);
  message_vision(HIY"突然间$n光华大盛，$N被吓的动都不敢动。\n", target, ob);
    	if(target->query_temp("flag_war/guard")) {
    		target->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N身上的特殊防护效果发挥效用抵挡住这次攻击。\n"NOR, target);
    	} else target->start_busy(10);
  destruct(ob);
  return 1;
}