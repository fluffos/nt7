// dragon-strike.c 降龙十八掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

//string main_skill() { return "yinyang-shiertian"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N双掌平平提到胸前，神色沉重的缓缓施出"+(order[random(13)])+"「亢龙有悔」"NOR"推向$n的$l",
          "lvl"        : 10,
          "skill_name" : "亢龙有悔",
]),
([        "action" : "$N突然身形飞起，双掌居高临下一招"+(order[random(13)])+"「飞龙在天」"NOR"拍向$n的$l",
          "lvl"        : 20,
          "skill_name" : "飞龙在天",
]),
([        "action" : "$N右掌一招"+(order[random(13)])+"「见龙在田」"NOR"，迅捷无比地劈向$n的$l",
          "lvl"        : 30,
          "skill_name" : "见龙在田",
]),
([        "action" : "$N双掌施出一招"+(order[random(13)])+"「鸿渐于陆」"NOR"，隐隐带着风声拍向$n的$l",
          "lvl"        : 40,
          "skill_name" : "鸿渐于陆",
]),
([        "action" : "$N左掌聚成拳状，右掌一招"+(order[random(13)])+"「潜龙勿用」"NOR"缓缓推向$n的$l",
          "lvl"        : 50,
          "skill_name" : "潜龙勿用",
]),
([        "action" : "$N施出一招"+(order[random(13)])+"「利涉大川」"NOR"，右掌插腰，左掌劈向$n的$l",
          "lvl"        : 60,
          "skill_name" : "利涉大川",
]),
([        "action" : "$N使出"+(order[random(13)])+"「突如其来」"NOR"，右掌从不可能的角度向$n的$l推出",
          "lvl"        : 70,
          "skill_name" : "突如其来",
]),
([        "action" : "$N大吼一声，双掌使出"+(order[random(13)])+"「震惊百里」"NOR"，不顾一切般击向$n",
          "lvl"        : 80,
          "skill_name" : "震惊百里",
]),
([        "action" : "$N使出"+(order[random(13)])+"「或跃在渊」"NOR"，向$n的$l连拍数掌",
          "lvl"        : 90,
          "skill_name" : "或跃在渊",
]),
([        "action" : "$N身形滑动，双掌使一招"+(order[random(13)])+"「双龙取水」"NOR"一前一后按向$n的$l",
          "lvl"        : 100,
          "skill_name" : "双龙取水",
]),
([        "action" : "$N使出"+(order[random(13)])+"「鱼跃于渊」"NOR"，身形飞起，双掌并在一起向$n的$l劈下",
          "lvl"        : 110,
          "skill_name" : "鱼跃于渊",
]),
([        "action" : "$N双掌立起，使出"+(order[random(13)])+"「时乘六龙」"NOR"向$n连砍六下",
          "lvl"        : 120,
          "skill_name" : "时乘六龙",
]),
([        "action" : "$N使出"+(order[random(13)])+"「密云不雨」"NOR"，左掌封住$n的退路，右掌斜斜地劈向$l",
          "lvl"        : 130,
          "skill_name" : "密云不雨",
]),
([        "action" : "$N使出"+(order[random(13)])+"「损则有孚」"NOR"，双掌软绵绵地拍向$n的$l",
          "lvl"        : 140,
          "skill_name" : "损则有孚",
]),
([        "action" : "$N脚下一转，突然欺到$n身前，一招"+(order[random(13)])+"「龙战于野」"NOR"拍向$n的$l",
          "lvl"        : 150,
          "skill_name" : "龙战于野",
]),
([        "action" : "$N门户大开，一招"+(order[random(13)])+"「履霜冰至」"NOR"向$n的$l劈去",
          "lvl"        : 160,
          "skill_name" : "履霜冰至",
]),
([        "action" : "$N使出"+(order[random(13)])+"「羝羊触蕃」"NOR"，双掌由下往上击向$n的$l",
          "lvl"        : 170,
          "skill_name" : "羝羊触蕃",
]),
([        "action" : "$N左掌护胸，右掌使一招"+(order[random(13)])+"「神龙摆尾」"NOR"上下晃动着击向$n的$l",
          "lvl"        : 180,
          "skill_name" : "神龙摆尾",
]),
});

