// 真武剑阵 zhenwu-array.c
// Modified by haiyan

#include <ansi.h>

#define MAX_ZHEN 8 
#define MIN_ZHEN 5 

inherit F_CLEAN_UP;
inherit F_SSERVER;

int valid_enable(string usage) { return usage=="array"; }

string *style = ({ 
HIM "$N手持$w，前进中一阵急骤，手中$w猛然刺向$n！\n"NOR,
HIM "$N着地一滚，手中$w上挑，已刺向$n小腹！\n"NOR, 
HIM "$N反手握住$w，化出一道白弧，剑尖直指$n眉心！\n"NOR,
HIM "$N向前一纵，略退半步，突然一个急进，手中$w向$n猛扑过去！\n"NOR,
HIM "$N与$w合而为一，飞身而起，挺身刺向$n的两处要害！\n"NOR, 
HIM "$N左手捻一个剑诀，手中$w忽而向下，刺向$n下盘！\n"NOR, 
HIM "$N纵身一跃，手中$w叮叮作响，已向$n连刺三剑！\n"NOR, 
HIM "$N手中$w疾挥，划出道道剑光，身形一转，迅速刺向$n！\n"NOR
});

string *zhen = ({ 
HIC"\n真武剑阵缓缓转动，将$n围在核心，一股强大的绵力压向$n。\n\n"NOR, 
HIC"\n真武剑阵忽进忽退，$n凝神观阵，看不出丝毫破绽，只得紧守门户，不敢妄自出招。\n\n"NOR, 
HIC"\n$N一声长啸，真武剑阵迅速移位，众人步法精妙，紧随$n进退。\n\n"NOR, 
HIC"\n真武剑阵越缩越小，攻势连绵不绝，无形剑气象浪潮一般圈向$n。\n\n"NOR 
});

int valid_learn(object me) 
{ 
        if ((int)me->query_skill("wudang-xinfa", 1) < 100)
                return notify_fail("你的武当心法火候不够，难以领会「真武剑阵」。\n"); 

        if ((int)me->query_skill("taoism", 1) < 150) 
                return notify_fail("你的道学心法修为不够，无法领悟高深的「真武剑阵」。\n"); 

        if ((int)me->query_skill("sword", 1) < 100) 
                return notify_fail("你的基本剑法火候太浅，对「真武剑阵」的变化不能领会。\n"); 

        if ((int)me->query_skill("array", 1) < (int)me->query_skill("zhenwu-array", 1)) 
                return notify_fail("你的基本阵法水平有限，无法领会更高深的「真武剑阵」。\n"); 

        return 1;
} 

void remove_effect(object me);
void checking(int del_time,object me);

int practice_skill(object me) 
{
      return notify_fail("真武剑阵只能用学(learn)或操演来增加熟练度。\n"); 
}

