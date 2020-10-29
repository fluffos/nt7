// lonely-sword.c 独孤九剑

#include <ansi.h>
#include <combat.h>

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int action_po(object me, object victim, object weapon, int damage);//
int action_busy(object me, object victim, object weapon, int damage);
int action_damage(object me, object victim, object weapon, int damage);//
int action_parry(object me, object victim, object weapon, int damage);
int action_dodge(object me, object victim, object weapon, int damage);


string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
        "却见$n踏前一步，剑式斜指你的右臂，想要使$P闪身而退。\n",
        "$n以攻为守，以进为退，凝神运气向$P猛攻快打地挥出方位大异的泰山"+(order[random(13)])+"「快活三」"NOR"三剑。\n",
        "$n剑法突变，剑势伸缩不定，奔腾矫夭，逆使嵩山剑法的"+(order[random(13)])+"「天外玉龙」"NOR"企图迫使$P变招。\n",
        "$n突然一剑点向$P的$l，虽一剑却暗藏无数后着，$P手足无措，攻势不由自主停了下来！\n",
        "$n不闪不避，举剑闪电般使出"+(order[random(13)])+"「叠翠浮青」"NOR"反削$P的$l，想挡过你此招。\n",
        "$n突然使出青城派松风剑法的"+(order[random(13)])+"「鸿飞冥冥」"NOR"，可是方位却有所偏差，长剑对着$P一绞，企\n图突破$P的攻势！\n",
        "$n挺剑一招象是"+(order[random(13)])+"「白云出岫」"NOR"回刺$P的$l，企图将$P的攻势化解。\n",
        "只见$n不退反进，身如飘风，诡异地一式"+(order[random(13)])+"「天柱云气」"NOR"，动向无定不可捉摸地挡住了$P的\n进攻。\n",
        "$n不退反进，使出恒山剑招"+(order[random(13)])+"「绵里藏针」"NOR"，森森剑气充溢四周！架开了$P的这招\n",
});
mapping *action = ({
([      "action" : "但见$N挺身而上，$w一旋，一招仿佛泰山剑法的「" HIC "来鹤清"
                   "泉" NOR "」直刺$n的$l",
        "force" : 290,
        "attack": 145,
        "dodge" :-95,
        "parry" :-105,
        "damage": 160,
        "damage_type" : "刺伤"
]),
([      "action" : "$N奇诡地向$n挥出「" CYN "泉鸣芙蓉" NOR "」、「" MAG "鹤翔"
                   "紫盖" NOR "」、「" HIG "石廪书声" NOR "」、「" HIW "天柱"
                   "云气" NOR "」及「" HIY "雁回祝融" NOR "」衡\n山五神剑",
        "force" : 410,
        "attack": 135,
        "dodge" :-135,
        "parry" :-175,
        "damage": 270,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N剑随身转，续而刺出十九剑，竟然是华山「" HIW "玉女十九剑"
                   NOR "」，但奇的是这十九剑便如一招，手法之快，\n直是匪夷所"
                   "思",
        "force" : 310,
        "attack": 115,
        "dodge" :-75,
        "parry" :-105,
        "damage": 205,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑势忽缓而不疏，剑意有余而不尽，化恒山剑法为一剑，向$n慢"
                   "慢推去",
        "force" : 280,
        "attack": 125,
        "dodge" :-55,
        "parry" :-125,
        "damage": 160,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑意突焕气象森严，便似千军万马奔驰而来，长枪大戟，黄沙千"
                   "里，尽括嵩山剑势击向$n",
        "force" : 340,
        "attack": 160,
        "dodge" :-65,
        "parry" :-95,
        "damage": 220,
        "damage_type" : "刺伤"
]),
([      "action" : "却见$N身随剑走，左边一拐，右边一弯，剑招也是越转越加狠辣，"
                   "竟化「" HIY "泰山十八盘" NOR "」为一剑攻\n向$n",
        "force" : 250,
        "attack": 135,
        "dodge" :-85,
        "parry" :-105,
        "damage": 210,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑招突变，使出衡山的「" HIB "一剑落九雁" NOR "」，削向$n"
                   "的$l，怎知剑到中途，突然转向，大出$n\n意料之外",
        "force" : 240,
        "attack": 105,
        "dodge" :-125,
        "parry" :-175,
        "damage": 180,
        "damage_type" : "刺伤"
]),
([      "action" : "$N吐气开声，一招似是「" CYN "独劈华山" NOR "」，手中$w向下"
                   "斩落，直劈向$n的$l",
        "force" : 345,
        "attack": 125,
        "dodge" :-115,
        "parry" :-145,
        "damage": 210,
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w越转越快，使的居然是衡山的「" HIW "百变千幻云雾十"
                   "三式" NOR "」，剑式有如云卷雾涌，旁观\n者不由得目为之眩",
        "force" : 350,
        "attack": 145,
        "dodge" :-165,
        "parry" :-185,
        "damage": 250,
        "damage_type" : "刺伤"
]),
([      "action" : "$N含笑抱剑，气势庄严，$w轻挥，尽融「" HIR "达摩剑" NOR "」"
                   "为一式，闲舒地刺向$n",
        "force" : 330,
        "attack": 135,
        "dodge" :-95,
        "parry" :-125,
        "damage": 260,
        "damage_type" : "刺伤"
]),
([      "action" : "$N举起$w运使「" CYN "太极剑" NOR "」剑意，划出大大小小无"
                   "数个圆圈，无穷无尽源源不绝地缠向$n",
        "force" : 230,
        "attack": 105,
        "dodge" :-285,
        "parry" :-375,
        "damage": 140,
        "damage_type" : "刺伤"
]),
([      "action" : "$N神声凝重，$w上劈下切左右横扫，挟雷霆万钧之势逼往$n，「"
                   HIR "伏摩剑" NOR "」的剑意表露无遗",
        "force" : 330,
        "attack": 185,
        "dodge" :-135,
        "parry" :-155,
        "damage": 280,
        "damage_type" : "刺伤"
]),
([      "action" : "却见$N突然虚步提腰，使出酷似武当「" HIG "蜻蜓点水" NOR
                   "」的一招",
        "force" : 180,
        "attack": 95,
        "dodge" :-285,
        "parry" :-375,
        "damage": 130,
        "damage_type" : "刺伤"
]),
([      "action" : "$N运剑如风，剑光霍霍中反攻$n的$l，尝试逼$n自守，剑招似是"
                   "「" HIR "伏魔剑" NOR "」的「" HIR "龙吞式" NOR "」",
        "force" : 270,
        "attack": 155,
        "dodge" :-135,
        "parry" :-165,
        "damage": 260,
        "damage_type" : "刺伤"
]),
([      "action" : "$N突然运剑如狂，一手关外的「" HIY "乱披风剑法" NOR "」，"
                   "猛然向$n周身乱刺乱削",
        "force" : 330,
        "attack": 145,
        "dodge" :-175,
        "parry" :-255,
        "damage": 220,
        "damage_type" : "刺伤"
]),
([      "action" : "$N满场游走，东刺一剑，西刺一剑，令$n莫明其妙，分不出$N剑法"
                   "的虚实",
        "force" : 310,
        "attack": 165,
        "dodge" :-115,
        "parry" :-135,
        "damage": 270,
        "damage_type" : "刺伤"
]),
([      "action" : "$N抱剑旋身，转到$n身后，杂乱无章地向$n刺出一剑，不知使的是"
                   "什么剑法",
        "force" : 330,
        "attack": 135,
        "dodge" :-175,
        "parry" :-215,
        "damage": 225,
        "damage_type" : "刺伤"
]),
([      "action" : "$N突然一剑点向$n的$l，虽一剑却暗藏无数后着，$n手足无措，不"
                   "知如何是好",
        "force" : 360,
        "attack": 160,
        "dodge" :-150,
        "parry" :-285,
        "damage": 210,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑挟刀势，大开大阖地乱砍一通，但招招皆击在$n攻势的破绽，"
                   "迫得$n不得不守",
        "force" : 510,
        "attack": 225,
        "dodge" :-135,
        "parry" :-175,
        "damage": 190,
        "damage_type" : "刺伤"
]),
([      "action" : "$N反手横剑刺向$n的$l，这似有招似无招的一剑，威力竟然奇大，"
                   "$n难以看清剑招来势",
        "force" : 334,
        "attack": 135,
        "dodge" :-155,
        "parry" :-185,
        "damage": 280,
        "damage_type" : "刺伤"
]),
([      "action" : "$N举剑狂挥，迅速无比地点向$n的$l，却令人看不出其所用是什么"
                   "招式",
        "force" : 380,
        "attack": 125,
        "dodge" :-145,
        "parry" :-215,
        "damage": 230,
        "damage_type" : "刺伤"
]),
([      "action" : "$N脸上突现笑容，似乎已看破$n的武功招式，胸有成竹地一剑刺向"
                   "$n的$l",
        "force" : 390,
        "attack": 155,
        "dodge" :-185,
        "parry" :-275,
        "damage": 230,
        "damage_type" : "刺伤"
]),
});

