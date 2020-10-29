// taiji-jian.c 太极剑法

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int taiji(object me, object victim, object weapon, int damage);
int raozhi(object me, object victim, object weapon, int damage);

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
         "$p左手剑诀斜引，$W横过，画了个半圈，平搭在$P$w之上，劲力传出，$w登时一沉。\n",
         "$p$W交左手，在身前划了两个圆圈，$P见$p剑劲连绵，护住全身，竟无半分空隙。\n",
         "$p剑招未曾使老，已然圈转。突然之间，$P眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已。$P眼睛一花，只好回招。\n",
         "$p当下凝神专志，将一套太极剑法使得圆转如意，严密异常的守住门户。\n",
         "$p以太极剑中「云麾三舞」三式解开。$P见$p化解时举重若轻，深得内家剑术三昧，不待$p回手，跳开一步。\n"
});
string *taiji_msg = ({
         "$N当下左足踏上，剑交左手，一招「三环套月」，虚虚实实，以左手剑攻敌，剑尖上光芒闪烁，嗤嗤嗤的发出轻微响声",
         "$N剑法吞吐开合、阴阳动静，将太极剑法中最精要之处都发挥了出来，功劲一加运开，绵绵不绝",
         "$N左手$w缓缓向前划出，成一弧形。$n只觉一股森森寒气，直逼过来",
         "$N右手捏著剑诀，左手$w不住抖动，突然平刺，剑尖急颤，看不出攻向何处。$P这一招中笼罩了$n上盘七大要穴",
         "$N剑招未曾使老，已然圈转。突然之间，$n眼前出现了几个白色光圈，大圈小圈，正圈斜圈，闪烁不已",
         "$N剑上所幻的光圈越来越多，过不多时，$P全身已隐在无数光圈之中，光圈一个未消，另一个再生。\n$w虽使得极快，却听不到丝毫金刃劈风之声，足见剑劲之柔韧已达於化境",
         "$n只觉似有千百柄$w护住了$N全身。$N纯采守势，端的是绝无破绽。\n可是这座剑锋所组成的堡垒却能移动，千百个光圈犹如浪潮一般，缓缓涌来",
         "$N并非一招一招的相攻，而是以数十招剑法混成的守势，同时化为攻势，使$n无法抵御"
});
mapping *action = ({
([      "action" : "$N虚步提腰，一招"+(order[random(13)])+"「蜻蜓点水」"NOR"，手中$w轻轻颤动，一剑剑点向$n的$l",
        "lvl" : 0,
        "skill_name" : "蜻蜓点水"
]),
([      "action" : "$N向前跨上一步，左手剑诀，右手$w使出一式"+(order[random(13)])+"「指南针」"NOR"直刺$n的$l",
        "lvl" : 4,
        "skill_name" : "指南针"
]),
([      "action" : "$N身形往右一挫，左手剑诀，右手$w使出一式"+(order[random(13)])+"「大魁星」"NOR"刺向$n的$l",
        "lvl" : 9,
        "skill_name" : "大魁星"
]),
([      "action" : "$N双膝下沉，右手$w使出一式"+(order[random(13)])+"「探海式」"NOR"，由下而上疾刺$n的$l",
        "lvl" : 14,
        "skill_name" : "探海式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「燕子掠波」"NOR"，$w自上而下划出一个大弧，平平地向$n的$l挥
去",
        "lvl" : 19,
        "skill_name" : "燕子掠波"
]),
([      "action" : "$N上身往左侧一拧，一招"+(order[random(13)])+"「乌龙摆尾」"NOR"，右手$w反手向$n的$l挥去",
        "lvl" : 24,
        "skill_name" : "乌龙摆尾"
]),
([      "action" : "$N一招"+(order[random(13)])+"「右拦扫」"NOR"，一招"+(order[random(13)])+"「左拦扫」"NOR"，剑锋平指，一气呵成横扫$n的
$l",
        "lvl" : 29,
        "skill_name" : "右拦扫左拦扫"
]),
([      "action" : "$N左腿提膝，手中$w斜指，一招"+(order[random(13)])+"「宿鸟投林」"NOR"刺向$n的$l",
        "lvl" : 34,
        "skill_name" : "宿鸟投林"
]),
([      "action" : "$N一招"+(order[random(13)])+"「青龙出水」"NOR"，$w自下而上划出一个大弧，平平地挥向$n的$l",
        "lvl" : 39,
        "skill_name" : "青龙出水"
]),
([      "action" : "$N使出"+(order[random(13)])+"「三环套月」"NOR"，$w划出三个圆圈，剑锋直出，绵绵不断划向$n
的$l",
        "lvl" : 44,
        "skill_name" : "三环套月"
]),
([      "action" : "$N一招"+(order[random(13)])+"「风卷荷叶」"NOR"，$w轻灵地划出几个圆弧，迅速地向$n的$l挥去",
        "lvl" : 49,
        "skill_name" : "风卷荷叶"
]),
([      "action" : "$N一招"+(order[random(13)])+"「虎抱头」"NOR"，$w划出一个左低右高的大弧，斜斜地斩向$n的$l",
        "lvl" : 54,
        "skill_name" : "虎抱头"
]),
([      "action" : "$N使出"+(order[random(13)])+"「狮子摇头」"NOR"，$w由右向左划出一个大８字，将$n圈在其中",
        "lvl" : 59,
        "skill_name" : "狮子摇头"
]),
([      "action" : "$N左脚踏实，右脚虚点，一招"+(order[random(13)])+"「仙人指路」"NOR"，右手$w带着一团剑花，
逼向$n的$l",
        "lvl" : 64,
        "skill_name" : "仙人指路"
]),
([      "action" : "$N轻轻跃起，一招"+(order[random(13)])+"「野马跳涧」"NOR"，$w在半空中化为一圈银芒，落向$n
的$l",
        "lvl" : 69,
        "skill_name" : "野马跳涧"
]),
([      "action" : "$N两腿前箭后弓，一招"+(order[random(13)])+"「射雁式」"NOR"，右手$w直刺$n的$l",
        "lvl" : 74,
        "skill_name" : "射雁式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「小魁星」"NOR"，身形往左一挫，左手剑诀，右手$w平平地向$n的
$l挥去",
        "lvl" : 79,
        "skill_name" : "小魁星"
]),
([      "action" : "$N猱身扑上，一招"+(order[random(13)])+"「白猿献果」"NOR"，手中$w斜斜地向$n的$l挥去",
        "lvl" : 84,
        "skill_name" : "白猿献果"
]),
([      "action" : "$N一招"+(order[random(13)])+"「迎风掸尘」"NOR"，$w看似随意地一挥，$n却陡觉一股劲气迎面袭
来。",
        "lvl" : 89,
        "skill_name" : "迎风掸尘"
]),
([      "action" : "$N一招"+(order[random(13)])+"「顺水推舟」"NOR"，$w自上而下划出一个大弧，平平地向$n的$l挥
去。",
        "lvl" : 94,
        "skill_name" : "顺水推舟"
]),
([      "action" : "$N一招"+(order[random(13)])+"「流星赶月」"NOR"，$w疾刺$n的$l",
        "lvl" : 99,
        "skill_name" : "流星赶月"
]),
([      "action" : "$N突然盘蹲下身来，一招"+(order[random(13)])+"「海底捞月」"NOR"，$w自下而上地向$n的$l挥去",
        "lvl" : 104,
        "skill_name" : "海底捞月"
]),
([      "action" : "$N一招"+(order[random(13)])+"「挑帘式」"NOR"，$w自下而上徐徐划出一个大弧，平平地向$n的$l
挥去",
        "lvl" : 109,
        "skill_name" : "挑帘式"
]),
([      "action" : "$N一招"+(order[random(13)])+"「黄蜂入洞」"NOR"，$w自上而下划出一个大弧，平平地向$n的$l挥
去",
        "lvl" : 114,
        "skill_name" : "黄蜂入洞"
]),
([      "action" : "$N一招"+(order[random(13)])+"「大鹏展翅」"NOR"，身形跃起，右手$w刺向$n的$l",
        "lvl" : 119,
        "skill_name" : "大鹏展翅"
]),
([      "action" : "$N一招"+(order[random(13)])+"「车轮剑」"NOR"，$w化作一片银盘，平平地向$n的$l卷去",
        "lvl" : 124,
        "skill_name" : "车轮剑"
]),
([      "action" : "$N左脚轻点地面，身形往前一扑，一招"+(order[random(13)])+"「天马行空」"NOR"，$w向$n的$l挥
去",
        "lvl" : 129,
        "skill_name" : "天马行空"
]),
([      "action" : "$N一招"+(order[random(13)])+"「风扫梅花」"NOR"，身体跃在半空，手中$w扫向$n的$l",
        "lvl" : 90,
        "skill_name" : "风扫梅花"
]),
([      "action" : "$N一招"+(order[random(13)])+"「却步抽剑」"NOR"，左脚跃步落地，$w回抽，反手勾向$n的$l",
        "lvl" : 139,
        "skill_name" : "却步抽剑"
]),
([      "action" : "$N右腿半屈般蹲，一招"+(order[random(13)])+"「如封似闭」"NOR"，剑尖虚指，转身撩向$n的$l",
        "lvl" : 144,
        "skill_name" : "如封似闭"
]),
([      "action" : "$N回身拧腰，右手虚抱，一招"+(order[random(13)])+"「拨云瞻日」"NOR"，$w中宫直进，刺向$n的$l",
        "lvl" : 149,
        "skill_name" : "拨云瞻日"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("int", me)<26 )
                return notify_fail("你先天悟性太差，难以领会太极剑的要诣。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("taiji-quan", 1) < 100)
                return notify_fail("你的太极拳火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法水平有限，无法修炼太极剑法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("taiji-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的太级剑法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的体力不够练太极剑法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的内力不够练太极剑法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -64, me);
        return 1;
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -55;
        int d_e2 = -45;
        int p_e1 = -50;
        int p_e2 = -45;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 60;
        int m_e2 = 150;
        int i, lvl, seq, ttl = sizeof(action), busy_time;
        object victim;
        string *limbs, limb, target, msg;

        lvl = (int) me->query_skill("taiji-jian", 1);
        busy_time = lvl/20;
        if( objectp(victim = me->select_opponent()) )
        {
                limbs=query("limbs", victim);
                limb = limbs[random(sizeof(limbs))];
                target = victim->name();
        }

//////// 附加双击 yun taiji后的双击/////
        if( query_temp("double_attack", me) )
        {
                return ([
                        "action" : HIW"突然之间，$N剑交右手，寒光一闪，向$n$l划出，这一下快速无伦"NOR,
                        "force"  : 350+random(100),
                        "dodge"  : -80,
                        "parry"  : -80,
                        "damage" : 200+random(50),
                        "damage_type" : "割伤" ]);
        }
////////太极剑 chan 好像没用/////
        if( query_temp("chan/"+target, me) )
        {
                victim->start_busy(2);
                addn("neili", -20, me);
                addn_temp("chan/"+target, 1, me);

                if( query_temp("chan/"+target, me) >= busy_time )
                        delete_temp("chan/"+target, me);
        }
//////// perform raozhi后的双（三）击 ////
        if( random(query_temp("wudang/raozhi", me))>50 ||
                query_temp("raozhi_attack", me) )
        {
                switch(query_temp("raozhi_attack", me) )
                {
                        case 1: msg =HIY"不料铮的一声轻响，$w"+HIY+"反弹过来，直刺向$p$l"NOR;
                                break;
                        case 2: msg =HIC"谁知$N於$w"HIC"上连催两重劲，剑弯成弧，又是一弯，便如长蛇之游，奇诡不可设想"NOR;
                                break;
                        default: msg = HIW"突然间$N$w"HIW"破空，疾刺$n"+limb+"，剑到中途，剑尖微颤，竟然弯了过去，斜刺$p$l"NOR;
                                break;
                }
                addn_temp("wudang/raozhi", -1, me);
                addn("neili", -25, me);
//              if( wizardp(me) )
//                      tell_object(me, sprintf("\nap: %d", COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK)));
                return ([
                        "action": msg,
                        "dodge" : -100,
                        "parry" : -100,
                        "force" : 380+random(120),
                        "damage": 220+random(80),
                        "damage_type":"刺伤",
                        "post_action": (: raozhi :)
                ]);
        }
///////////yun taiji后的普通招////////////
        if( query_temp("taiji", me) && query("neili", me)>100 )
        {
                addn_temp("taiji_fight", 1, me);
                addn("neili", -10, me);
                return ([
                        "action": taiji_msg[random(sizeof(taiji_msg))],
                        "force" : 420+random(120),
                        "dodge" : -100-random(50),
                        "parry" : -100-random(50),
                        "damage": 220+random(80),
                        "damage_type" : random(2)?"刺伤":"割伤",
                        "post_action" : (: taiji :) ]);
        }
/////////// 都没有的话/////////
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割伤" : "刺伤",
        ]);
}
int taiji(object me, object victim, object weapon, int damage)
{
        int n = random(2);

        if( damage == RESULT_DODGE )
        {
                if( n == 0 && me->query_skill_mapped("unarmed") == "taiji-quan"
                && me->query_skill_prepared("unarmed") == "taiji-quan" )
                {
                        set_temp("double_attack", 1, me);
                        weapon->unequip();
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        weapon->wield();
                }
                else
                {
                        set_temp("double_attack", 1, me);
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        message_combatd("\n$N又是剑交左手，在身前划了两个圆圈。$n见$P剑劲连绵，护住全身，竟无半分空隙。\n"NOR,me,victim);
                }
                delete_temp("double_attack", me);
                return 1;
        }
        else if( damage <= 0 )
        {
                message_combatd("$p但觉$P剑上有股绵劲，震得自己手臂隐隐发麻。\n", me, victim);
//              if( !victim->is_busy() )
//              victim->start_busy(1+random((int)(me->query_skill("force")/150)));
                addn("neili", -(me->query_skill("force")/10), victim);
        }
        return 1;
}
int raozhi(object me, object victim, object weapon, int damage)
{
        int level = (int)me->query_skill("taiji-jian", 1)/2;
        string ductile;

        if( !objectp(weapon) ) return 1;
        ductile=query("id", weapon);
        addn_temp("raozhi_attack", 1, me);

        if( damage == RESULT_DODGE && query_temp("raozhi_attack", me)<3 )
        {
                addn_temp("apply/attack", level, me);

                if( query_temp("raozhi_attack", me) == 1 ||
                        ( (ductile == "bailong jian" || ductile == "ruanjian"
                                 || ductile == "shuixinjian") && query("neili", me)>500) )
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);
                else delete_temp("raozhi_attack", me);

                addn_temp("apply/attack", -level, me);
                return 1;
        }
        else delete_temp("raozhi_attack", me);
        return 1;
}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("taiji-jian", 1) < 100 ||
            !(m_weapon=query_temp("weapon", me)) ||
            !living(me) || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("taiji-jian", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "一抖手中的" + m_weapon->name() +
                                            HIC "，划出了一个圆圈，竟然让$N" +
                                            HIC "的攻击全然落空。\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "手中" + m_weapon->name() + HIC
                                            "轻挑，正指向$N" HIC "攻势中的破绽。\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "晃动手中的" + m_weapon->name() +
                                            HIC "，不住的变幻剑势，让$N"
                                            HIC "完全无法捕捉到力道。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() +
                                 HIY "，划出了一个圆圈，$N"
                                 HIY "理也不理，当即挥招直入，进袭$n"
                                 HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY "轻挑，"
                                 HIY "正指向$N" HIY "攻势中的破绽，可是$N"
                                 HIY "身形一变，破绽立刻不成为破绽。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "晃动手中的" + m_weapon->name() +
                                 HIY "，不住的变幻剑势，然而$N"
                                 HIY "算理深厚，精演天数，丝毫不受$n"
                                 HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("taiji-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"taiji-jian/" + action;
}
int help(object me)
{
        write(HIC"\n太极剑法："NOR"\n");
        write(@HELP

    和太极拳武学原理相同，亦是张三丰祖师晚年时闭关悟得，剑
势圆融，并无固定招式，讲究以无招胜有招，招名乃是后人所加。
太极剑法有了一定修为后，需相当的太极拳基础，方可上进。

        学习要求：
                太极拳20级
                太极神功20级
                内力100
HELP
        );
        return 1;
}
