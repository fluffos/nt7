// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// equipmentd.c

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;
#include <equipment.h>

#define EQUIP_DIR       "/inherit/template/"
#define EQUIP_LIST      CONFIG_DIR "equiplist/"

// 兵器有 2件，分为兵器和空手兵器(hand, finger)
// 防具有 head, armor, cloth, pants, boots, waist, wrists, surcoat 8件
// 饰品有 charm, ring, neck 3件
// 7个防具7孔，2个兵器9孔，3个饰品3孔
/*

淑女剑（小龙女）增加玉女剑法武功伤害
君子剑（小龙女）增加全真剑法武功伤害
玉箫（黄药师）增加玉箫剑法武功伤害
软猬甲（黄药师）护甲，面对敌人空手伤害几率卸掉并反伤敌人一半伤害
逍遥神仙环（无崖子）增加六阳掌折梅手武功伤害
真武剑（张三丰）增加太极剑武功伤害，持有者必须正神
琥珀神环（慕容博）增加参合指武功伤害
冷月宝刀（胡斐）增加刀剑归真武功伤害
闯王军刀（胡斐）增加刀剑归真武功伤害
黑索（渡厄、渡劫、渡难）增加日月鞭法武功伤害
锦澜袈裟（渡劫）护甲，增加有效招架
神草结（渡难）靴子，增加有效轻功
血刀（血刀老祖）增加血刀刀法武功伤害
日月金轮（金轮法王）增加日月轮法武功伤害
龙象袈裟（金轮法王）护甲，可注入(force)龙象之力抵御伤害
玉竹杖（洪七公）增加打狗棒法武功伤害
葵花针（东方不败）增加葵花魔功辟邪剑法武功伤害
圣火令（张无忌）增加圣火令法武功伤害

急速就是增加出招的几率 暴击是双倍伤害几率 格挡是减免30%伤害几率。命中是无视闪避招架的几率 精通是perform伤害加成
还有 5行可以是 急速 暴击 格挡（减免伤害） 精通  命中
金木水火土，攻击，治疗，buff, 攻击， 防御
火代表眩晕 水代表招式变慢 金代表持续伤害命中 木代表致盲

a 物理攻击类
增加attack（固定）
增加伤害（随机）
b  物理防御
增加气血抗性（固定）
增加额外气血和护甲（随机）
增加气血恢复（随机）
c 魔法攻击
增加attack（固定）
增加魔法伤害（随机）
d 魔法防御
增加 魔法抗性（固定）
增加额外心神和精力（随机）
f 治疗输出
增加疗伤比例（固定）
增加法力、灵力（随机）
增加法力 灵力恢复（随机）
g 对友方的增强buff
增加buff 持续时间（固定）
增加队伍群伤（随机）
增加队伍群抗（随机）
h 对怪物的debuff
增加buff 持续时间（固定）
减少怪物抗性（随机）
*/

// 所有属性
mapping all_props = ([
        "consistence"   : "耐久度",     // 基本属性
        "damage"        : "兵器伤害力", // 基本属性
        "unarmed_damage": "空手伤害力", // 基本属性
        "armor"         : "保护力",     // 基本属性

        "str"           : "臂力",       // weapon/armor/rings \attribute.c
        "int"           : "悟性",       // weapon/armor/rings \attribute.c
        "con"           : "根骨",       // weapon/armor/rings \attribute.c
        "dex"           : "身法",       // weapon/armor/rings \attribute.c
        "kar"           : "福缘",       // weapon/armor/rings \attribute.c
        "per"           : "容貌",       // weapon/armor/rings \attribute.c

        "max_neili"     : "内力最大值", // weapon/armor/rings \user.c
        "max_qi"        : "气血最大值", // weapon/armor/rings \user.c
        "max_jingli"    : "精力最大值", // weapon/armor/rings \user.c
        "max_jing"      : "精气最大值", // weapon/armor/rings \user.c
        "max_potential" : "潜能上限",   // weapon/armor/rings \user.c
        "max_experience": "体会上限",   // weapon/armor/rings \user.c

        "sword"         : "剑法",       // weapon \combatd.c
        "blade"         : "刀法",       // weapon \combatd.c
        "club"          : "棍法",       // weapon \combatd.c
        "hammer"        : "锤法",       // weapon \combatd.c
        "staff"         : "杖法",       // weapon \combatd.c
        "whip"          : "鞭法",       // weapon \combatd.c
        "unarmed"       : "拳脚",       // weapon \combatd.c
        "strike"        : "掌法",       // weapon \combatd.c
        "cuff"          : "拳法",       // weapon \combatd.c
        "hand"          : "手法",       // weapon \combatd.c
        "finger"        : "指法",       // weapon \combatd.c
        "claw"          : "爪法",       // weapon \combatd.c

        "attack"        : "攻击",       // weapon \combatd.c
        "parry"         : "招架",       // armor  \combatd.c
        "dodge"         : "躲闪",       // armor  \combatd.c
        "defense"       : "防御",       // armor  \combatd.c

        "neili_recover" : "内力恢复",   // armor/rings 战斗中每秒恢复 \char.c/damage.c
        "qi_recover"    : "生命恢复",   // armor/rings 战斗中每秒恢复 \char.c/damage.c
        "jing_recover"  : "精气恢复",   // armor/rings 战斗中每秒恢复 \char.c/damage.c

        // 火焰伤害，冷冻伤害，闪电伤害，毒素伤害，抗火，抗寒，抗闪电，抗毒
        "add_poison"    : "毒伤害",     // weapon \itemd.c
        "add_magic"     : "魔伤害",     // weapon \itemd.c
        "add_metal"     : "金伤害",     // weapon \itemd.c
        "add_wood"      : "木伤害",     // weapon \itemd.c
        "add_water"     : "水伤害",     // weapon \itemd.c
        "add_fire"      : "火伤害",     // weapon \itemd.c
        "add_earth"     : "土伤害",     // weapon \itemd.c
        "reduce_magic"  : "抗魔",       // armor  \itemd.c
        "reduce_metal"  : "抗金",       // armor  \itemd.c
        "reduce_wood"   : "抗木",       // armor  \itemd.c
        "reduce_water"  : "抗水",       // armor  \itemd.c
        "reduce_fire"   : "抗火",       // armor  \itemd.c
        "reduce_earth"  : "抗土",       // armor  \itemd.c
        "reduce_poison" : "抗毒",       // armor  \itemd.c/condition.c
        "avoid_poison"  : "忽视中毒",   // armor/rings \itemd.c/condition.c

        "research_effect"       : "研究效果",   // weapon/armor/rings \cmds
        "practice_effect"       : "练习效果",   // weapon/armor/rings \cmds
        "study_effect"          : "读书效果",   // weapon/armor/rings \cmds
        "learn_effect"          : "学习效果",   // weapon/armor/rings \cmds
        "derive_effect"         : "汲取效果",   // weapon/armor/rings \cmds
        "research_times"        : "研究次数",   // weapon/armor/rings \cmds
        "learn_times"           : "学习次数",   // weapon/armor/rings \cmds
        "practice_times"        : "练习次数",   // weapon/armor/rings \cmds
        "study_times"           : "读书次数",   // weapon/armor/rings \cmds
        "derive_times"          : "汲取消耗",   // weapon/armor/rings \cmds
        // 以上都是基本属性

        "magic_find"    : "寻宝率(MF值)",       // weapon/rings \equipmentd.c

        "leech_neili"   : "偷取内力",           // weapon 命中偷取内力几率：命中敌人时按伤害值的10%比率回复内力 \damage.c/itemd.c
        "leech_qi"      : "偷取生命",           // weapon 命中偷取生命几率：命中敌人时按伤害值的10%比率回复生命 \damage.c/itemd.c

        "ap_power"      : "绝招攻击力",         // weapon/rings  \skillsd.c
        "dp_power"      : "绝招防御力",         // armor         \skillsd.c
        "da_power"      : "绝招伤害力",         // weapon/rings  \skillsd.c

        //"ignores_parry":
        "avoid_parry"   : "忽视目标招架",       // rune \combatd.c
        "avoid_dodge"   : "忽视目标躲闪",       // rune \combatd.c
        "avoid_force"   : "忽视内功防御",       // rune \combatd.c
        "avoid_attack"  : "忽视目标特攻",       // rune \combatd.c
        "avoid_defense" : "忽视目标特防",       // rune \combatd.c

        //"critcal"       : "暴击",               // weapon/rings \combatd.c 增加杀气：加一点杀气，暴击（双倍伤害）的概率增加1%
        "through_armor" : "穿透破甲",           // weapon       \combatd.c 穿透破甲-攻击时无视目标防具的保护力through_armor

        "double_damage" : "双倍伤害",           // weapon/rings \combatd.c

        "qi_abs_neili"  : "伤转内力",           // rings 30%的机会受损的生命x%转换为内力 \damage.c

        "add_reward"    : "获取额外奖励",       // weapon/rings \giftd.c
        /*
        "add_exp"       : "获取额外经验",       // weapon/rings \giftd.c
        "add_pot"       : "获取额外潜能",       // weapon/rings \giftd.c
        "add_mar"       : "获取额外体会",       // weapon/rings \giftd.c
        */

        "add_blind"     : "致盲",                       // weapon 终极兵器 致盲-让对手失明 \damage.c/itemd.c
        "add_freeze"    : "冰冻",                       // weapon 终极兵器 冰冻-迟缓，减缓对方攻击，攻击pfm速度降低，无任何防御，无躲闪，无招架，就是挨打 \damage/itemd.c/combatd.c/cmds
        "add_forget"    : "遗忘",                       // weapon 终极防具 遗忘-使对方忘记所有技能的绝招add_oblivion
        "add_weak"      : "虚弱",                       // weapon 终极兵器
        "add_busy"      : "忙乱",                       // weapon 终极兵器


        "avoid_blind"   : "忽视致盲",                   // armor/rings 终极防具
        "avoid_freeze"  : "忽视冰冻",                   // armor/rings 终极防具
        "avoid_forget"  : "忽视遗忘",                   // armor/rings 终极兵器
        //add_oblivion

        "avoid_weak"    : "忽视虚弱",                   // armor/rings 终极防具
        "avoid_busy"    : "忽视忙乱",                   // armor/rings 终极防具
        "reduce_busy"   : "化解忙乱",                   // armor/rings 终极防具
        "avoid_fear"    : "忽视恐惧",                   // armor/rings 终极防具

        "fatal_blow"    : "致命一击",                   // weapon 终极兵器 必杀率-拥有20%的几率损伤目标的生命x%


        "add_skill"     : "提升技能",                   // weapon/rings 终极兵器
        "add_damage"    : "追加伤害",                   // weapon 终极兵器
        "reduce_damage" : "化解伤害",                   // armor 终极防具
        "full_self"     : "战神附体",                   // armor 终极防具 战神附体-气血内力自动恢复  远古装备
        "avoid_die"     : "浴血重生",                   // armor/ring 凤凰涅槃，浴血重生，忽视死亡   远古装备
        "counter_damage": "伤害反射",                   // armor 终极防具 伤害反射，受到伤害时30%几率的伤害x%反射给对方
]);

