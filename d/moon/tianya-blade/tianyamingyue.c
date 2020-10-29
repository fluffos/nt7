 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target){
    string dodskill,msg;
 int extra, step,bonus,lvl,str;
    object weapon;
      weapon=me->query_temp("weapon");
       lvl = me->query_skill("tianya-blade",1);
     if ( me->query("class")!= "bandit")
     			return notify_fail("你的天涯明月刀已经失去了功效。\n");
        if ( lvl < 50)
        	                 return notify_fail("你的［天涯明月刀］还不够纯熟！\n");
        	                                  if( !target ) target = offensive_target(me);
    if( !target
 ||      !target->is_character()
  ||      !me->is_fighting(target) )
     return notify_fail("『天涯·明月』只能对战斗中的对手使用。\n");
          if(NATURE_D->is_day_time()) {
           extra= me->query_skill("blade");
 } else {                extra= me->query_skill("blade")*2;
    }
  bonus = me->query("combat_exp")/1000*extra/8000;
if (bonus>extra*4) bonus=extra*4;
	 	 str = 0;
        if (me->query_skill("tianya-blade",1)>500) str = me->query_skill("tianya-blade",1)/4;
        			if (me->query_skill("tianya-blade",1)>1000) str = me->query_skill("tianya-blade",1)/2;
        			 	if (me->query_skill("tianya-blade",1)>2000) str = me->query_skill("tianya-blade",1);
        			 me->add_temp("apply/skill_str",str);
   if (lvl <100) {
   	  me->add_temp("apply/attack",extra);
        me->add_temp("apply/damage",extra+bonus);
          msg = HIC"$N"HIC"乍然退步，旋身，反手，——拔刀。
刀既出，天上的玉钩也失去了光华，地上的万物都屏吸注视着$N"HIC"手中一弯明月。刀光如月，月光如刀。"NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
 me->add_temp("apply/attack",-extra);
           COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
    me->start_busy(1);
   }
 else {
me->add_temp("apply/attack",extra);
      me->add_temp("apply/damage",extra+bonus);
       msg = WHT"$N"WHT"乍然退步，旋身，反手，——拔刀。
刀既出，天上的玉钩也失去了光华，地上的万物都屏吸注视着$N"WHT"手中一弯明月。刀光如月，月光如刀。"NOR;
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
    msg = HIY"『天涯明月刀』" NOR;
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
combat_message_vision(HIC"刀光隐，明月现。\n"NOR,target);
me->add_temp("apply/attack",-extra);
    me->add_temp("apply/damage",-extra-bonus);
 me->start_busy(2);
}
 me->add_temp("apply/skill_str",-str);
  return 1;
}