int form_array(object me)
{
        int i; 
        object *member, weapon; 
        member = me->query_team();

        if( !pointerp(member=me->query_team()) || !me->is_team_leader())
                return notify_fail("只有队伍领袖才可以指挥组阵！\n");

        if( me->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你还没有准备好真武剑阵！\n");

        if( sizeof(member) > MAX_ZHEN )
                return notify_fail("真武剑阵最多只能由八名武当弟子组成。\n");

        if( sizeof(member) < MIN_ZHEN )
                return notify_fail("真武剑阵至少要由五名武当弟子组成。\n");

        if( me->query_skill("zhenwu-array",1) < sizeof(member)*20 ) 
                return notify_fail("你对真武剑阵的精要变化还未完全领悟！\n"); 

        for( i = 0; i < sizeof(member); i++ ) 
        { 
           if (!member[i]) 
                return notify_fail("你的队伍中有人离开，需要重新组合队伍。\n");

           if (environment(member[i]) != environment(me)) 
                return notify_fail("你队伍中的"+member[i]->name()+"不在你身边。\n");

           if( query("family/family_name", member[i]) != "武当派" )
                return notify_fail("你队伍中的"+member[i]->name()+"不是武当派弟子。\n"); 

           if (member[i]->query_skill("zhenwu-array",1) < 80 ) 
                return notify_fail("你队伍中的"+member[i]->name()+"真武剑阵阵法还未入门。\n");

           if( !objectp(weapon=query_temp("weapon", member[i])) || 
                query("skill_type", weapon) != "sword" )
                return notify_fail("你队伍中的"+member[i]->name()+"没有装备剑。\n"); 

           if (member[i]->query_skill("sword",1) < 120 ) 
                return notify_fail("你队伍中"+member[i]->name()+"的基本剑法造诣太低。\n");

           if (member[i]->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("你队伍中的"+member[i]->name()+"未准备好真武剑阵阵法！\n");
        } 

        if( me->is_busy())
               return notify_fail("你现在忙不过来指挥众人组阵! \n");

        if( query_temp("alreading", me) )
               return notify_fail("你的队伍已经组成了「真武剑阵」！\n");

        message_vision( HIY "$N" HIY "一声长啸，手中" + weapon->name() + 
                        HIY "一荡，身形移动，率领众人分四象八卦站定方位，摆出了"
                        HIY "「真武剑阵」阵法！\n\n"
                        HIW "众人挥剑齐呼：真武剑阵 —— 天下第一！\n\n" NOR, me);

        set_temp("alreading", me->query_skill("zhenwu-array",1)/10+10, me);
        call_out("checking", 1, 1, me); 
        return 1;
}

void checking(int del_time,object me)
{
        string msg;
        int num, atac;
        int i, fighting;
        object *member, target, weapon;

        if( !query_temp("alreading", me))return ;

        target=query_temp("offensive_target", me);
        num=query_temp("alreading", me);
        member = me->query_team(); 

        set_temp("alreading",query_temp("alreading",  me)-del_time, me);
        if( wizardp(me) )  tell_object(me,sprintf("<持续时间还剩%d秒>\n",num));
        if( num <= 1 ) 
        {
             message_vision(HIW "$N" HIW "已将自己所掌握的真武剑阵全部变化"
                            HIW "操演完毕，解散了剑阵。\n\n"NOR, me);
             delete_temp("alreading", me);
             return;
        }

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character())
        {
            call_out("checking", 1, 1, me); 
            return;
        }

        for (i = 0; i < sizeof(member); i++ ) 
        {
            if (!member[i]) 
            {
                message_vision(HIW "由于$n" HIW "已离开剑阵，真武剑阵需要重新组合。\n\n" NOR, me, member[i]); 
                remove_effect(me);
                return;
            }

            if(member[i]->is_corpse())
            {
                if ( sizeof(member) < MIN_ZHEN )
                {
                    message_vision(HIW "由于$N" HIW "没能抵挡住$n"
                                   HIW "的致命一击，真武剑阵人数不足，顿出破绽，被$n攻破。\n\n"NOR, member[i], target);
                    remove_effect(me);
                    return;
                }
                else
                    message_vision(HIW "众人看到$N" HIW "惨遭$n"
                                   HIW "毒手，怒从心起，士气大增，当下改变阵形，将$n"
                                   HIW "团团围住。\n\n"NOR, member[i], target);
            }

            if (environment(member[i]) != environment(me)) 
            {
                message_vision(HIW "$n" HIW "见$N" HIW "愈战愈勇，私心顿起，为求自保，悄然逃离现场！\n"
                               HIC "由于$n离开现场，真武剑阵被$N攻破了！\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }

            weapon=query_temp("weapon", member[i]);
            if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
            {
                message_vision(HIW "$N" HIW "见$n" HIW "剑已离手，精神大振，疾向$n连攻数招。\n"
                               HIW "$n" HIW "无奈之下，步步后退，终于偏离了真武剑阵方位！\n"
                               HIC "真武剑阵被$N" HIC "攻破了！！\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }
            atac += (member[i]->query_skill("force",1) +
                     member[i]->query_skill("sword",1)) / 2;
            member[i]->kill_ob(target); 
        }

        atac = atac / sizeof(member);
        if( wizardp(me) )  tell_object(me,sprintf("<增加攻击力%d点>\n",atac));
        fighting = random(sizeof(member)); 
        if (living(member[fighting]))
        {
           if (random(10) > 6)
           {
              msg = zhen[random(sizeof(zhen))]; 
              message_vision(msg, me, target);
           }

           if (random(8) > 5)
           {
               if( query("family/family_name", target) != "武当派" )
                   message_vision(HIY "$N" HIY "大声对$n"
                                  HIY "喝道：“大胆狂徒，我武当派今日替天行道，还不快快受死！”\n"
                                  NOR, member[fighting], target);
           else
                   message_vision(HIY "$N" HIY "对$n"
                                  HIY "喝道：“今日我武当派要清理门户，还不快快受死？”\n"
                                  NOR, member[fighting], target);
           }

           weapon=query_temp("weapon", member[fighting]);
           msg = style[random(sizeof(style))]; 
           msg = replace_string(msg,"$w",weapon->name()); 
           if( objectp(weapon) && query("skill_type", weapon) == "sword" )
           {
               if (!member[fighting]->is_busy())
               {
                   message_combatd(msg, member[fighting], target); 
                   addn_temp("apply/attack", atac, member[fighting]);
                   addn_temp("apply/damage", atac, member[fighting]);
                   COMBAT_D->do_attack(member[fighting], target, weapon, 0);
                   addn_temp("apply/attack", -atac, member[fighting]);
                   addn_temp("apply/damage", -atac, member[fighting]);
                   member[fighting]->start_busy(2);
               }
           }
        }
        call_out("checking", 1, 1, me);
        return;
}

void remove_effect(object me)
{
        if (!me) return;
        delete_temp("alreading", me);
        me->start_busy(1);
}