mapping value_2_props = ([
        "consistence"   : "耐久度",     // 基本属性           a
        "damage"        : "兵器伤害力", // 基本属性           a
        "unarmed_damage": "空手伤害力", // 基本属性           a
        "armor"         : "保护力",     // 基本属性           a

        "str"           : "臂力",       // weapon/armor/rings a
        "int"           : "悟性",       // weapon/armor/rings a
        "con"           : "根骨",       // weapon/armor/rings a
        "dex"           : "身法",       // weapon/armor/rings a
        "kar"           : "福缘",       // weapon/armor/rings a
        "per"           : "容貌",       // rings              a

        "max_jingli"    : "精力最大值", // weapon/armor/rings a
        "max_jing"      : "精气最大值", // weapon/armor/rings a
        "max_potential" : "潜能上限",   // weapon/armor/rings a
        "max_experience": "体会上限",   // weapon/armor/rings a

        "sword"         : "剑法",       // weapon             a
        "blade"         : "刀法",       // weapon             a
        "club"          : "棍法",       // weapon             a
        "hammer"        : "锤法",       // weapon             a
        "staff"         : "杖法",       // weapon             a
        "whip"          : "鞭法",       // weapon             a
        "unarmed"       : "拳脚",       // weapon             a
        "strike"        : "掌法",       // weapon             a
        "cuff"          : "拳法",       // weapon             a
        "hand"          : "手法",       // weapon             a
        "finger"        : "指法",       // weapon             a
        "claw"          : "爪法",       // weapon             a

        "attack"        : "攻击",       // weapon             a
        "parry"         : "招架",       // armor              a
        "dodge"         : "躲闪",       // armor              a
        "defense"       : "防御",       // armor              a

        "research_times": "研究次数",   // weapon/armor/rings a
        "learn_times"   : "学习次数",   // weapon/armor/rings a
        "practice_times": "练习次数",   // weapon/armor/rings a
        "study_times"   : "读书次数",   // weapon/armor/rings a
]);

mapping value_3_props = ([
        "max_neili"     : "内力最大值", // weapon/armor/rings b
        "max_qi"        : "气血最大值", // weapon/armor/rings b
        "neili_recover" : "内力恢复",   // armor/rings        b
        "qi_recover"    : "生命恢复",   // armor/rings        b
        "jing_recover"  : "精气恢复",   // armor/rings        b

        "add_poison"    : "毒伤害",     // weapon                           b
        "add_magic"     : "魔伤害",
        "add_metal"     : "金伤害",     // weapon                           b
        "add_wood"      : "木伤害",     // weapon                           b
        "add_water"     : "水伤害",     // weapon                           b
        "add_fire"      : "火伤害",     // weapon                           b
        "add_earth"     : "土伤害",     // weapon                           b
        "reduce_magic"  : "抗魔",       // armor
        "reduce_metal"  : "抗金",       // armor                            b
        "reduce_wood"   : "抗木",       // armor                            b
        "reduce_water"  : "抗水",       // armor                            b
        "reduce_fire"   : "抗火",       // armor                            b
        "reduce_earth"  : "抗土",       // armor                            b
        "reduce_poison" : "抗毒",       // armor                            b
        "avoid_poison"  : "忽视中毒",   // armor/rings                      b

        "research_effect"       : "研究效果",   // weapon/armor/rings       b
        "practice_effect"       : "练习效果",   // weapon/armor/rings       b
        "study_effect"          : "读书效果",   // weapon/armor/rings       b
        "learn_effect"          : "学习效果",   // weapon/armor/rings       b
        "derive_effect"         : "汲取效果",   // weapon/armor/rings       b
        "derive_times"          : "汲取消耗",   // weapon/armor/rings       b
]);

