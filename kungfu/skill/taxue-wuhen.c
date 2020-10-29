// taxue-wuhen.c 踏雪无痕

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }
int is_pbsk() { return 1; }

string *dodge_msg = ({
"$n一式"YEL"「雁落平沙」"NOR"，变招奇速，右足向前踢出，身子已然腾起，轻轻巧巧地落在一旁。\n",
"$n一式"HIW"「玉龙飞起」"NOR"，纵身高跃，半空中一折一转，已飘身在数丈之外。\n",
"$n一式"HIY"「夏日消融」"NOR"，两足足跟不动，足尖左磨，身子随之右转，卸开了$N这一招。\n",
"$n一式"HIB"「枯松倒挂」"NOR"，只见$n身子后仰，双掌往地下一撑，身子借势倒射而出，$N便已打$n不着。\n",
"$n一式"HIW"「晴雪飞滩」"NOR"，纵高伏低，东奔西闪，身形飘忽不定，$N手无足措，只得回招自守。\n",
"$n一式"HIW"「冰丝带雨」"NOR"，突然反手一招，竟然是两败俱伤的打法，趁$N手忙脚乱安全脱身。\n",
"$n一式"HIM"「寒江钓雪」"NOR"，不招不架，只微微一侧身，$N犹如暴风骤雨般的进攻便即落空。\n",
"$n一式"HIY"「鱼龙潜跃」"NOR"，陡然间身形拔起，直冲云霄，直如鹰隼，几个盘旋，飘飘荡荡落在数丈之外。\n",
"$n一式"HIW"「踏雪无痕」"NOR"，身形急速旋转，几下就划到数丈之外。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的体力太差了，不能练踏雪无痕。\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }
mixed valid_damage(object me, object victim, int damage, object weapon)
{
        int ap, dp/*, level*/;
        object weapon1=query_temp("weapon", me);
        mapping prepare;
        string result, attack_skill;

        if ( victim->query_skill("taxue-wuhen", 1) < 100
        || !living(victim) )
                return;

        dp = COMBAT_D->skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
                dp += COMBAT_D->skill_power(victim, "force", SKILL_USAGE_DEFENSE);

        ap = COMBAT_D->skill_power(me, "dodge", SKILL_USAGE_DEFENSE);
        prepare = me->query_skill_prepare();
        if( !prepare ) prepare = ([]);

        if( objectp(weapon1))attack_skill=query("skill_type", weapon1);
        else switch( sizeof(prepare) )
        {
                case 0: attack_skill = "unarmed"; break;
                case 1: attack_skill = (keys(prepare))[0]; break;
                case 2: attack_skill = (keys(prepare))[query_temp("action_flag", me)]; break;
        }

        ap += COMBAT_D->skill_power(me, attack_skill, SKILL_USAGE_ATTACK);

        ap /= 100;
        dp /= 100;

        if ( random(ap+dp) > ap ) {
                result =  "$n身形一晃闪过一边，手做掷暗器状，$N心头一惊，一时有点手忙脚乱！\n";
                result += "$n见有机可趁，立刻对$N发动攻势！\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
         else if ( random(ap+dp) > ap ) {
                result = HIW "只见$n举重若轻,以极巧妙身法，身影满天飞舞，手做掷暗器状，$N心头一惊，一时有点手忙脚乱！\n" NOR;
                result += "$n捉紧时机，立刻对$N发动攻势！\n" ;
                COMBAT_D->do_attack(victim,me,query_temp("weapon", victim));
                addn("jingli", random(-20), victim);

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+2*dp) > ap ) {
                result = "$n身形一晃闪过一边，已然轻易地避开了$N的攻击。\n" ;

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else if ( random(ap+3*dp) > ap ) {
                result = "$n身形一晃闪过一边，$N只觉得用力处力道全无。\n";

                return ([ "msg" : result, "damage" : -damage ]);
        }
        else
                return;
}

string perform_action_file(string action)
{
        return __DIR__"taxue-wuhen/" + action;
}
