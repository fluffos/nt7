// hamagong.c 蛤蟆功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_force(string force) { return 1; } 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hamagong", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

/*
mapping *action = ({
([      "action" : "$N忽而倒竖，一手撑地，身子横挺，只以一掌向$n的$l拍出",
        "lvl" : 0,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N双手在地上一撑，身子忽地拔起，一跃三尺，落在$n的面前，单掌向$p直劈而下",
        "lvl" : 10,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N突然伸手在自己脸上猛抓一把，又反足在自己肾上狠踢一脚，一掌击出，中途方向必变，实不知将打何处",
        "lvl" : 20,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "突然之间，$N俯身疾攻，上盘全然不守，微微侧头，一口唾沫往$n$l吐去",
        "lvl" : 30,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N丝毫不动声色，双腿微曲，右掌平伸，左掌缓缓运起蛤蟆功的劲力，呼的一声推向$n",
        "lvl" : 80,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N默念口诀运气经脉，只觉愈转愈是顺遂，当下一个翻身跃起，咕的一声叫喊，双掌对着$n拍出",
        "lvl" : 110,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "但见$N双腿微曲，双掌会收，然后向$n一上一下，一放一收，斗然击出",
        "lvl" : 140,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N闭眼逼住呼吸，过了片刻，猛跃而起，眼睛也不及睁开，双掌便向$n的方向推了出去",
        "lvl" : 170,
        "skill_name" : "蛤蟆功"
]),
([      "action" : "$N脚步摇摇幌幌的看上去马上就会跌倒，忽然双腿一弯、一登，口中阁的一声叫喝，手掌向$n猛然推出",
        "lvl" : 199,
        "skill_name" : "蛤蟆功"
]),
});
*/
mapping *action = ({
([      "action": "$N轻身一跃，使出一招" + HIY"「沙漠孤舟」"NOR + "，左掌横，右掌带，将$n逼开。",
        "force" : 200,
        "lvl"   : 0,
        "dodge" : -20,
        "damage": 240,
        "skill_name": "沙漠孤舟",
        "damage_type": "瘀伤"
]),
([      "action":"只见$N倏地向前跨出一步，一招" + WHT"「万里独归」"NOR + "，双掌一错，顺势攻向$n",
        "force" : 220,
        "lvl"   : 20,
        "dodge" : -20,
        "damage": 250,
        "skill_name": "万里独归",
        "damage_type": "瘀伤"
]),
([      "action":"$N一招" + HIW"「鸣沙寒烟」"NOR + "，来势曼妙无方，掌力微吐，罩向$n周身。",
        "force" : 400,
        "lvl"   : 40,
        "dodge" : -30,
        "damage": 250,
        "skill_name": "鸣沙寒烟",
        "damage_type": "瘀伤"
]),
([      "action":"$N低眉曲身，掌势若有若无，恰恰将$n来招一一封住，并暗含反击之意，正是一招" + HIR"「霓裳弄雪」"NOR + "。",
        "force" : 225,
        "dodge" : -30,
        "lvl"   : 70,
        "damage": 270,
        "skill_name": "霓裳弄雪",
        "damage_type": "瘀伤"
]),
([      "action":"$N一招" + HIB"「秋恨客途」"NOR + "，抽身提步，不退反进，双掌平推，来如电闪，径直拍向$n。",
        "force" : 530,
        "dodge" :-20,
        "lvl"   : 100,
        "damage": 300,
        "skill_name": "秋恨客途",
        "damage_type": "瘀伤"
]),
});

mapping *reverse_action = ({
([      "action": "忽听$N大叫三声，三个筋斗翻将出来，大吼一声，恶狠狠的朝$n扑将上来",
        "dodge": -15,
        "parry": -20,
        "force": 300,
        "damage": 60,
        "damage_type": "跌伤"
]),
([      "action":"但见$N疯势更加厉害，口吐白沫，举头朝$n猛撞",
        "parry": -15,
        "force": 360,
        "damage": 70,
        "damage_type": "瘀伤"
]),
([      "action":"$N蓦地张口，白牙一闪，已向$n$l咬落，又快又准",
        "dodge": -5,
        "force": 420,
        "damage": 80,
        "weapon": "牙齿",
        "damage_type": "咬伤"
]),
([      "action":"$N一口唾沫急吐，势挟劲风，竟将痰涎唾沫也当作了攻敌利器",
        "dodge": -45,
        "force": 480,
        "damage": 90,
        "weapon":"唾沫",
        "damage_type": "刺伤"
]),
([      "action":"$N忽然张嘴，一口唾沫往$n脸上吐去，发掌击向$n趋避的方位，同时又是一口浓痰吐将过来",
        "dodge": -30,
        "force": 540,
        "damage": 100,
        "weapon" : "浓痰",
        "damage_type": "刺伤"
]),
([      "action":"此时$N所使的招数更是希奇古怪，诡异绝伦，身子时而倒竖，时而直立，忽然一手撑地，身子横挺，一手出掌打向$n$l",
        "dodge": -10,
        "force": 600,
        "damage": 110,
        "damage_type": "瘀伤"
]),
});

