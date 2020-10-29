//xunlei.c 迅雷剑

#include <ansi.h>

inherit F_SSERVER;

string name() { return "迅雷剑"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("shenlong-jian", 1);
        damage = lv + random(lv/2) + (int)me->query_skill("sword",1);
        attack = lv + random(lv/2);
        speed = me->query_skill("sword")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
             return notify_fail("「迅雷剑」只能对战斗中的对手使用。\n");

        if( query_temp("xunlei_yushi", me) || query_temp("xunlei", me) )
             return notify_fail("你剑势未尽，不能再施展「迅雷剑」！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
             return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<300 )
             return notify_fail("你的内力不够！\n");

        if( me->query_skill("shenlong-jian", 1) < 100 )
             return notify_fail("你的「神龙剑法」未臻高妙境界，无法使用「迅雷剑」！\n");

        msg=HIR"\n$N手中"+query("name", weapon)+HIR"剑尖指向自己胸口，剑柄斜斜向外，怪异之极，竟似回剑自戕一般！\n\n"NOR;
        message_combatd(msg, me,target);
        me->start_busy(1);
        ob = me->select_opponent();
        set_temp("xunlei", 4, me);
            addn("neili", -5, me);
        me->set_temp("xunlei_yushi");
        call_out("checking", 1, me, target);
        return 1;
}


  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
        if ( !objectp( me ) ) return;
        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                tell_object(me, "\n你手中无剑，当下停止了迅雷剑的架势。\n" NOR);
                delete_temp("xunlei", me);
                return;
        }
        else if( query("weapon_prop", weapon) == 0){
                tell_object(me, "\n你的"+weapon->name()+"已毁，无法持续迅雷剑的攻势！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
          else if( query("neili", me)<300){
                  message_combatd(HIR"$N的内劲後继无力，不得不停止迅雷剑的攻势！\n" NOR, me,target);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->query_skill_mapped("sword") != "shenlong-jian" ) {
                tell_object(me, HIR "\n你转而施展其他剑法，无法再以迅雷剑攻敌！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->is_busy() ) {
                tell_object(me, HIR "\n你现在动作不够灵活，无法继续维持迅雷剑攻势！\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if (!me->is_fighting() || !objectp(target)) {
                tell_object(me,  "\n你现在没有和人过招，当下收回了迅雷剑的攻势。\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        if( environment(target) != environment(me) ) {
                tell_object(me, "你见对方已经不在这里，当下停止了迅雷剑的攻势。\n");
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else{
                addn_temp("apply/damage", damage*2, me);
                addn_temp("apply/attack", attack*2, me);

                if( query_temp("xunlei", me) == 4)message_combatd(HIY"\n$N纵身近前，"+weapon->name()+HIY"陡然弯弯弹出，剑尖直刺$n，出招之快真乃为任何剑法所不及！\n"NOR,me,target);
                if( query_temp("xunlei", me) == 3)message_combatd(HIW"\n$N伸指在"+weapon->name()+HIW"上一弹，剑声嗡嗡，有若龙吟，"+weapon->name()+HIW"颤处，剑锋来势神妙无方！\n"NOR,me,target);
                if( query_temp("xunlei", me) == 2)message_combatd(HIG"\n$N陡然间大喝一声，"+weapon->name()+HIG"上寒光闪动，喝道：「"+target->name()+HIG"，可小心了！」\n"NOR,me,target);
                if( query_temp("xunlei", me) == 1)message_combatd(HIR"\n见$N随手挥剑，"+weapon->name()+HIR"颤处，前后左右，瞬息之间已攻出了四四一十六招！\n"NOR,me,target);
                addn("neili", -30, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn_temp("apply/damage", -damage*2, me);
                addn_temp("apply/attack", -attack*2, me);
                if( query_temp("xunlei", me) == 1){
                        message_combatd(HIY "\n$N顺势圈转手中"+weapon->name()+HIY"，一十六手「迅雷剑」已然尽数使出！\n" NOR, me, weapon);
                        call_out("xunlei_end", 12, me);
                        me->start_busy(2);
                }
                else {
                        me->set_temp("xunlei_attack");
                        set_temp("xunlei",query_temp("xunlei",  me)-1, me);
                        call_out("checking", 1, me, target);
                }
        }
}

void xunlei_end(object me)
{
        object weapon;
        if ( !objectp( me ) )
                return;
        weapon=query_temp("weapon", me);

        tell_object(me, HIR "\n你暗自调息，渐渐平复腾涌的真气。\n\n" NOR);

        delete_temp("xunlei", me);
        delete_temp("xunlei_yushi", me);

}