mapping value_5_props = ([
        "magic_find"    : "寻宝率(MF值)",       // weapon/rings             c
        "ap_power"      : "绝招攻击力",         // weapon/rings             c
        "dp_power"      : "绝招防御力",         // armor                    c
        "da_power"      : "绝招伤害力",         // weapon/rings             c
        "avoid_defense" : "攻击无视目标防御",   // weapon/rings             c
        "avoid_parry"   : "攻击无视目标招架",   // weapon/rings             c
        "avoid_dodge"   : "攻击无视目标躲闪",   // weapon/rings             c
        "avoid_force"   : "攻击无视内功防御",   // weapon/rings             c
        "avoid_attack"  : "无视目标特殊攻击",   // armor                    c
        "leech_neili"   : "偷取内力",           // weapon 命中偷取内力几率：命中敌人时按伤害值的10%率回复内力   c
        "leech_qi"      : "偷取生命",           // weapon 命中偷取生命几率：命中敌人时按伤害值的10%比率回复生命 c
        "double_damage" : "双倍伤害",           // weapon/rings 增加杀气：加一点杀气，暴击（双倍伤害）的概率增加1%  c
        "through_armor" : "穿透破甲",           // weapon/rings 穿透破甲-攻击时无视目标防具的保护力through_armor        c
        "qi_abs_neili"  : "伤转内力",           // rings 30%的机会受损的生命x%转换为内力  c

        "add_blind"     : "致盲",               // weapon 终极兵器 致盲-让对手失明 c
        "avoid_blind"   : "忽视致盲",           // armor/rings 终极防具            c
]);

mapping value_10_props = ([
        "add_freeze"    : "冰冻",                       // weapon 终极兵器 冰冻-迟缓，减缓对方攻击，攻击pfm速度降低，无任何防御，无躲闪，无招架，就是挨打 d
        "add_forget"    : "遗忘",                       // weapon 终极防具 遗忘-使对方忘记所有技能的绝招add_oblivion    d
        "add_weak"      : "虚弱",                       // weapon 终极兵器 让对手攻防伤害减半，包括绝招                 d
        "add_busy"      : "忙乱",                       // weapon 终极兵器                                              d

        "avoid_freeze"  : "忽视冰冻",                   // armor/rings 终极防具 d
        //"avoid_fear"    : "忽视恐惧",                   // armor/rings 终极防具 d
        "avoid_forget"  : "忽视遗忘",                   // armor/rings 终极兵器 d
        "avoid_weak"    : "忽视虚弱",                   // armor/rings 终极防具 d
        "avoid_busy"    : "忽视忙乱",                   // armor/rings 终极防具 d
        "reduce_busy"   : "化解忙乱",                   // armor/rings 终极防具 d

        "fatal_blow"    : "致命一击",                   // weapon 终极兵器 必杀率-拥有20%的几率损伤目标的生命x%     d                                    d
        "add_skill"     : "提升技能",                   // weapon/rings 终极兵器                                    d
        "add_damage"    : "追加伤害",                   // weapon 终极兵器                                          d
        "reduce_damage" : "化解伤害",                   // armor 终极防具                                           d
        "full_self"     : "战神附体",                   // armor 终极防具 战神附体-气血内力自动恢复                 d
        "avoid_die"     : "浴血重生",                   // armor/ring 凤凰涅槃，浴血重生，忽视死亡                  d
        "counter_damage": "伤害反射",                   // armor 终极防具 伤害反射受到伤害时30%几率的伤害x%反射给对方 d
]);



// 宝石分为4个等级，碎片，完好1，稀有1+1，神之1+2
// 一个固定的属性(金木水火土)+1-2个随机属性

// 百分比的属性
string *percent_props = ({
        "gold_find", "magic_find", "add_magic", "add_metal", "add_wood", "add_water", "add_fire", "add_earth",
        "add_poison", "reduce_magic", "reduce_metal", "reduce_fire", "reduce_wood", "reduce_water", "reduce_earth",
        "reduce_poison", "avoid_poison", "research_effect", "learn_effect", "practice_effect",
        "derive_effect", "study_effect", "ap_power", "dp_power", "da_power", "avoid_attack",
        "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force",
        "double_damage", "through_armor", "qi_abs_neili", "add_reward",
        "add_exp", "add_pot", "add_mar", "add_blind", "add_freeze",
        "add_forget", "add_weak", "avoid_blind", "avoid_freeze",
        "avoid_forget", "avoid_weak", "avoid_busy", "fatal_blow",
        "add_damage", "reduce_damage", "full_self", "avoid_die", "counter_damage", "leech_neili", "leech_qi",
});

mapping prop_values = ([
        "damage"       : ({ 4600, 6600, 9600, 13600, 18600, 24600, 31600, 39600, 50000, }),
        "unarmed_damage"       : ({ 4600, 6600, 9600, 13600, 18600, 24600, 31600, 39600, 50000, }),
        "armor"        : ({ 2200, 2900, 3700, 4600, 5600, 7700, 8900, 10200, 11500, }),

        "str,con,dex,int,kar,per"     : ({ 1, 2, 3, }),         // 200

        "max_qi"        : ({ 2500, 3500, 4500, }),              // 200000
        "max_jing"      : ({ 1200, 1700, 2200, }),              // 100000
        "max_jingli"    : ({ 2500, 3500, 4500, }),              // 200000
        "max_neili"     : ({ 6000, 8000, 10000, }),             // 500000
        "max_potential,max_experience"  : ({ 30000, 40000, 50000, }),   // 2000000

        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 10, 20, 30, }),        // 500
        "defense,parry,dodge"  : ({ 10, 20, 30, }),

        "jing_recover,qi_recover"       : ({ 20, 30, 40, }),    // 1000
        "neili_recover"     : ({ 60, 70, 80, }),
        "leech_qi,leech_neili"  : ({ 1.0, 1.5, 2.0, }),   // 1000

        "magic_find"    : ({ 1, 2, 3, }),       // 70

        "add_magic,add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 1, 2, 3, }),       // 42
        "add_poison"    : ({ 1, 2, 3, }),       // 42
        "reduce_magic,reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1.0, 1.2, 1.5, }), // 35
        "reduce_poison,avoid_poison"    : ({ 1.0, 1.2, 1.5, }),       // 44

        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 5, 10, 15, }),    // 1000
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 1, 2, 3, }), // 180

        "ap_power,da_power"    : ({ 1.0, 1.5, 2.0, }),       // 70
        "dp_power"    : ({ 1.0, 1.2, 1.5, }),       // 70
        "avoid_attack,avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1.0, 1.2, 1.5, }),       // 70

        "double_damage,through_armor"   : ({ 1.0, 1.5, 2.0, }),       // 70
        "qi_abs_neili"   : ({ 1.0, 1.5, 2.0, }),       // 63

        "add_reward"    : ({ 1.0, 1.2, 1.5, }),       // 70
        "add_exp,add_pot,add_mar"     : ({ 1.0, 1.5, 2.0, }),       // 92

        "add_blind,fatal_blow"   : ({ 1.0, 1.5, 2.0 }),        // 42
        "avoid_blind" : ({ 1.0, 1.2, 1.5, }), // 44

        "add_skill"     : ({ 100, 130, 160, 200 }),
        "add_busy"      : ({ 6, 8, 10, 12 }),
        "reduce_busy"   : ({ 1, 2, 3, 4 }),
        "add_damage,add_freeze,add_forget,add_weak" : ({ 6, 8, 10, 12 }),
        "avoid_fear,avoid_forget,avoid_weak,avoid_busy,avoid_die,full_self,counter_damage,reduce_damage": ({ 1, 2, 3, 4 }),
]);