// string main_skill() { return "dragon-strike"; }

mapping sub_skills = ([
       "kanglong-youhui"  : 80,        // 1
       "feilong-zaitian"  : 80,        // 2
       "jianlong-zaitian" : 80,        // 3
       "hongjian-yulu"    : 80,        // 4
       "qianlong-wuyong"  : 80,        // 5
       "lishe-dachuan"    : 80,        // 6
       "turu-qilai"       : 80,        // 7
       "zhenjing-baili"   : 80,        // 8
       "huoyue-zaiyuan"   : 80,        // 9
       "shuanglong-qushui": 80,        // 10
       "yuyue-yuyuan"     : 80,        // 11
       "shicheng-liulong" : 80,        // 12
       "miyun-buyu"       : 80,        // 13
       "sunze-youfu"      : 80,        // 14
       "longzhan-yuye"    : 80,        // 15
       "lvshuang-bingzhi" : 80,        // 16
       "diyang-chufan"    : 80,        // 17
       "shenlong-baiwei"  : 80,        // 18
]);

int get_ready(object me)
{
       return 1;
}

int get_finish(object me)
{
       if( query("str", me)<31 || me->query_str()<45 )
       {
               tell_object(me, "你演练完毕，手臂又酸又软，几乎抬不起来。\n");
               return 0;
       }

       if( query("con", me)<24 || me->query_con()<37 )
       {
               tell_object(me, "你演练完毕，就觉得眼前金星乱冒，太阳穴突突的跳。\n");
               return 0;
       }

       if ((int)me->query_skill("force") < 150)
       {
               tell_object(me, "你演练完毕，几乎虚脱，自己的内功水平看来还有待提高。\n");
               return 0;
       }

       if( query("max_neili", me)<1500 )
       {
               tell_object(me, "你演练完毕，丹田提不起半点力来，看来应该继续锻炼内力。\n");
               return 0;
       }

       if (random(10) < 5)
       {
               tell_object(me, "你对十八掌的奥妙颇有领悟，或许再演练一次就能够融会贯通。\n");
               return 0;
       }

       tell_object(me, HIY "你一气呵成，将十八掌从头到尾演练了一变，心中顿悟，通\n"
                           "晓了降龙十八掌的奥妙精髓，融会贯通了掌法的精微之处，\n"
                           "再也非拆开使用那么那么简单。\n" NOR);
       return 1;
}

mapping query_sub_skills()
{
       return sub_skills;
}

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
       if( query("str", me)<31 )
               return notify_fail("就你这身子骨还练降龙十八掌？小心弄折了胳膊。\n");

       if( query("con", me)<24 )
               return notify_fail("算了吧，你先天根骨不好，别强学了。\n");

       if ((int)me->query_skill("force") < 150)
               return notify_fail("你的内功火候不够，无法学习降龙十八掌。\n");

       if( query("max_neili", me)<1500 )
               return notify_fail("你的内力这么差，怎能融会贯通降龙十八掌？\n");

       if ((int)me->query_skill("strike", 1) < 30)
               return notify_fail("你的基本掌法火候不够，无法学习降龙十八掌。\n");

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1))
               return notify_fail("你的基本掌法水平有限，无法领会更高深的降龙十八掌。\n");

       return 1;
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
//      mapping a_action;
        int level, tmp;
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -20;
        int p_e2 = 10;
        int f_e1 = 520;
        int f_e2 = 640;
        int /*i,*/ seq, ttl = sizeof(action);

        level = (int)me->query_skill("dragon-strike", 1);
        if( query_temp("xlz/hanglong", me) )
        {
                tmp = 4 + random(15);
                delete_temp("xlz/hanglong", me);
                return ([
                        "action": HIY "\n$N叫道：「看招！」左腿微屈，右掌划了个圆圈，平推出去，正是降龙十八掌中的「亢龙有悔」。\n" +
                                  "初推出去看似轻描淡写，但一遇阻力，刹时之间连加" + chinese_number(tmp) + "道後劲，一道强似一道，\n" +
                                  "重重叠叠，直至无坚不摧，无强不破！" NOR,
                        "dodge" : -140,
                        "parry" : -140,
                        "attack": 200,
                        "force" : 500 + 40 * tmp,
                        "damage": 100 + 20 * tmp,
                        "damage_type": random(2)?"内伤":"瘀伤"
                ]);
        }

        seq = random(ttl);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}