mapping *action2 = ({
([      "action" : "$N随手一剑指向$n，落点正是$n的破绽所在，端的是神妙无伦，不"
                   "可思议",
        "force" : 370,
        "attack": 135,
        "dodge" :-185,
        "parry" :-300,
        "damage": 238,
        "post_action" : (: action_busy :),
        "damage_type" : "刺伤"
]),
([
        "action" : "$N将$w随手一摆，但见$n自己向$w撞将上来，神剑之威，当真人所"
                   "难测",
        "force" : 410,
        "attack": 155,
        "dodge" :-300,
        "parry" :-300,
        "damage": 280,
        "post_action" : (: action_damage :),
        "damage_type" : "刺伤"
]),
([      "action" : HIW "但见$N手中$w" HIW "破空长吟，平平一剑刺向$n，毫无招式可言",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_parry :),
        "damage_type" : "刺伤"
]),
([      "action" : HIW "$N揉身欺近，轻描淡写间随意刺出一剑，简单之极，无招无式",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_dodge :),
        "damage_type" : "刺伤"
]),
([      "action" : HIW "$N身法飘逸，神态怡然，剑意藏于胸中，手中$w" HIW "随意挥洒而出，独孤"
                   "九剑已到了收发自如的境界",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_po :),
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
        ||  query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        if( query("int", me)<34 )
                return notify_fail("你的天资不足，无法理解独孤九剑的剑意。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想杀尽敌人，没能理解独孤九剑的的真正含义。\n");

        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你一心想怎么学好剑法去害人，结果没能理解独孤九剑。\n");

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什么独孤九剑，乱七八糟的，没有半点气势。\n");

        if( me->query_skill("sword", 1) < me->query_skill("lonely-sword", 1) )
                return notify_fail("你的基本剑法造诣有限，无法理解更高深的独孤九剑。\n");

        return 1;
}
int practice_skill(object me)
{
        return notify_fail("独孤九剑只能通过「总诀式」来演练。\n");
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
        int lvl;
        lvl = (int) me->query_skill("lonely-sword", 1);
        if( objectp(weapon) && query("id", weapon) == "xuantie jian" )
        {
                if( me->query_str() >= 60 && me->query_int() >= 36
                &&  random(lvl) > 120
                &&  me->query_skill("force")>150 && query("neili", me) > 400 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": HIR "$N脸色凝重虔诚，缓缓举起玄铁重剑，突然跃起身剑合一，"
                                          "驭剑化为一道黑气向$n冲刺而去" NOR,
                                "damage": 900,
                                "attack": 300,
                                "dodge" :-300,
                                "parry" :-300,
                                "damage_type" : "刺伤"
                        ]);
                }
        }

        if( query("lonely-sword/nothing", me) )
               return action2[random(sizeof(action2))];

        else   return action[random(sizeof(action))];
}