// 属性强化值1-9星
mapping steady_values = ([
        "damage,unarmed_damage"       : ({ 4600,6600,9600,13600,18600,24600,31600,39600,50000 }),
        "armor"         : ({ 2200,2900,3700,4600,5600,7700,8900,10200,11500 }),

        "str,con,dex,int"     : ({ 5, 7, 9, 11, 14, 17, 20, 25, 30, }),

        "max_qi"        : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_jing"      : ({ 500, 1000, 1500, 2500, 3500, 4500, 6000, 7500, 10000, }),
        "max_jingli"    : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_neili"     : ({ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 100000, }),
        "max_potential,max_experience"  : ({ 200000, 400000, 600000, 1000000, 1500000, 2000000, 3000000, 4000000, 6000000, }),

        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 20, 30, 40, 60, 80, 110, 150, 200 }),
        "dodge,parry,defense"   : ({ 10, 15, 20, 25, 30, 35, 40, 45, 60 }),

        "jing_recover,qi_recover"       : ({ 60, 70, 80, 100, 120, 140, 160, 180, 200, }),
        "neili_recover"     : ({ 120, 140, 160, 180, 240, 280, 320, 360, 500, }),
        "leech_qi,leech_neili"  : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),

        "magic_find"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),

        "add_poison,add_magic,add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 3, 5, 7, 10, 13, 16, 19, 23, 28, }),
        "reduce_poison,avoid_poison,reduce_magic,reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 2, 3, 4, 5, 6, 7, 8, 9, }),

        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 10, 15, 20, 25, 30, 35, 40, 45, 50 }),
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 5, 7, 9, 12, 15, 18, 21, 25, 30, }),

        "ap_power,da_power"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "dp_power"      : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_attack"  : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),

        "double_damage,through_armor"   :  ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "qi_abs_neili"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),

        "add_reward"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "add_exp,add_pot,add_mar,add_force"  :  ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),

        "add_blind,avoid_blind"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),

        "add_freeze,add_forget,add_weak,avoid_freeze,avoid_forget,avoid_weak,avoid_busy" : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "add_busy,reduce_busy"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "fatal_blow"    : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "add_skill"     : ({ 10, 15, 20, 25, 30, 35, 40, 45, 50, }),
        "add_damage"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "reduce_damage" : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "full_self"     : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "avoid_die"     : ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
        "counter_damage": ({ 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, }),
]);

// 装备的品级有6级，前2个品级属性没有特殊，从稀有（第三个）品级开始有特殊属性
// 宝石的等级有3级，宝石的属性应该和装备前2个品级的属性一样
// qlvl1只有基本属性，qlvl2才有宝石属性，qlvl3拥有宝石属性，qlvl4拥有史诗属性，qlvl5拥有传说属性，qlvl6拥有神奇属性
mixed weapon_props = ({
        ({ "damage", "int", "str", "con", "dex", "kar", "skill", "attack",
           "magic_find", "add_poison",
           "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect",
           "derive_effect", "study_effect", "ap_power", "da_power", "avoid_defense",
           "avoid_parry", "avoid_dodge", "avoid_force", "double_damage",
           "through_armor",
           "add_blind",
           "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential", "max_experience",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "attack", "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge",
           "avoid_force", "through_armor", "skill", // skill特殊处理
           "leech_qi", "leech_neili",
        }),
        ({ "through_armor", "double_damage",
           "add_blind",
           "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power",
           "leech_qi", "leech_neili", "add_damage", "add_busy", "add_freeze", "add_weak",
        }),
        ({ "add_blind", "double_damage", "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power",
           "add_freeze", "add_weak", "add_forget", "add_busy", "fatal_blow", "add_damage",
        }),
});

mixed armor_props = ({
        ({ "armor", "int", "str", "con", "dex", "kar", "max_neili", "max_qi", "max_jing",
           "max_jingli", "max_potential", "max_experience", "parry", "dodge", "defense",
           "neili_recover", "jing_recover", "qi_recover", "reduce_poison", "avoid_poison", "research_times",
           "learn_times", "practice_times", "derive_times", "study_times", "research_effect",
           "learn_effect", "practice_effect", "derive_effect", "study_effect", "dp_power", "avoid_attack",
           "avoid_blind",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "reduce_poison", "avoid_poison", "max_qi", "max_jing", "parry", "dodge", "defense",
        }),
        ({ "neili_recover", "jing_recover", "qi_recover", "avoid_attack", "dp_power", "avoid_blind",
           "research_effect", "practice_effect", "derive_effect",
           "counter_damage", "reduce_busy", "reduce_damage", "avoid_freeze", "avoid_weak",
        }),
        ({ "avoid_blind", "research_effect",
           "dp_power", "research_effect", "practice_effect", "derive_effect",
           "avoid_freeze", "avoid_forget", "avoid_weak", "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_die", "counter_damage",
        }),
});

// 项链amulet、戒指ring、护身符属性charm
mixed ring_props = ({
        ({ "per", "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential",
           "max_experience", "neili_recover", "jing_recover", "qi_recover",
           "magic_find", "avoid_poison", "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect", "derive_effect", "study_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force",
           "double_damage", "through_armor", "qi_abs_neili",
           "avoid_blind",
           "through_armor",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "reduce_poison", "avoid_poison", "max_qi", "max_jing",
        }),
        ({ "through_armor", "magic_find", "qi_abs_neili", "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force",
           "reduce_busy", "avoid_freeze", "avoid_weak",
        }),
        ({ "avoid_blind", "research_effect", "practice_effect", "derive_effect",
           "magic_find", "double_damage",
           "avoid_freeze", "avoid_forget", "avoid_weak", "avoid_die", "avoid_busy", "reduce_busy",
        }),
});

string *rare_props = ({
        "avoid_freeze", "avoid_forget", "avoid_weak", "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_die", "counter_damage",
        "add_freeze", "add_weak", "add_forget", "add_busy", "fatal_blow", "add_damage",
});

// 套化的兵器属性
string *suit_weapon_props = ({
        "double_damage", "avoid_forget", "add_damage", "add_skill", "fatal_blow", "add_busy", "add_weak",
        "add_freeze",

});
// 套化的防具属性
string *suit_armor_props = ({
        "reduce_busy", "avoid_busy", "avoid_weak", "avoid_die",
        "counter_damage", "avoid_forget", "full_self", "reduce_damage", "research_effect",
});
// 套化的护身符属性
string *suit_ring_props = ({
        "magic_find", "avoid_die",
        "full_self", "avoid_busy", "avoid_forget", "research_effect",
});

void create()
{
        seteuid(getuid());
        set("name", "装备精灵");
        set("id", "equipmentd");
}

