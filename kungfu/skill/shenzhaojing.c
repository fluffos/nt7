// 神照经神功 shenzhaojing.c

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) 
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N倏然跃近，击出一拳，这一拳无声无影，去势快极，向$n的胸口打去",
        "dodge"  : 81,
        "force"  : 323,
        "attack" : 119,
        "parry"  : 94,
        "damage" : 68,
        "lvl"    : 0,
        "damage_type": "内伤"
]),
([      "action" : "$N丝毫不动声色，右掌平伸，左掌运起神照经神功的劲力，呼的一声拍向$n",
        "dodge"  : 73,
        "force"  : 362,
        "attack" : 138,
        "parry"  : 51,
        "damage" : 73,
        "lvl"    : 200,
        "damage_type": "内伤"
]),
([      "action" : "$N身形微微一展，已然游走至$n跟前，陡然间双掌齐施，向$n猛拍而去",
        "dodge"  : 78,
        "force"  : 389,
        "attack" : 152,
        "parry"  : 53,
        "damage" : 87,
        "lvl"    : 220,
        "damage_type": "内伤"
]),
([      "action" : "$N退后一步，双掌回收，凌空划出一个圆圈，顿时一股澎湃的气劲直涌$n而出",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 163,
        "parry"  : 67,
        "damage" : 93,
        "lvl"    : 250,
        "damage_type": "内伤"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("shenzhaojing", 1);

        if(lvl >= 180)
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";

}

int valid_learn(object me)
{
        if( query("str", me)<32 )
                return notify_fail("你先天膂力孱弱，无法修炼神照经神功。\n");

        if( query("con", me)<32 )
                return notify_fail("你先天根骨孱弱，无法修炼神照经神功。\n");

        if( query("gender", me) == "无性" && query("shenzhaojing", me)>29 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的神照经神功。\n");

        if( query("family/family_name", me) != "密宗" )
                return notify_fail("神照经神功乃是血刀门的不传神功，你无法理解其中精髓。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本内功火候不足，不能学神照经神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳脚火候不足，不能学神照经神功。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，不能学神照经神功。\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本内功水平不够，难以锻炼更深厚的神照经神功。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本拳脚水平不够，难以锻炼更深厚的神照经神功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -30;
        int p_e2 = 10;
        int f_e1 = 140;
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenzhaojing", 1);
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
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);

        if (damage_bonus < 160
           || lvl < 180
           || query("neili", me)<300
           || query_temp("weapon", me )
           || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "shenzhaojing"
           || me->query_skill_mapped("unarmed") != "shenzhaojing"
           || me->query_skill_prepared("unarmed") != "shenzhaojing")
                return 0;

        // 神照经神功所具有的既添设额外伤害又使对手中
        // 毒的max_hit 在所有武功中是绝无仅有的，但是
        // 它出现的几率以及伤害值又及毒性伤害相对于其
        // 他武功大大减弱。
        if (damage_bonus > victim->query_con()/10)
        {
                victim->receive_wound("qi", damage_bonus, me);
                victim->affect_by("shenzhao",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 100 + random(lvl / 10) ]));
                return HIR "$n" HIR "一声惨嚎，全身骨骼格格格格爆声不"
                       "绝，肋骨、臂骨、腿骨同时断折。\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("神照经神功只能用学(learn)的来增加熟练度。\n");
}

int difficult_level()
{
        return 400;
}

string perform_action_file(string action)
{
        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}


int help(object me)
{
        write(HIC"\n神照经："NOR"\n");
        write(@HELP

    丁典是荆门人，出生于武林世家。父母双亡，家财不少，却不
想结亲，只是勤于练武，结交江湖上的朋友。
    某次他乘船从四川下来，出了三峡后，船泊在三斗坪。晚上，
在船中听得岸上有打斗的声音。从窗中向外张望。那晚月光明亮，
看得清清楚楚，是三个人在围攻一个老者。一个是五云手万震山。
另一个是陆地神龙言达平。第三个人使一口长剑，身手甚是矫捷，
那是铁锁横江戚长发。老者便是铁骨墨萼梅念笙。他们的师父。梅
念笙受伤在先，抵敌不住三个徒弟的毒招，跳江而逃。
    丁典身边带得有金创药，救起梅念笙后，便替他治伤。可是他
背上那一剑刺得好深，穿通了肺，这伤是治不好的了。这么治了三
天，梅念笙从怀中取出一个油纸包来交给丁典，道：“我在这世上
的亲人，就这么三个徒儿。他们想夺我一部剑谱，可是没有剑诀，
那又有什么用？连城剑法虽然神奇，又怎及得上神照经了？这部神
照经，我送了给你，好好地练罢，此经若然练成，威力奇大，千万
不可误传匪人。”神照经，就是这样来的。

        学习要求：
                凭机缘向丁典学习
HELP
        );
        return 1;
}