int action_damage(object me, object victim, object weapon, int damage)
{
        string msg;
        string*limbs=query("limbs", victim);
        int dam;
        int skill= me->query_skill("lonely-sword", 1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage == RESULT_DODGE && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/2 ) //躲过
        {
                addn("neili", -50, me);
                message_combatd("\n$N一声长啸:"HIW"「剑旋离身，剑啸震山河」"NOR", 瞬间剑芒大作,朝$n激射而至！\n",me,victim);
                dam=skill*2+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi", dam);
                msg = COMBAT_D->damage_msg(dam, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg, me, victim);
                COMBAT_D->report_status(victim);
                return 1;
        } else 
        if( damage > 0 && !victim->is_busy()
        &&  skill > 100
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/4)   //打中对方
        {
                addn("neili", -50, me);
                message_combatd("\n$N突然悟出"HIW"「练精化气, 练气化神, 练神还虚」"NOR"之真理, 手中长剑突然消失, 朝$n飞至！\n",me,victim);
                dam=skill+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi",dam);
                msg = COMBAT_D->damage_msg(skill*2, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
        }
        return 1;
}

int action_po(object me, object victim, object weapon, int damage)
{
        // 破对方武功、内功  为终极效果
        int skill= me->query_skill("lonely-sword", 1);
        string v_force = victim->query_skill_mapped("force");
        int jiali;
        if( !me->is_fighting(victim) ) return 0;
        if( damage > 0 )// 打中对方 破内功 或者破内力
        {
                if( v_force && skill > 250
                &&  random(skill/2) > random(victim->query_skill("force"))
                &&  random(skill) > 200
                &&  victim->query_map_skill("force")
                &&  objectp(weapon=query_temp("weapon", me) )
                &&  random(3)==1 )
                {
                        addn("neili", -100, me);
                        victim->map_skill("force");
                        message_combatd(HIC "$N一剑得手，剑招源源而出，剑尖直刺$n丹田！\n",me,victim);
                        message_combatd(RED "$n只觉混身如遭电击，真气劲力紊乱难控，已然不能施展"+to_chinese(v_force)+"！\n" NOR,me,victim);
                        return 1;
                } else 
                if( random(me->query_skill("lonely-sword",1)) > 100 &&
                    random(me->query_skill("sword",1))>100 &&
                    me->query_skill("force",1) > 120 &&  
                    !victim->is_busy() ) {
                        addn("neili", -50, me);
                        if( query("neili", victim)>600 )
                                addn("neili", -500, victim);
                        else
                                set("neili", 0, victim);
                        message_combatd(HIC "\n$N一剑得手，剑招源源而出，欲将$n团团困住！\n",me,victim);
                        message_combatd(HIM "$n急运内力，使出浑身解数，方才脱出剑圈！\n"NOR , me, victim);
                        return 1;
                }
        }
        else if( damage == RESULT_DODGE && !victim->is_busy()) //躲过  震慑对方
        {
                addn("neili", -50, me);
                message_combatd(HIY "$n只觉$N剑中暗藏无数玄机，稍一胆怯，不敢攻上前去！\n"NOR,me,victim);
                victim->start_busy(1+random(skill/50));
                return 1;
        }
        else if ( damage == RESULT_PARRY ) //对手招架住 可顺势再创对手
        {
                jiali=query("jiali", me);
                if (!jiali) jiali=10;
                if( random(skill)>140 )
                {
                        addn("neili", -50, me);
                        message_combatd(HIC "$N相交一招，已然看破$n武功套路，胸有成竹地刺出一剑!\n",me,victim);
                        victim->receive_wound("qi", (random(jiali)*2+100));
                        message_combatd(HIM"$N剑气纵横! 一道剑气划过了$n的胸口。结果鲜血狂喷!\n"NOR,me,victim);
                        COMBAT_D->report_status(victim,1);
                }
                return 1;
        }
        return 1;

}

int action_busy(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage <= 0 && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(query("combat_exp", me))>query("combat_exp", victim)/3)//威力极小,如果没有上两个则包括躲过和招架
        {
                addn("neili", -50, me);
                message_combatd("$N顿然领悟了"HIW"「剑在神先, 绵绵不绝」"NOR"之真意, 剑尖瞬间爆出无数大大小小,\n正反斜直各种各样的圆圈, 将$n团团困住。\n",me,victim);
                victim->start_busy(2+random(skill/50));
                return 1;
        } else 
        if( damage > 0  && !victim->is_busy()
        &&  skill > 100
        &&  random(skill) > victim->query_skill("force",1)/3)
        {
                addn("neili", -30, me);
                message_combatd(CYN"$N以意驭剑，画出数个"RED"圆圈"CYN"，左右兼顾，将$n缠在正中！\n" NOR,me,victim);
                victim->start_busy(1+random(skill/50));
        }
        return 1;
}