// 为属性名称匹配中文
varargs string chinese(string prop, mixed value)
{
        string desc;

        if( !undefinedp(all_props[prop]) )
                desc = all_props[prop];
        else
                desc = to_chinese(prop);

        if( !value ) return desc;

        if( member_array(prop, percent_props) != -1 )
        {
                if( floatp(value) )
                desc = sprintf("%s %s%.1f%s", desc,
                               value > 0 ? "+" : "-", abs(value), "%");
                else
                desc = sprintf("%s %s%d%s", desc,
                               value > 0 ? "+" : "-", abs(value), "%");
        }
        else
        {
                if( floatp(value) )
                desc = sprintf("%s %s%.1f", desc,
                               value > 0 ? "+" : "-", abs(value));
                else
                desc = sprintf("%s %s%d", desc,
                               value > 0 ? "+" : "-", abs(value));
        }

        return desc;
}

// 获取装备部件的属性
varargs mixed query_prop_value(string prop, int ilvl, int s)
{
        int i, j, flag;
        int *value;
        float n;
        mapping data;
        string *ks;
        string *temp_str;

        flag = 0;
        if( s ) data = copy(steady_values); // 强化属性
        else data = copy(prop_values);
        ks = keys(data);
        for( i=0; i<sizeof(ks); i++ ) {
                //reset_eval_cost();
                temp_str = explode(ks[i], ",");
                for( j=0; j<sizeof(temp_str); j++ )
                        if( temp_str[j] == prop ) {
                                value = data[ks[i]];
                                flag = 1;
                                break;
                        }
                if( flag ) break;
        }
        if( !flag || !value ) return 0;
        if( ilvl ) {
                if( ilvl > sizeof(value) )
                        ilvl = sizeof(value);

                if( member_array(prop, rare_props) == -1 )
                        return value[ilvl-1];

                n = 1.0 + (ilvl-1)*0.5;
                return n;
        }
        return value[random(sizeof(value))];
}

// 装备绿化时候获得的属性
mapping apply_ultimate_prop(object ob, string type, int ilvl)
{
        string *props;
        string prop;
        mapping apply;
        mixed value;
        int n;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "xsword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "throwing"
        ||  type == "hands"
        ||  type == "finger" )
                props = suit_weapon_props;
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // 护身符·左
        ||  type == "myheart2"  // 护身符·右
        ||  type == "neck" )
                props = suit_ring_props;
        else
                props = suit_armor_props;

        n = 1;
        if( random(10000) == 1 )
                n = 2;
        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                value = query_prop_value(prop, ilvl, 1);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 生成宝石属性
varargs mapping apply_gem_prop(string type, int ilvl, int special, int n)
{
        string *props;
        string prop;
        mapping apply;
        mixed value;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "xsword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "throwing"
        ||  type == "hands"
        ||  type == "finger" ) {
                if( special )
                        props = weapon_props[3];
                else
                        props = weapon_props[0]; // 获取对应的品质属性
        }
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // 护身符·左
        ||  type == "myheart2"  // 护身符·右
        ||  type == "neck" ) {
                if( special )
                        props = ring_props[3];
                else
                        props = ring_props[0];
        }
        else
        {
                if( special )
                        props = armor_props[3];
                else
                        props = armor_props[0];
        }

        if( type == "weapon" ) props -= ({ "skill" });

        if( special ) n = 3;
        if( !n ) n = 1 + random(3);

        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                if( prop == "skill" ) // skill特殊分析
                {
                        int rate;
                        rate = random(100);
                        if( type == "finger" )
                        {
                                if( rate < 50 )
                                        prop = "claw";
                                else
                                        prop = "finger";
                        } else
                        if( type == "hands" )
                        {
                                if( rate < 25 )
                                        prop = "unarmed";
                                else if( rate < 50 )
                                        prop = "cuff";
                                else if( rate < 75 )
                                        prop = "hand";
                                else
                                        prop = "strike";
                        } else
                                prop = type;
                }
                value = query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 设置装备属性
mapping apply_props(string type, int ilvl, int n, int special)
{
        mapping applied_prop;
        mapping enchase_prop;
        mapping data = ([]);
        string *apply;
        mapping *insert;
        int i, j;

        applied_prop = ([]);
        insert = ({});

        if( !n ) return data;
        for( i=1; i<=n; i++ ) // 凹槽数
        {
                enchase_prop = copy(apply_gem_prop(type, ilvl, special));
                apply = keys(enchase_prop);
                for( j=0; j<sizeof(apply); j++ )
                {
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[apply[j]]) )
                                applied_prop[apply[j]] = enchase_prop[apply[j]];
                        else
                                applied_prop[apply[j]] += enchase_prop[apply[j]];
                }
                insert += ({ (["name" : HIM"玄石"NOR, "id" : "magic stone", "apply_prop" : enchase_prop]) });
        }

        data["apply_prop"] = applied_prop;
        data["insert"] = insert;
        return data;
}

protected mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str, temp_str2;
        string *temp_arr, *temp_val;
        string  temp_key, key;
        mapping temp_status;
        mapping temp_map;
        mapping *temp_map2;

        temp_status = ([ ]);

        // 解析insert
        if( sscanf(mark, "%s<insert>%s</insert>", mark, temp_str2) == 2 )
        {
                temp_map2 = ({ });
                while (sscanf(temp_str2, "%*s[%s]%s[/%s]%s", key, temp_str, key, temp_str2) > 3)
                {
                        temp_map = ([ ]);
                        temp_arr = explode(temp_str, "\n");

                        for ( i=0; i<sizeof(temp_arr); i++ ) {
                                //temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                // 解析VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;

                                if( !undefinedp(temp_map["name"]) )
                                        temp_map["name"] = trans_color(temp_map["name"], 3);
                        }
                        temp_map2 += ({ temp_map });
                }
                temp_status["insert"] = temp_map2;
        }

        // 开始解析
        while (sscanf(mark, "%*s<%s>%s</%s>%s", key, temp_str, key, mark) > 3)
        {
                temp_map = ([ ]);
                temp_arr = explode(temp_str, "\n");
                if( sizeof(temp_arr) < 2 ) {
                        if( sscanf(temp_arr[0], "%s:%d", temp_key, temp_value) == 2 ||
                            sscanf(temp_arr[0], "%s:%s", temp_key, temp_value) == 2 ) {
                               // 解析VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;

                                temp_status[key] = temp_map;
                        }
                        else if( atoi(temp_str) )
                                temp_status[key] = atoi(temp_str);
                        else
                                temp_status[key] = temp_str;

                } else {
                        for ( i=0; i<sizeof(temp_arr); i++ ) {
                                temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                // 解析VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                        }
                        temp_status[key] = temp_map;
                }
        }

        if( !undefinedp(temp_status["name"]) )
                temp_status["name"] = trans_color(temp_status["name"], 3);

        if( !undefinedp(temp_status["mod_name"]) )
                temp_status["mod_name"] = trans_color(temp_status["mod_name"], 3);

        if( !undefinedp(temp_status["long"]) )
                temp_status["long"] = trans_color(temp_status["long"], 3) + "\n";

        return temp_status;
}

