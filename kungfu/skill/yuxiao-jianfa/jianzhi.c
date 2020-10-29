
// jianzhi.c 剑指相配攻击
// 神雕侠侣(20)：玉箫剑法与弹指功夫均以攻敌穴道为主，剑指相配，精微奥妙

#include <ansi.h>

inherit F_SSERVER;

string name() { return "剑指相配"; }

void remove_effect(object me, object weapon, int speed, int damage);

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        object weapon;
        int speed, damage, sword;
        int skill;

        weapon=query_temp("weapon", me);

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("剑指相配攻击只能对战斗中的对手使用。\n");

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中无剑，如何谈得上「剑指相配」？\n");

        if( query_temp("secondary_weapon", me) )
                return notify_fail("你正握着短兵，没有手能空出来「剑指相配」了。\n");

        if( query_temp("th_jianmang", me) )
                return notify_fail("你正凝神使动「剑芒」，不能再分心了！\n");

        if( query_temp("th_jianzhi", me) )
                return notify_fail("你正在运用剑指相配的攻势！\n");

        if( me->query_skill("yuxiao-jianfa",1) < 120 )
                return notify_fail("你的玉箫剑法修为未到，不能剑指相配攻敌！\n");

        if( me->query_skill("tanzhi-shentong",1) < 120 )
                return notify_fail("你的弹指神通修为未到，不能剑指相配攻敌！\n");

        if( me->query_skill("bibo-shengong", 1) < 120 )
                return notify_fail("你的碧涛玄功修为不足，强使剑指相配，徒然分散功力！\n");

        if( me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你并没有使用玉箫剑法！\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所运使的内功无法与剑指相配之心法协调！\n");

        if( me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你所施展的指法并非弹指神通！\n");

        if( me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你还没有准备好施展弹指神通！\n");

        if( query("max_neili", me) <= 1200 )
                return notify_fail("你的内力修为不足，倘若施展剑指相配，反而会有力分则弱的凶险！\n");

        if( query("neili", me) <= 400 )
                return notify_fail("你的内力不足，不足以施展剑指相配！\n");

        if( query("jingli", me) <= 400 )
                return notify_fail("你的精力不足，不足以施展剑指相配！\n");

        if( BUFF_D->check_buff(me, "yxjf_jianzhi") )
                return notify_fail("你正在使用剑指相配中！\n");
                
        damage = me->query_skill("yuxiao-jianfa",1) + me->query_skill("tanzhi-shentong",1);
        damage /= 3;
        sword = (me->query_skill("sword") + me->query_skill("finger") );
        addn("neili", -250, me);
        addn("jingli", -100, me);

        //命中率增加
        data = ([
                "defense": damage,
                "attack" : damage,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "yxjf_jianzhi",
                "attr"  : "bless",
                "name"  : "玉箫剑法·剑指相配",
                "time"  : skill/2,
                "buff_data": data,      
                "buff_msg" : "",
                "disa_msg" : "你的玉箫剑法运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        message_combatd(HIG"$N手中"+weapon->name()+HIG"一腾，飞舞来去，潇洒自如，著著都是攻势，一招不待$n化解开去，第二招第三招已连绵而至！\n"NOR, me,target);

        //第二剑稍快
        addn_temp("apply/attack", damage/3, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        addn_temp("apply/attack", -damage/3, me);

        if(me->is_fighting(target) ){
                message_combatd(HIG"$N剑势未止，左手指力已蕴劲弹出，点向$n各路穴道，"+HIW"「玉箫剑法」"NOR+HIG"与"+HIW"「弹指神通」"NOR+HIG"互相为用，越发精微奥妙，变化无穷！\n"NOR, me,target);

                weapon->unequip();
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                weapon->wield();
        }
        set_temp("th_jianzhi", sword/10, me);

        if( query_temp("th_jianzhi", me)>70 )
                set_temp("th_jianzhi", 70, me);

        call_out("checking", 1, me, weapon,speed,damage);

        return 1;
}

void checking(object me, object weapon,int speed, int damage)
{
        if (!me) return;
        if( !living(me) || me->is_ghost() )
        {
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd("\n$N见战局已毕，便即收起了剑指相配的功法。\n", me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }

        else if( environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_combatd("\n$N手中兵器已失，当下收回了剑指相配的攻势。\n"NOR, me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jianfa"
        || me->query_skill_mapped("finger") != "tanzhi-shentong"
        || me->query_skill_prepared("finger") != "tanzhi-shentong" )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$N一挥"+weapon->name()+HIG"，骤然变换招数，不再是玉箫剑法与弹指神通的搭配进击！\n"NOR, me);
                return ;
        }
        else if( query("neili", me)<500 || query("jingli", me)<500 )
        {
                tell_object(me, HIW "\n你惊觉内息渐弱，再如此快攻恐怕後继乏力，当下不动声色，暗暗收了左手「弹指神通」攻势。\n" NOR);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( query_temp("th_jianzhi", me) <= 20 )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$N一挥"+weapon->name()+HIG"，左手食中二指捏起剑诀，心无旁骛地使动「玉箫剑法」！\n"NOR, me);
                return;
        }

        else call_out("checking", 1, me, weapon,speed,damage);
        return;
}

void remove_effect(object me, object weapon, int speed, int damage)
{
        if (!me) return;
        BUFF_D->debuff(me, "yxjf_jianzhi", 1);
        delete_temp("th_jianzhi", me);
}