// int double_attack() { return 1; }

int practice_skill(object me)
{
//      int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练降龙十八掌必须空手。\n");

        if( query("qi", me)<110 )
                return notify_fail("你的体力太低了。\n");

        // cost = me->query_skill("dragon-strike", 1) / 5 + 90;
        if( query("neili", me)<110 )
                return notify_fail("你的内力不够练降龙十八掌。\n");

        me->receive_damage("qi", 100);
        addn("neili", -100, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        string msg;
        int lvl;

        lvl = me->query_skill("dragon-strike", 1);

        if (damage < 50 || lvl < 150) return;

        if (random(10) < 2)
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIY "$N" HIY "一掌既出，身子抢前，又是一招「亢龙有悔」，"
                                     "後掌推前掌，双掌力道并在一起，排山倒海的压将过来。\n"
                                     HIR "$n" HIR "那曾见过这样霸道的掌力，顿时身受重创，哇的一声，吐出一口鲜血！\n"
                                     NOR ]);
        }
        else
        {
                victim->receive_wound("qi", damage, me);
                msg = random(2) ? HIR "$n" HIR "一声惨叫，胸前「咔嚓咔嚓」几声脆"
                                  "响，口中鲜血狂喷。\n" NOR :
                                  HIR "只听$n" HIR "前胸「咔嚓」一声脆响，竟像是"
                                  "肋骨断折的声音。\n" NOR;
                result = ([ "msg" : msg ]);
        }

        return result;
}

string perform_action_file(string action)
{
/*
        object me = this_player();

        if( me->query_family() != "丐帮" && query("reborn/family_name", me) != "丐帮" )
                return 0;
*/

        return __DIR__"dragon-strike/" + action;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
               me->delete_skill(sub_skillnames);
}

/*
// Let parry skill take its special effort.
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("dragon-strike", 1)) < 100 ||
            !living(query_temp("weapon", me) || objectp(me)) )
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) * 2 / 3 +
             me->query_skill("dragon-strike", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "不待回身，一招「神龙摆尾」，反手还劈一掌。\n"
                                    "$N" HIC "见这招来势凶狠，不敢硬接，纵身避开。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "只见$n" HIC "左掌圆劲，右掌直势，使招「见龙在田」，挡在身前。\n"
                                    "这一招纯是防御，却是在双方之间布了一道坚壁。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "当下不敢怠慢，双掌飞舞，将自己全身笼罩在掌力之下。\n"
                                    "这一守当真是稳若渊停岳峙，直无半点破绽。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("dragon-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("huntian-qigong",1) >= 10)        return 0.8;
        else return 1.0;
}

// 技能典故介绍
string query_description()
{
        return
        "降龙十八掌勇往直前，它的威力甚至超过了六脉神剑，当然"
        "综合起来与六脉神剑相差还颇有距离。关于降龙十八掌的"
        "定位问题颇有争议，这里是依据萧峰手下的功夫定位的。"
        "当然学习还是要找洪七公，降龙十八掌乃是丐帮专用武功，"
        "其它门派的人物不可学习，丐帮学习的条件是你的妻子或"
        "女友能够拿得出像样的叫化鸡给洪七公吃，如何作菜这就靠自"
        "己摸索了。有几处地方可以学习厨艺。不过如果你没有 31"
        " 点的先天膂力和 24 点的先天根骨，就省省，可不必摸索了。"
        "降龙十八掌要先将十八掌学齐到 80 级，然后通过演练合"
        "成降龙十八掌。";
}

int help(object me)
{
        write(HIC"\n降龙十八掌："NOR"\n");
        write(@HELP

    降龙十八掌是丐帮镇帮之宝，是天下最刚猛的武功。

        学习要求：
                自行演练，将十八路掌法合而为一
                内力3000
                先天臂力25
                先天根骨20
                基本掌法180
                基本掌法不低于降龙掌
HELP
        );
        return 1;
}