int action_dodge(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);

        weapon = query_temp("weapon", me);
        if( !me->is_fighting(victim)) return 0;
        if( random(me->query_skill("lonely-sword",1)) >= 200 &&
            random(me->query_skill("sword",1))>180 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("dodge") ) {
                addn("neili", -50, me);
                victim->map_skill("dodge");
                if( !victim->is_busy() )
                        victim->start_busy(random(3)+1);

                msg = HIC "\n$N突然举剑一刺，剑招随便无章，却莫明奇妙地突破了$n的攻势，大出$n意料！\n" ;
                msg += HIR"$n大吃一惊，竟然忘了闪避！\n"NOR;
                message_combatd(msg,me,victim);
                return 1;
        }
        else if( damage <= 0 && random(skill) > random(victim->query_skill("dodge",1)/3))
        {
                addn("neili", -50, me);
                message_combatd("\n却见$N飘身而上，半空中举剑上挑，剑光已封住了$n身周数尺之地，攻得精巧无比！\n",me,victim);
                victim->receive_damage("qi",skill/2);
                msg = COMBAT_D->damage_msg(skill/2, "刺伤");
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                if( objectp(weapon) )
                msg=replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
       }
       return 1;
}

int action_parry(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( damage == RESULT_DODGE &&
            random(me->query_skill("lonely-sword",1)) > 140 &&
            random(me->query_skill("sword",1))>140 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("parry") ) {
                addn("neili", -50, me);
                victim->map_skill("parry");
                if( !victim->is_busy() )
                        victim->start_busy(random(2)+1);

                msg = HIC "\n$N举剑反攻，后发先至地刺向$n，不仅把$n招术封死，更进一步发出攻击！\n" NOR;
                msg += HIY"$n难以看清剑招来势,竟然忘了招架！\n"NOR;
                message_combatd(msg,me,victim);
        }
        else if (damage <= 0 && random(skill) > random(victim->query_skill("parry",1)/3))
        {
                addn("neili", -50, me);
                msg = "\n$N一个箭步纵到$n身前，手腕微颤，挥剑斜撩，横削$n$l，剑法极尽灵动轻捷\n";
                victim->receive_damage("qi",skill/2);
                msg += COMBAT_D->damage_msg(skill/2, "刺伤"); //此次伤害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
       }
}

