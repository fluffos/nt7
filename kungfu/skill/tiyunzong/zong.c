// This program is a part of NITAN MudLIB
// zong.c

#include <ansi.h>

string name() { return "纵字诀"; }

void remove_effect(object me,int count);

int perform(object me, object target)
{
        mapping buff, data;
        string msg;
        int improve;
        int delta;

        if( (int)me->query_skill("tiyunzong",1) < 120 )
                return notify_fail("你的梯云纵不够娴熟，不会使用「纵字诀」！\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 120 )
                return notify_fail("你的太极神功等级不够，不能使用「纵字诀」！\n");

        if (me->query_skill_mapped("force") != "taiji-shengong")
                return notify_fail("你的内功不对，不能使用「纵字诀」。\n");

        if( (int)me->query_dex() < 28 )
                return notify_fail("你的身法太低，不能使用「纵字诀」！\n");

        if( (int)me->query_skill("dodge",1) < 120 )
                return notify_fail("你的基本轻功太差，身体笨拙，不能使用「纵字诀」！\n");

        if( query("neili", me)<600 )
                return notify_fail("你的内力太少了，无法使用出「纵字诀」！\n");

        if (me->query_skill_mapped("dodge") != "tiyunzong")
                return notify_fail("你现在激发的轻身数使用「纵字诀」绝技。\n");

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你正在使用梯云纵的特殊防御「纵字诀」！\n");

        if( query_temp("zong", me) )
                return notify_fail("你正在使用梯云纵的特殊防御「纵字诀」！\n");

        msg = HIY"$N突然深吸一口气，一抬腿猛的拔高数丈，升势刚尽，双腿连续踢出，" +
                        "身体又上升丈许，才有如大鸟般盘旋落下！\n" NOR;

        improve = (int)me->query_skill("dodge")* 10;
        delta = ABILITY_D->check_ability(me, "dp_power-tyz-zong"); // 门派ab
        if( delta ) improve += improve*delta/100;

        data = ([
                "defense": improve, 
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "梯云纵·纵字诀",
                "time"  : improve/10,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIY"你散去丹田凝聚的内力，混身经脉真气流动，气定神闲，精神弈弈。\n"NOR,
                        
        ]);
        BUFF_D->buffup(buff);

        addn("neili", -(350-me->query_skill("tiyunzong",1)/100), me);
        return 1;
}

/*
void remove_effect(object me, int count)
{
        int improve;
        if( !me ) return;
        if( !intp(improve=query_temp("zong", me)))return ;
        if( !me->is_fighting()
        ||  count < 1)
        {
                BUFF_D->debuff(me, "dodgeup", 1);
  
                delete_temp("zong", me);
                tell_object(me, HIY"你散去丹田凝聚的内力，混身经脉真气流动，气定神闲，精神弈弈。\n"NOR);
                tell_room(environment(me), HIY + me->name()+"全身骨头一阵轻响，散去了混身的功力。\n"NOR,  ({ me }));
                return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}
*/

int help(object me)
{
        write(WHT"\n梯云纵「纵」字诀："NOR"\n");
        write(@HELP
        武当轻功，当世可谓独步武林，天下轻功无出其右，临敌之时使出「纵」字
        诀，可以用来大幅度提升自己的轻功有效等级，增加胜算或逃脱机率。

        要求：  梯云纵等级 120 以上；
                太极神功等级 120 以上；
                基本轻功等级 120 以上；
                内力 600 以上；
                后天身法 28 以上。
HELP
        );
        return 1;
}