int valid_combine(string combo) { return combo=="shexing-diaoshou"; }

int valid_enable(string usage)
{
        if (usage == "force" || usage == "parry" ) return 1;
        if (usage == "strike") {
                if (this_player()->query_skill("hamagong",1) < 200) {
                        /*
                        message_vision("$N蹲下身来，口中咕咕咕的叫了几声，要将蛤蟆功口诀用在拳脚之上，但无论如何使用不上。\n", this_player() );
                        write("你的蛤蟆功火候不足，无法运用它到掌法中。\n");
                        */
                        return 0;
                }
                return 1;
        }
        return 0;
}
int valid_learn(object me)
{
        mapping skl;
        string *sname;
        int v, i, k=0;

        if( query("character", me) == "光明磊落"
            || query("character", me) == "狡黠多变" )
                return notify_fail("你心中暗道：这蛤蟆功阴毒异常，估计会伤及自"
                                   "身，还是别练为妙。\n");

        /*
        if( query("con", me)<32 )
                return notify_fail("你先天根骨孱弱，无法修炼蛤蟆功。\n");

        if( query("dex", me)<32 )
                return notify_fail("你先天身法太差，无法修炼蛤蟆功。\n");
        */

        if( query("gender", me) == "无性" && query("hamagong", me)>49 )
                return notify_fail("你无根无性，阴阳不调，难以领会高深的蛤蟆功。\n");

        /*
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技火候不足，难以领会蛤蟆功。\n");
        */

        i = (int)me->query_skill("hamagong", 1);

        if ((int)me->query_skill("force", 1) < 30
         || (int)me->query_skill("force", 1)/2 < i/3 )
                return notify_fail("你的基本内功火候不足，不能学蛤蟆功。\n");

        if( query("tianmo_jieti/times", this_player()) )
                return ::valid_learn(me);

        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );

        if(me->query_skill("hamagong", 1) > 99){

                for(v=0; v<sizeof(skl); v++) {
                        if (SKILL_D(sname[v])->check() == "force")
                        k++;
                }
                if ( k >=3 )
                return notify_fail("你体内不同内力互相冲撞，难以领会更高深的内功。\n");
        }

        if( query("class", me) == "bonze" && !query("reborn/times", me))
        {
                if( query("gender", me) == "女性" )
                        return notify_fail("小尼姑练蛤蟆功，不怕别人叫你秃头蛤蟆吗？\n");
                if( query("gender", me) == "男性" )
                        return notify_fail("大师傅练蛤蟆功，不怕别人叫你秃头蛤蟆吗？\n");
        }

        if( query("family/family_name", me) == "丐帮" && !query("reborn/times", me) )
                return notify_fail("老叫化的徒弟学不了蛤蟆功。\n");

        if( query("family/family_name", me) == "武当派"  && !query("reborn/times", me))
                return notify_fail("老道练蛤蟆功，不怕别人叫你牛鼻子蛤蟆吗？\n");

        return ::valid_learn(me);
}
int practice_skill(object me)
{
        if( query("family/master_id", me) != "ouyang feng"
        && me->query_skill("hamagong", 1) > 99)
                 return notify_fail("蛤蟆功需高人指点才能继续提高。\n");

        if( query_temp("weapon", me) )
                 return notify_fail("蛤蟆从不手持兵刃，所以练蛤蟆功也必须空手。\n");

        if( query("jing", me)<50 )
                return notify_fail("你的精气不够练蛤蟆功。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够练蛤蟆功。\n");
        addn("neili", -30, me);
        me->receive_damage("jing", 10);
        if (me->query_skill("hamagong", 1) > 100){
                addn("neili", -40, me);
                me->receive_damage("jing", 20);
        }
        if (me->query_skill("hamagong", 1) > 150){
                addn("neili", -20, me);
                me->receive_damage("jing", 10);
        }
        if (me->query_skill("hamagong", 1) > 200){
                addn("neili", -10, me);
                me->receive_damage("jing", 10);
        }
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -40;
        int d_e2 = -20;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 190;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        string *power_msg =
        ({
                HIR"$N蹲下身来，运起蛤蟆功，双手平推，吐气扬眉，阁阁阁三声叫喊。这三推之力带有风疾雷迅的猛劲，实是非同小可"NOR,
                WHT"$N阁阁两声怒吼，蹲下身来，呼的双掌齐出，掌力未到，掌风已将地下尘土激起，一股劲风直扑$n面门，势道雄强无比"NOR,
                HIR"$N脸色阴沉，脸颊上两块肌肉微微牵动，两臂弯曲，阁的一声大叫，双手挺出，一股巨力横冲直撞的朝$n推将过来"NOR,
                WHT"$N蹲低身子，口中咕咕咕的叫了三声，双手推出，以蛤蟆功向$n猛攻。$n身周在$P掌力笼罩之下，只激得灰泥弥漫，尘土飞扬"NOR,
        });
        string *reverse_msg =
        ({
                HIM"但见$N招术奇特，怪异无伦，忽尔伸手在自己脸上猛抓一把，忽尔反足在自己臀上狠踢一脚，每一掌打将出来，中途方向必变，实不知打将何处"NOR,
                HIM"$N忽然反手拍拍拍连打自己三个耳光，大喊一声，双手据地，爬向$n，忽地翻身一滚，骤然间飞身跃起，双足向$n连环猛踢"NOR,
                HIM"突然之间，$N俯身疾攻，上盘全然不守，出招怪异无比，将蛤蟆功逆转运用，上者下之，左者右之，招数难以捉摸"NOR,
                HIM"$N全身经脉忽顺忽逆，手上招数虽然走了错道，但是错有错着，出手怪诞，竟教$n差愕难解"NOR,
        });

        lvl = (int) me->query_skill("hamagong", 1);
        if (me->query_skill_mapped("force") == "hamagong" ) {
                if( !query_temp("hmg_dzjm", me) && query_temp("powerup", me) && random(me->query_skill("force",1))>250 && query("neili", me)>1000 && query("jiali", me)>100 )
                        return ([
                        "action": power_msg[random(sizeof(power_msg))],
                        "dodge": -120,
                        "parry": -120,
                        "force": 650+random(100),
                        "damage": 120,
                        "damage_type": random(2)?"内伤":"瘀伤"
                        ]);
                else if( query_temp("reverse", me) && random(me->query_skill("force",1))>400 && random(me->query_skill("strike",1))>300 && query("neili", me)>1000 )
                        return ([
                        "action": reverse_msg[random(sizeof(reverse_msg))],
                        "dodge": -200,
                        "parry": -200,
                        "force": 630+random(100),
                        "damage": 300+random(20),
                        "damage_type": "瘀伤",
                        ]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        if( query_temp("hmg_dzjm", me) )
                return ([
                        "action"      : reverse_action[random(6)]["action"],
                        "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                        "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                        "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                        "damage_type" : random(2) ? "内伤" : "瘀伤",
                ]);
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

        lvl = me->query_skill("hamagong", 1);

        if (damage_bonus < 150
           || lvl < 180
           || query("neili", me)<300
        // || query_temp("weapon", me )
           || me->query_skill_mapped("force") != "hamagong"
           || me->query_skill_mapped("strike") != "hamagong"
           || me->query_skill_prepared("strike") != "hamagong")
                return 0;

        if (damage_bonus / 2 > victim->query_con() / 10)
        {
                addn("neili", -30, me);
                victim->receive_wound("qi", damage_bonus/2, me);
                return WHT "$n" WHT "硬承下$N" WHT "一掌，霎时全"
                       "身一颤，经脉受震，喷出一口鲜血！\n" NOR;
        }
}

string exert_function_file(string func)
{
        return __DIR__"hamagong/exert/" + func;
}

string perform_action_file(string action)
{
        return __DIR__"hamagong/perform/" + action;
}

int help(object me)
{
        write(HIC"\n蛤蟆功："NOR"\n");
        write(@HELP

    欧阳锋创立此功，为白驼山派本门内功。此功也可作为掌法使
用，并能与蛇形刁手互备。
    这蛤蟆功纯系以静制动，他全身涵劲蓄势，蕴力不吐，只要敌
人一施攻击，立时便有猛烈无比的劲道反击出来，刚猛无匹。

        学习要求：
                基本内功10级
                太监无法领悟50级以上的蛤蟆功
                相应的戾气
HELP
        );
        return 1;
}
