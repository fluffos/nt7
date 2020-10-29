// This program is a part of NT MudLIB
// lianhuan.c 连环飞鹰抓


#include <ansi.h>

inherit F_SSERVER;

string name() { return "连环飞鹰抓"; }

int perform(object me, object target)
{
        int claw, lv, i, hit;
        string weapon, lzg_msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("搜骨鹰爪功龙爪八显只能对战斗中的对手使用。\n");

        if( query_temp("lzg_effect", me) )
                return notify_fail("你刚才已经使出了搜骨鹰爪功连环攻击，一时难以再行抢攻！\n");

        if ( query_temp("weapon", me) )
                return notify_fail("搜骨鹰爪功连环攻击必须空手方可施展。\n");

        if( me->query_skill("force", 1) < 100 )
                return notify_fail("你的内功火候未到，无法施展搜骨鹰爪功连环攻击！\n");

        if( me->query_skill("claw",1) < 140 )
                return notify_fail("你的爪法修为有限，无法施展搜骨鹰爪功连环攻击！\n");

        if( me->query_skill("sougu",1) < 140 )
                return notify_fail("你的搜骨鹰爪功造诣未到，无法施展搜骨鹰爪功连环攻击！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的内力不足以使出搜骨鹰爪功连环攻击！\n");

        if( query("jingli", me) <= 200 )
                return notify_fail("你的精力不够使用搜骨鹰爪功连环攻击！\n");

        claw = me->query_skill("claw");
        lv = (int)me->query_skill("sougu-yingzhua",1);
        hit = (lv/100)*2;
        if(hit > 8) hit = 8;
        if(hit <4) hit = 4;

        addn_temp("apply/attack", lv/5, me);
        addn_temp("apply/unarmed_damage", lv/5, me);

        lzg_msg = HIY"\n$N突然间大喝一声，纵身而上，双手犹如狂风骤雨，";

        if(hit >= 4)lzg_msg += "「推爪式」、「盖爪式」、「掏爪式」、「托爪式」";
        if(hit >= 6)lzg_msg += "、「撩爪式」、「锁爪式」";
        if(hit >= 8)lzg_msg += "、「千爪式」、「飞爪式」";

        lzg_msg += "，"+chinese_number(hit)+"式连环，疾攻而至！\n"NOR;

        message_combatd(lzg_msg, me, target);
        set("lzg_times", hit, me);
        set("lzg_effect", 1, me);
        addn_temp("lzg_lianhuan", 3, me);
        for( i=0; i < hit; i++ )
        {
                addn_temp("lzg_lianhuan", 1, me);
                COMBAT_D->do_attack(me, target, weapon);
        }

        addn_temp("apply/attack", -lv/5, me);
        addn_temp("apply/unarmed_damage", -lv/5, me);

        message_combatd(HIY"\n这"+chinese_number(hit)+"式连环的飞鹰抓绵绵不绝，便如是一招中的"+chinese_number(hit)+"个变化一般，快捷无比！\n"NOR, me);

        addn("neili", -hit*20+20, me);
        addn("jingli", -hit*5, me);
        me->start_busy(1+random(2));
        delete_temp("lzg_lianhuan", me);
        delete_temp("lzg_times", me);
        call_out("remove_effect", hit*2, me);
        return 1;
}


void remove_effect(object me)
{
        if (!me) return;
        delete_temp("lzg_effect", me);
        tell_object(me, YEL"\n你微一调息，平复了施展搜骨鹰爪功後鼓荡奔腾的真气。\n"NOR);
}