int double_attack() { return 1; }

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("lonely-sword", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 90;
        if (lvl < 325) return 100;
        if (lvl < 350) return 110;
        return 120;
}

void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("lonely-sword", 1);

        if (lvl >= 20
         && !query("can_perform/lonely-sword/jue", me))
        {
                tell_object(me, HIC "你通晓了独孤九剑「" HIW "总决式" HIC "」的奥秘。\n" NOR);
                set("can_perform/lonely-sword/jue", 1, me);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
        }

        if (lvl > 120
         && query("can_perform/lonely-sword/qi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/qi",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIW "破气式"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIW "破"
                                        "气式" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 150
         && query("can_perform/lonely-sword/po", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/po",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIR "总破式"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIR "总"
                                        "破式" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 200
         && query("can_perform/lonely-sword/yi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/yi",random(i))<100 )
                {
                        tell_object(me, HIC "你对独孤九剑「" HIR "剑意"
                                        HIC "」有了新的领悟。\n" NOR);
                } else
                {
                        tell_object(me, HIC "你通晓了独孤九剑「" HIR "剑"
                                        "意" HIC "」的奥秘。\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }
}

int difficult_level()
{
        object me = this_object();

        if( query("lonely-sword/nothing", me) )
                return 300;

        else   return 200;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, n;
        object m_weapon;

        if ((int) me->query_skill("lonely-sword", 1) < 120
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me)
         || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("parry", 1) / 2 +
        me->query_skill("lonely-sword", 1);       

        // 无招
        if( query("lonely-sword/nothing", me) )
        {
                if( n = ABILITY_D->check_ability(me, "def_power-dgjj-nothing") )
                        dp += dp * n/100;
                //if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) >
                //    ob->query_skill("parry"))
                if( dp * 2 + random(dp) > ap )
                {
                        result = ([ "damage": -damage ]);

                        result += (["msg" : HIC "$n" HIC "突然举剑一刺，剑招随意无章，"
                                            "却莫明奇妙地突破了$N的攻势，大出$N意料。\n"
                                            "$n一转剑势，剑招源源而出，对$N发动攻势！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);

                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                        return result;
                }

        }

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "突然举剑一刺，剑招随意无章，"
                                            "却莫明奇妙地突破了$N的攻势，大出$N意料。\n"
                                            "$n一转剑势，剑招源源而出，对$N发动攻势！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me),3);
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "举剑反攻，后发先至地刺向$N，不仅把"
                                            "$N招术封死，更进一步发出攻击！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "提剑回刺，落点正是$N的破绽，"
                                            "$N不得不撤招严守，身形一晃间已退出丈许！\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "却见$n" HIC "踏前一步，剑式斜指$P" HIC
                                            "右臂，招式迅捷无比，使得$N" HIC "闪身而退"
                                            "。\n" NOR]);
                        break;
                case 4:
                        result += (["msg" : HIC "$n" HIC "突然一剑点向$N" HIC "，虽一剑"
                                            "却暗藏无数后着，$N" HIC "顿时手足无措，攻"
                                            "势不由自主停了下来。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "眼见避无可避，只好提剑乱刺一通，"
                                            "居然出乎意料地将$N的攻击接去。\n" NOR]);
                        break;
                }

                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() +
                                 HIY "，中攻直进一剑挺进，可是$N" HIY "反招更快"
                                 "，进袭$n" HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + "轻挑"
                                 "，" HIY "正指向$N" HIY "攻势中的破绽，可是$N"
                                 HIY "身形一变，破绽立刻不成为破绽。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY
                                 "续变换数种剑招，然而$N" HIY "理也不理，再次攻"
                                 "出，丝毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        int lvl;
        object weapon, weapon2;
        int i, ap, dpp, dpd, dpf;
        string type, msg, msg1;

        lvl = me->query_skill("lonely-sword", 1);

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "lonely-sword"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("lonely-sword/nothing", me) )
                return 0;

        ap = me->query_skill("sword");
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");

        switch(random(3))
        {
        case 1:
                if (ap * 3 / 4 + random(ap) > dpp)
                {
                        addn("neili", -100, me);
                        result = ([ "damage" : damage_bonus ]);

                        msg1 = random(2) ? HIR "$N" HIR "一剑攻出，剑气横飞，" + weapon->name() + HIR
                                           "时若游龙穿空，时若惊鸿渡云，却不知这普通的"
                                           "一剑之中竟蕴藏着如此威力。\n" NOR:
                                           HIR "$N" HIR "手中" + weapon->name() + HIR "犹"
                                           "如生了眼睛一般，一剑随意挥出，竟直刺向$n" HIR
                                           "小腹，看似平淡，但方位、力道却拿捏得恰倒好处。\n" NOR;
                        result += ([ "msg" : msg1 ]);
                        return result;
                }
                break;

        case 2:
                message_combatd(HIC "\n$N" HIC "随意挥洒手中的" + weapon->name() +
                               HIC "，招招从出其不意的方位直指$n" HIC "招式中的"
                               "破绽！\n" NOR, me, victim);

                if (! me->is_busy())
                {
                        weapon=query_temp("weapon", me);
                        weapon2=query_temp("weapon", victim);
                        if( weapon2)type=query("skill_type", weapon2);


                        if (ap * 3 / 4 + random(ap) >= dpf && weapon2
                        &&  type != "pin")
                        {
                                msg = HIW "$n" HIW "觉得眼前眼花缭乱，手中"
                                      "的" + weapon2->name() + HIW "一时竟"
                                      "然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                                addn("neili", -100, me);
                        } else
                        {
                                msg = HIY "$n" HIY "略得空隙喘息，一时间却"
                                      "也无力反击。\n" NOR;
                                addn("neili", -40, me);
                        }
                }else
                if (ap * 4 / 5 + random(ap) > dpd)
                {
                        msg = HIY "$n" HIY "连忙抵挡，一时间不禁手忙脚乱，"
                              "无暇反击。\n" NOR;

                        if (! victim->is_busy())
                        victim->start_busy(1 + random(lvl / 30));
                }
                else
                {
                        msg = HIC "$N" HIC "随意挥洒着手中的" + weapon->name() +
                              HIC "刺向$n" HIC "，不过$n" HIC "防守的异常严密，$N"
                              HIC "一时竟然无法找到破绽。\n" NOR;
                        if (! victim->is_busy())
                        victim->start_busy(1);
                }
                message_combatd(msg, me, victim);
                break;

        default :
                if (ap * 2 / 3 + random(ap) > dpd &&
                    ! me->is_busy() &&
                    ! random(2) &&
                    !query_temp("lonely-sword/lian", me) )
                {
                        weapon=query_temp("weapon", me);
                        message_combatd(HIY "\n$N" HIY "胸藏剑意，手中" + weapon->name() + HIY
                                     "随意挥洒而出，速度之快，方位之准，\n显是独孤九剑已达到"
                                     "收发自如的境界。\n" NOR,
                                     me, victim);

                        addn("neili", -270, me);

                        set_temp("lonely-sword/lian", 1, me);
                        for (i = 0; i < 5; i++)
                        {
                                if (! me->is_fighting(victim))
                                        break;

                                if (! victim->is_busy() && random(2) == 1)
                                        victim->start_busy(1);

                                COMBAT_D->do_attack(me, victim, weapon, 0);
                        }
                        delete_temp("lonely-sword/lian", me);

                }
                break;
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}
string perform_action_file(string action)
{
        return __DIR__"lonely-sword/" + action;
}

int help(object me)
{
        write(HIC"\n独孤九剑："NOR"\n");
        write(@HELP

    “独孤九剑，有进无退！”
    创制这套剑法的独孤求败前辈，名字叫做‘求败’，他毕生想
求一败而不可得，这剑法施展出来，天下无敌，当年他仗剑江湖，
无敌于天下，连找一个对手来逼得他回守一招都不可得，委实令人
可惊可佩。
    无招胜有招，敌强我更强。独孤九剑不含招式，有招既无招，
无招亦有招。独孤九剑要旨在于「悟」，不可拘泥不化，讲究料敌
机先，出奇制胜。通晓了九剑剑意，则无所施而不可。
    独孤九剑，自“总诀式”、“破剑式”、“破刀式”以至“破
枪式”、“破鞭式”、“破索式”、“破掌式”、“破箭式”而到
第九剑“破气式”。九剑的第一招“总诀式”，有种种变化，用以
体演总诀，便于修习。第二招“破剑式”，用以破解普天下各门各
派的剑法。第三招“破刀式”，用以破解单刀、双刀、柳叶刀、鬼
头刀、大砍刀、斩马刀种种刀法。第四招“破枪式”，包括破解长
枪、大戟、蛇矛、齐眉棍、狼牙棒、白蜡杆、禅杖、方便铲种种长
兵刃之法。第五招“破鞭式”，用以破解钢鞭、铁锏、点穴橛、拐
子、蛾眉刺、匕首、板斧、铁牌、八角槌、铁椎等等短兵刃，第六
招“破索式”，破解的是长索、软鞭、三节棍、链子枪、铁链、渔
网、飞锤流星等等软兵刃。第七招“破掌式”，破的是拳脚指掌上
的功夫，将长拳短打、擒拿点穴、魔爪虎爪、铁沙神掌，诸般拳脚
功夫尽数包括内在。第八招“破箭式”这个“箭”字，则总罗诸般
暗器，练这一剑时，须得先学听风辨器之术，不但要能以一柄长剑
击开敌人发射来的种种暗器，还须借力反打，以敌人射来的暗器反
射伤敌。第九剑“破气式”，是为对付身具上乘内功的敌人而用，
神而明之，存乎一心。

        学习要求：
                只能向风清扬学习
                紫霞神功100级
                内力600
HELP
        );
        return 1;
}