// 创造一个固定物件，根据序号
varargs mixed create_object(string num, int level)
{
        string *list;
        string  mark, part, rec;
        string  type, str;
        string  filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object  ob;

        if( !num || num == "" ) {
                if( !level ) level = random(3);

                switch( random(3) )
                {
                case 0 :
                        rec = "W";
                        if( level == 0) filename = EQUIP_LIST+"basic.weapon";
                        else if( level == 1) filename = EQUIP_LIST+"advance.weapon";
                        else if( level == 2) filename = EQUIP_LIST+"expert.weapon";
                        break;
                case 1 :
                        rec = "A";
                        if( level == 0) filename = EQUIP_LIST+"basic.armor";
                        else if( level == 1) filename = EQUIP_LIST+"advance.armor";
                        else if( level == 2) filename = EQUIP_LIST+"expert.armor";
                        break;
                default:
                        rec = "G";
                        if( level == 0) filename = EQUIP_LIST+"basic.gem";
                        else if( level == 1) filename = EQUIP_LIST+"advance.gem";
                        else if( level == 2) filename = EQUIP_LIST+"expert.gem";
                        break;
                }

                this_file = read_file(filename);
                str = sprintf("%s%d", rec, level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if( num[0] == 'W' ) {
                        if( num[1] == '0' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"basic.weapon";
                        else if( num[1] == '1' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"advance.weapon";
                        else if( num[1] == '2' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"expert.weapon";
                } else if( num[0] == 'A' ) {
                        if( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.armor";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.armor";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.armor";
                } else if( num[0] == 'G' ) {
                        if(  num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.gen";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.gen";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.gen";
                }

                if( !filename )
                        return 0;

                this_file = read_file(filename);
        }

        // 解析序号对应的字符串
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) ) {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 0, temp_function);
                set("mod_mark", num, ob);
                set("can_sign", 1, ob); // 装备签名
                if( temp_status["mod_level"] )
                        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(),"sys", "创造一个错误的物件。");
                return 0;
        }
}

// 创造一个固定套装部件，根据序号
varargs object create_module(string num, int level)
{
        string mark, part, str, rec;
        string *list;
        string type;
        string filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object ob;

        if( !num || num == "" ) {
                if( !level ) level = random(4);

                if( level == 0 ) filename = EQUIP_LIST+"basic.mod";
                else if( level == 1 ) filename = EQUIP_LIST+"advance.mod";
                else if( level == 2 ) filename = EQUIP_LIST+"expert.mod";
                else if( level == 3 ) filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
                str = sprintf("A%d", level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if(  num[1] == '0' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"basic.mod";
                else if(  num[1] == '1' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"advance.mod";
                else if(  num[1] == '2' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"expert.mod";
                else if(  num[1] == '3' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
        }
        //解析序号对应的字符串
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) )
        {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 0, temp_function);
                set("mod_mark", num, ob);
                //set("can_sign", 1, ob); // 装备签名
                //if( temp_status["mod_level"] )
                //        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(), "sys", "创造一个套装部件错误。");
                return 0;
        }
}

// 创造一个动态的物件
public varargs object create_dynamic(string obj_type, int ilvl, int mf, int flag)
{
        mapping temp_status, all_list, data;
        mapping applied_prop = ([]);
        mapping *insert;
        string *gems1 = ({ "cruby", "ctopaz", "csapphire", "cemerald", "cdiamond" });
        string *gems2 = ({ "ruby", "topaz", "sapphire", "emerald", "diamond" });
        string *gems3 = ({ "xruby", "xtopaz", "xsapphire", "xemerald", "xdiamond" });
        string *gems4 = ({ "fruby", "ftopaz", "fsapphire", "femerald", "fdiamond" });
        string *gems5 = ({ "mruby", "mtopaz", "msapphire", "memerald", "mdiamond" });
        string *all_id, *types;
        string id;
        string *file;
        string color, filename;
        string base_type;
        object ob;
        int qlvl;
        int rate, rate2, n, uf, sf, rf;
        string prop, *props;

        if( !ilvl || ilvl < 1 )
                return 0;

        if( !obj_type || obj_type == "" ) { // 随机生成装备种类或宝石
                rate = random(100);
                if( rate < 35 ) obj_type = "weapon";
                else if( rate < 90 ) obj_type = "armor";
                //暂时取消饰品的掉落
                //else if( rate < 90 ) obj_type = "rings";
                else obj_type = "gem";
                flag = 0;
        }

        if( flag ) { // 指定的兵器类型、防具类型或宝石类型
                if( flag == 1 ) {
                        if( member_array(obj_type, weapon_type) != -1 )
                                base_type = "weapon";
                        else if( member_array(obj_type, armor_type) != -1 )
                                base_type = "armor";
                        else if( member_array(obj_type, rings_type) != -1 )
                                base_type = "rings";
                        else    base_type = "gem";
                } else {
                        // 系统固定的名称和ID的装备
                        all_list = type_list[obj_type];
                        all_id = values(all_list);
                        id = all_id[random(sizeof(all_id))];
                }
        } else {
                base_type = obj_type;
                types = all_type[obj_type];
                obj_type = types[random(sizeof(types))]; // 随机一种
        }

        if( flag && flag > 1 ) // 用模型文件，需要检查写法
                filename = sprintf("%s%s/%s.c", TEMPLATE_DIR, base_type, obj_type);
        else
                filename = sprintf("%s%s/%s.c", EQUIP_DIR, base_type, obj_type);

        data = ([]);
        temp_status = ([]);
        /*
        rate = random(100);
        if( rate < 40 ) data["str"] = ilvl*2 + random(ilvl);
        else if( rate < 60 ) data["con"] = ilvl*2 + random(ilvl);
        else if( rate < 80 ) data["dex"] = ilvl*2 + random(ilvl);
        else data["int"] = ilvl*2 + random(ilvl);

        data["level"] = ilvl;
        temp_status["require"] = copy(data); // 设置装备要求
        */

        if( base_type != "gem" ) // 掉落装备，非宝石
        {
                // 凹槽数量：普通0、精制1、珍稀2、史诗3、传说4、神器5
                // 武器6孔，防具4孔，护身符3孔，盾牌4孔

                data = ([]);

                if( mf < 2 ) mf = 2;

                uf = mf*10/(mf+10);  // 传说品级
                sf = mf*30/(mf+30);  // 史诗品级
                rf = mf*500/(mf+500);  // 珍稀品级

                rate = random(100);
                /*
                rate2 = random(100);
                rate = (rate + rate2) / 2;
                */

                if( mf >= 700 )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 9;       // 凹槽数量
                        else if( base_type == "armor" )
                                n = 7;
                        else // 护身符
                                n = 3;

                        if( mf >= 800 )
                                qlvl = 8;
                        else
                                qlvl = 7;

                        color = HBRED+HIW; // 神话
                } else
                if( mf >= 600 )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 5;       // 凹槽数量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 护身符
                                n = 3;
                        qlvl = 6;
                        color = HBRED+HIW; // 神话
                } else
                if( mf >= 500 )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 4;       // 凹槽数量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 护身符
                                n = 3;
                        if( (mf >= 540 && random(300) == 1) || random(1000) == 1 )
                        {
                                //qlvl = 5+random(2);
                                qlvl = 6;
                                if( qlvl == 6 ) color = HBRED+HIW; else color = HIY;
                        }
                        else
                        {
                                qlvl = 5;
                                color = HIY; // 传奇以上
                        }
                } else
                if( mf >= 400 )
                {
                        n = 3;
                        if( !random(5) )
                        {
                                if( random(10000) == 1 )
                                        qlvl = 6;
                                else
                                        qlvl = 4+random(2);
                                if( qlvl == 6 ) color = HBRED+HIW; else if( qlvl == 5 ) color = HIY; else color = HIM;
                        }
                        else
                        {
                                qlvl = 4;
                                color = HIM; // 史诗
                        }
                } else
                if( mf >= 300 )
                {
                        n = 2;
                        if( !random(3) )
                        {
                                qlvl = 3+random(3);
                                if( qlvl == 5 ) color = HIY; else if( qlvl == 4 ) color = HIM; else color = HIR;
                        }
                        else
                        {
                                qlvl = 3;
                                color = HIR; // 珍稀以上
                        }
                } else
                if( rate < uf && !random(100) )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 4;       // 凹槽数量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 护身符
                                n = 3;
                        qlvl = 5;
                        color = HIY; // 传说
                } else
                if( rate < sf && !random(50) )
                {
                        n = 3;
                        qlvl = 4;
                        color = HIM; // 史诗
                } else
                if( rate < rf )
                {
                        n = 2;
                        qlvl = 3;
                        color = HIR; // 珍稀
                }
                else
                if( rate < mf )
                {
                        n = 1;
                        qlvl = 2;
                        color = HIB; // 精制
                }
                else
                {
                        n = 0;
                        qlvl = 1;
                        color = HIW; // 普通
                }

                // 生成镶嵌的宝石
                if( mf >= 700 )
                {
                        data = apply_props(obj_type, ilvl/10, n, 1);
                        data["flute"] = n; //socket
                        data["used"] = n;
                        insert = data["insert"];
                        map_delete(data, "insert");
                        temp_status["enchase"] = copy(data); // 设置装备属性 buff/enchase ?
                        temp_status["insert"] = insert;      // 插槽宝石属性
                }
                else
                {
                        if( n > 1 )
                                n = random(n); // 随机凹槽数
                        if( n > 0 )
                        {
                                data = apply_props(obj_type, ilvl/10, n, 0);
                                data["flute"] = n; //socket
                                data["used"] = n;
                                insert = data["insert"];
                                map_delete(data, "insert");
                                temp_status["enchase"] = copy(data); // 设置装备属性 buff/enchase ?
                                temp_status["insert"] = insert;      // 插槽宝石属性
                        }
                }

                if( qlvl > 5 ) // 神器
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                props = weapon_props[3];
                        else if( base_type == "armor" )
                                props = armor_props[3];
                        else
                                props = ring_props[3];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);
                } else {
                if( qlvl > 4 ) // 传说
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                props = weapon_props[2];
                        else if( base_type == "armor" )
                                props = armor_props[2];
                        else
                                props = ring_props[2];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);
                }
                if( qlvl > 3 ) // 史诗
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                props = weapon_props[1];
                        else if( base_type == "armor" )
                                props = armor_props[1];
                        else
                                props = ring_props[1];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);
                }
                if( qlvl > 2 ) // 珍稀
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                props = weapon_props[0];
                        else if( base_type == "armor" )
                                props = armor_props[0];
                        else
                                props = ring_props[0];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);
                }
                }

                if( base_type == "weapon" )
                {
                        temp_status["weapon_prop"] = ([ "damage" : (ilvl+15)*qlvl*10 ]); // 基本属性-伤害
                        if( applied_prop )
                                temp_status["weapon_prop"] += applied_prop;
                }
                else if( base_type == "armor" )
                {
                        if( obj_type == "hands"
                        ||  obj_type == "finger" )
                        {
                                temp_status["armor_prop"] = ([ "armor" : 10 ]);
                                temp_status["armor_prop"]+= ([ "unarmed_damage" : (ilvl+15)*qlvl*10 ]);
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }
                        else
                        {
                                temp_status["armor_prop"] = ([ "armor" : (ilvl+15)*qlvl*2 ]); // 基本属性-保护
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }
                }
                else // 护身符
                {
                        temp_status["armor_prop"] = ([ "armor" : 10 ]);
                        if( applied_prop )
                                temp_status["armor_prop"] += applied_prop;
                }

                ob = TEMPLATE_D->create_object(filename, obj_type, temp_status);
                set("quality_level", qlvl, ob); // 品质
                set("can_sign", 1, ob); // 装备签名
                set("auto_load", 1, ob); // 下线不掉
                if( color )
                        ob->set_color(color); // 设置颜色,x_name中已经处理颜色了？
        }
        else // 掉落宝石
        {
                // 宝石分为4个等级，碎片，完好1，稀有1+1，神之1+2，宝石拥有兵器和防具以及饰品3种属性？
                // 掉落未鉴定的宝石代替
                if( ilvl <= 20 )
                        filename = "/clone/tessera/"+gems1[random(sizeof(gems1))];
                else if( ilvl <= 40 )
                        filename = "/clone/tessera/"+gems2[random(sizeof(gems2))];
                else if( ilvl <= 60 )
                        filename = "/clone/tessera/"+gems3[random(sizeof(gems3))];
                else if( ilvl <= 80 )
                        filename = "/clone/tessera/"+gems4[random(sizeof(gems4))];
                else
                        filename = "/clone/tessera/"+gems5[random(sizeof(gems5))];

                ob = new(filename);
                //file = map_array(get_dir("/inherit/template/gem/"), (: "/inherit/template/gem/" + $1 :));
                //filename = file[random(sizeof(file))];
                //ob = new(filename);
        }

        return ob;
}

