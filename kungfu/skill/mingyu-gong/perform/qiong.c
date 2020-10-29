// This program is a part of NT MudLIB
// qiong.c 琼楼玉宇

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "琼楼玉宇"; }

int perform(object me, object target)
{
        int bonus, hits;
        object weapon;
        mapping buff, data;
        string msg;
        int skill;
        int time;
        
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「琼楼玉宇」只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("空手才能施展「琼楼玉宇」。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( query("neili", me)<400 )
                return notify_fail("你的内力所剩无几，无法施展「琼楼玉宇」。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，无法施展「琼楼玉宇」。\n");

        if ( skill = me->query_skill("mingyu-gong", 1) < 200 )
                return notify_fail("你的明玉神功不够娴熟，不能使用「琼楼玉宇」。\n");

        if ( me->query_skill("unarmed", 1) < 200 )
                return notify_fail("你的基本拳脚不够娴熟，不能使用「琼楼玉宇」。\n");

        if( query("jiali", me)<1 )
                return notify_fail("你加力太少，无法使用「九羽天诛」。\n");

        if ( me->query_skill_mapped("force") != "mingyu-gong" )
                return notify_fail("你的内功没有使用明玉功，无法使用「琼楼玉宇」绝技。\n");
        if ( me->query_skill_mapped("parry") != "mingyu-gong" )
                return notify_fail("你的招架没有使用明玉功，无法使用「琼楼玉宇」绝技。\n");
        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
                return notify_fail("你的拳脚没有使用明玉功，无法使用「琼楼玉宇」绝技。\n");
        if ( me->query_skill_mapped("dodge") != "mingyu-gong" )
                return notify_fail("你的轻功没有使用明玉功，无法使用「琼楼玉宇」绝技。\n");
        if( query("gender", me) != "女性" )
                return notify_fail("你并非纯阴之体，无法使用「琼楼玉宇」绝技。\n");
        if( BUFF_D->check_buff(me, "mingyu_qiong") ) 
                return notify_fail("你正在使用「琼楼玉宇」。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "mingyue-qiong-over")) > 0 )
                        return notify_fail(MAG"你刚刚使用过「琼楼玉宇」，此时气血不调，还需等待"+time+"秒。\n"NOR);
        }

        bonus = me->query_skill("mingyu-gong", 1) / 3;
        bonus += me->query_skill("unarmed", 1) /3;
        bonus += me->query_skill("force", 1) /3;
        
        data = ([
                "attack": bonus,
                "unarmed_damage": bonus,
                "defense": bonus*2,
        ]);

        msg = WHT"〖"HIY"琼楼玉宇"WHT"〗\n\n"HIG"只见$N分光劲势再抖，像蛟龙出海，大鹏展翅，\n"
                "先是一团光芒，光芒蓦然爆开，化作一片光雨，漫天遍地向$n刺来！\n" NOR;
        
        buff = ([
                "caster": me,
                "target": target,
                "type"  : "mingyu_qiong",
                "attr"  : "bless",
                "name"  : "明玉功·琼楼玉宇",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的琼楼玉宇运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        set_temp("mingyu_pfm/qiong", bonus, me);
        addn("neili", -200, me);

        call_out("check_fight", 1, me, target, bonus);

        return 1;
}

void remove_effect(object me, int bonus)
{
        mapping buff, data;
        int time;
        
        BUFF_D->debuff(me, "mingyu_qiong", 1);
        delete_temp("mingyu_pfm/qiong", me);
        
        if ( me->is_fighting() && !me->is_busy() )
                me->start_busy(3);
        
        time  = 30;
        time -= ABILITY_D->check_ability(me, "cd-myg-qiong"); // ab门派减cd
                
        buff =  
        ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "mingyue-qiong-over",
                "attr"   : "curse",
                "name"   : "明玉功·琼楼玉宇",
                "time"   : time,
                "buff_msg" : "琼楼玉宇消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : HIY"经过一段时间的休息，你又可以使用「琼楼玉宇」了！\n"NOR,
                "disa_type": 0,
        ]);
        BUFF_D->buffup(buff);
        return;
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("mingyu_pfm/qiong", me) || query_temp("mingyu_pfm/qiong", me)<1
             || !target || ! (living(target)) )
        {
                message_combatd(WHT"\n$N长舒了一口气，手中的无形劲气也以不似先前一般凌厉了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N额头冒汗，看来是内力不随，手上的劲道一下消失不见了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
        {
                message_combatd(HIR"\n$N忽然招式一边，手上的劲道顿时消失得无影无踪。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n你装备上兵器，无法继续使用「琼楼玉宇」了。\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}


