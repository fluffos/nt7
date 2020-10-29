#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "参商剑气" NOR; }

int perform( object me, object target)
{
        int lvl, str, dex, skill;
        string weapon;
        mapping buff, data;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("参商剑气只能对战斗中的对手使用！\n");

        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已经在使用参商剑气了！\n");

        if( objectp(query_temp("weapon", me)) )
                        return notify_fail("参商剑气需要你空手才能施展！\n");

        if( me->query_skill_mapped("finger") != "canhe-zhi" )
                return notify_fail("你所使用的并非参合指，不能施展参商剑气！\n");

        if( me->query_skill_prepared("finger") != "canhe-zhi" )
                return notify_fail("你所备的并非参合指，不能施展参商剑气！\n");

/*
     if( me->query_skill_mapped("force") != "shenyuan-gong" )
                return notify_fail("你所激发的内功并非神元功，施展不出参商剑气！\n");
*/

        if( me->query_skill("force") < 140 )
                return notify_fail("你的内功火候不到，无法施展慕容家传绝学！\n");

        if( me->query_int() < 22 )
                return notify_fail("你的悟性太差，不能施展姑苏慕容家传绝学！\n");

        if( (lvl=me->query_skill("finger")) < 100 )
                return notify_fail("参商剑气需要精深的指力方能奏效！\n");

        if( query("neili", me) <= lvl*3/2 )
                return notify_fail("你的内力不足以使用慕容绝学参商指法！\n");

        if( query("jingli", me)<lvl )
                return notify_fail("你的精力不足以使用慕容绝学参商指法！\n");

        msg = HIM "$N" HIM "口中默念“动静如参商”，心随意转，劲跟力发。只听得内力破空之声呲呲作响！\n"
                        HIM "内力化作一股剑气直奔"+target->name()+ HIM "射去！\n" NOR;
                        
        str = me->query_skill("canhe-zhi",1)*2;
        dex = me->query_skill("beidou-xianzong" ,1)*2;
        skill = (str+dex) / 2;
        
        addn("neili", -lvl, me);
        addn("jingli", -lvl, me);
        
        data = ([
                "str" : str,
                "dex" : dex,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "参合指·参商剑气",
                "time"  : skill/8,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你缓缓收住身形，轻吁一口气，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        me->start_busy(1+random(2)); 
        return 1;
}