public varargs void killer_reward(object killer, object victim, mapping drops)
{
        object ob, *obs;
        string *ks, key, str;
        string ob_file, ob_quality, ob_num, ob_typ;
        int i, n, value, level, team_size, mf;
        int rand, times, score;
        object where;

        if(  !mapp(drops) || !sizeof(drops) )
                return;

        where = environment(victim);
        obs = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
        team_size = sizeof(filter_array(obs, (: objectp($1) && environment($1) == environment($(killer)) :)));

        times = ACTION_D->query_action("drop_times");
        if( !times ) times = 1;
        if( killer->query_bunch() && BUNCH_D->query_bunch_efficient(killer->query_bunch(), "mf") )
                times *= 2;
        if( killer->query_family() && BUNCH_D->query_bunch_efficient(killer->query_family(), "mf") )
                times *= 2;
        mf=killer->query_all_buff("magic_find");

        if( mf > 300 ) mf = 300;
        score = 0;
        ks = keys(drops);
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];
                score += drops[ks[i]];
        }
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];
                value = drops[ks[i]];
                value += value * mf/100;

                // 掉落几率公式
                if( team_size >= 5 )
                        value = value * 220 / 100;
                else if( team_size == 4 )
                        value = value * 182 / 100;
                else if( team_size == 3 )
                        value = value * 152 / 100;
                else if( team_size == 2 )
                        value = value * 121 / 100;
                for( n=0; n<times; n++ ) {
                        //rand = random(100);
                        rand = random(score);
                        if( rand < value) {
                                str = key[0..1];
                                // 掉落阵列关键字以 F I 起头表示为掉落某个物品
                                if( str == "FI" ) {
                                        if( sscanf(key, "FI&%s", ob_file) )
                                                ob = new(ob_file);

                                }
                                // 掉落阵列关键字以 N U 起头表示为掉落某个序号的物品
                                else if( str == "NU" ) {
                                        if(  sscanf(key, "NU&%s", ob_num) )
                                                ob = create_object(ob_num);

                                }
                                // 掉落阵列关键字以 T Y 起头表示为掉落某个类型的物品
                                else if( str == "TY" ) {
                                        if(  sscanf(key, "TY&%s%d", ob_typ, level) == 2 )
                                                ob = create_dynamic(ob_typ, level, mf);

                                }
                                // 掉落阵列关键字以 M O 起头表示为掉落某个序号的套装部件
                                else if( str == "MO" ) {
                                        if( sscanf(key, "MO&%s", ob_num) )
                                                ob = create_module(ob_num);

                                }
                                // 掉落阵列关键字以 R A 起头表示为掉落某类品质的的随机物品或者随机的某级装备
                                else if( str == "RA" ) {
                                        if( sscanf(key, "RA&%s%d", ob_quality, level) == 2 ) {
                                                switch (ob_quality)
                                                {
                                                case "MODULE"   :
                                                        ob = create_module("", level);
                                                        break;
                                                case "NUMBER"   :
                                                        ob = create_object("", level);
                                                        break;
                                                case "RANDOM"   :
                                                        ob = create_dynamic("", level, mf);
                                                        break;
                                                case "RARE"     :
                                                        ob = create_dynamic("", level, 300);
                                                        break;
                                                case "EPIL"     :
                                                        ob = create_dynamic("", level, 400);
                                                        break;
                                                case "LEGEND"   :
                                                        ob = create_dynamic("", level, 500+mf/5);
                                                        break;
                                                case "MYTH"     :
                                                        ob = create_dynamic("", level, 600);
                                                        break;
                                                case "IMMORTAL" :
                                                        ob = create_dynamic("", level, 700);
                                                        break;
                                                case "SUPREME"     :
                                                        ob = create_dynamic("", level, 800);
                                                        break;
                                                default         :
                                                        break;
                                                }
                                        }
                                }
                                if( objectp(ob) ) {
                                        // HIW+treasure_level+NOR" 级"HIC"稀"NOR CYN"有"NOR"物品
/*
                                        if( query("quality_level", ob) == 3 ) // 珍稀
                                                CHANNEL_D->channel_broadcast("news",
                                                        query("name", killer) + "杀死" + victim->name() + NOR YEL"，从其身上掉出一"+query("unit", ob)+HIR" 珍"NOR RED"稀"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 4 ) // 史诗
                                        if( query("quality_level", ob) == 4 ) // 史诗
                                                CHANNEL_D->channel_broadcast("news",
                                                        query("name", killer) + "杀死" + victim->name() + NOR YEL"，从其身上掉出一"+query("unit", ob)+HIM" 史"NOR MAG"诗"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
*/
                                        if( query("quality_level", ob) == 5 ) // 传说
                                                CHANNEL_D->channel_broadcast("news",
                                                        query("name", killer) + "杀死" + victim->name() + NOR YEL"，从其身上掉出一"+query("unit", ob)+HIY" 传"NOR YEL"说"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 6 ) // 神器
                                        {
                                                CHANNEL_D->channel_broadcast("news",
                                                        //query("name", killer) + "杀死" + victim->name() + NOR YEL"，从其尸体上捡起了一"+query("unit", ob)+HIY" 神"NOR YEL"器"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                                        query("name", killer) + "杀死" + victim->name() + NOR YEL"，从其身上掉出一"+query("unit", ob)+" "+HBRED+HIW"神器"NOR+HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                                log_file("myth", sprintf("%s have get a %s(%s) of myth equip at %s.\n",killer->query_idname(),query("name",ob),query("id",ob),TIME_D->replace_ctime(time())));
                                        }
                                        else if( query("quality_level", ob) == 7 ) // 神器
                                        {
                                                CHANNEL_D->channel_broadcast("news",
                                                        HIY "数颗流星疾射而过，远古蛮荒" + (random(2) ? "气息" : "味道") + "四散飘逸...\n" + HIC + (random(2) ? "哐啷" : "噹地") + "~" + (random(2) ? "~" : "") + "~一声，" +  ob->name() + NOR + HIC + "从天而降！\n"NOR);

                                                if( ob->is_weapon() || ob->is_unarmed_weapon() )
                                                {
                                                        set("combat/MKS", 2100, ob);
                                                        set("owner/"+query("id", killer), 21000000, ob);
                                                        set("magic/imbue_ok", 1, ob);
                                                        set("magic/blood", 21000, ob);
                                                        set("enchase/flute", 9, ob);
                                                        set("enchase/SN", 87, ob);
                                                        IDENTIFY_D->identify_ultimate_ob(ob, 1);
                                                }
                                                else
                                                {
                                                        set("ultimate/37", 1, ob);
                                                        set("ultimate/39", 1, ob);
                                                        set("enchase/flute", 7, ob);
                                                        set("enchase/SN", 69, ob);
                                                        IDENTIFY_D->identify_ultimate_ob(ob, 1);
                                                }

                                                log_file("myth", sprintf("%s have get a %s(%s) of immortal equip at %s.\n",killer->query_idname(),query("name",ob),query("id",ob),TIME_D->replace_ctime(time())));
                                        }

                                        else if( query("quality_level", ob) == 8 ) // 神器
                                        {
                                                CHANNEL_D->channel_broadcast("news",
                                                        HIK "黑白两色照耀天地，太古洪荒" + (random(2) ? "气息" : "味道") + "让人窒息...\n" + HIC + (random(2) ? "哐啷" : "噹地") + "~" + (random(2) ? "~" : "") + "~一声，" +  ob->name() + NOR + HIC + "从天而降！\n"NOR);

                                                if( ob->is_weapon() || ob->is_unarmed_weapon() )
                                                {
                                                        set("combat/MKS", 2100, ob);
                                                        set("owner/"+query("id", killer), 21000000, ob);
                                                        set("magic/imbue_ok", 1, ob);
                                                        set("magic/blood", 21000, ob);
                                                        set("enchase/flute", 9, ob);
                                                        set("enchase/SN", 105, ob);
                                                        IDENTIFY_D->identify_ultimate_ob(ob, 1);
                                                }
                                                else
                                                {
                                                        set("ultimate/37", 1, ob);
                                                        set("ultimate/39", 1, ob);
                                                        set("enchase/flute", 7, ob);
                                                        set("enchase/SN", 87, ob);
                                                        IDENTIFY_D->identify_ultimate_ob(ob, 1);
                                                }

                                                log_file("myth", sprintf("%s have get a %s(%s) of immortal equip at %s.\n",killer->query_idname(),query("name",ob),query("id",ob),TIME_D->replace_ctime(time())));
                                        }

                                        message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
                                        if( query("quality_level", ob) > 2 ) {
                                                set("who_get/id", query("id", killer), ob);
                                                set("who_get/time", time() + 10, ob); // 10秒内别人都不能捡取
                                        }
                                        ob->move(where);
                                }
                        }
                }
        }
        /*
        mf=killer->query_all_buff("gold_find");
        if( random(100) < mf )
        {
                ob = new("/clone/money/gold");
                ob->set_amount(random(20)+20);
                ob->move(where);
                message_vision(HIC "叮~~一声，从$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
        }
        */

        // 特殊活动爆物品，统一调用giftd接口
        //GIFT_D->boss_drops(this_object());

        return;
}

// 特殊活动爆物品
void festival_drops(object me);
