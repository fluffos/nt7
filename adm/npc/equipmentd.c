// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// equipmentd.c

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;
#include <equipment.h>

#define EQUIP_DIR       "/inherit/template/"
#define EQUIP_LIST      CONFIG_DIR "equiplist/"

// 破防提高：我的理解是在目前破防的技术上增加一个比例。比如破防提高10％，那么如果你破防10点，就变成了11点。
// 命中加强：说实话，我看不出它有什么作用来。
// 双倍打击：在你造成伤害的基础上，加2倍，重要的一个属性。比例越高越好。
// 致命打击：非常重要的属性，造成比例打血效果。
// 比如火代表眩晕 水代表招式变慢 金代表持续伤害命中 木代表致盲
// 杀戮-攻击时有几率对当前房间所有人进行一次攻击
// 还有 5行可以是 急速 暴击 格挡（减免伤害） 精通  命中
// 急速就是增加出招的几率 暴击是双倍伤害几率 格挡是减免30%伤害几率。命中是无视闪避招架的几率 精通是perform伤害加成
// 7个防具5孔，2个兵器7孔，3个饰品3孔

// 所有属性
mapping all_props = ([
        "consistence"   : "耐久度",     // 基本属性
        "damage"        : "兵器伤害力", // 基本属性
        "unarmed_damage": "空手伤害力", // 基本属性
        "armor"         : "保护力",     // 基本属性
        "damage2"       : "改造伤害",   // weapon
        "armor2"        : "改造保护",   // armor
        "damage1"       : "附加伤害",   // weapon
        "armor1"        : "附加保护",   // armor

        "str"           : "臂力",       // weapon/armor/rings
        "int"           : "悟性",       // weapon/armor/rings
        "con"           : "根骨",       // weapon/armor/rings
        "dex"           : "身法",       // weapon/armor/rings
        "kar"           : "福缘",       // weapon/armor/rings
        "per"           : "容貌",       // rings
        "attribute"     : "所有属性",   // rings

        "max_neili"     : "内力最大值", // weapon/armor/rings
        "max_qi"        : "气血最大值", // weapon/armor/rings
        "max_jingli"    : "精力最大值", // weapon/armor/rings
        "max_jing"      : "精气最大值", // weapon/armor/rings
        "max_potential" : "潜能上限",   // weapon/armor/rings
        "max_experience": "体会上限",   // weapon/armor/rings

        "sword"         : "剑法",       // weapon
        "blade"         : "刀法",       // weapon
        "club"          : "棍法",       // weapon
        "hammer"        : "锤法",       // weapon
        "staff"         : "杖法",       // weapon
        "whip"          : "鞭法",       // weapon
        "unarmed"       : "拳脚",       // weapon
        "strike"        : "掌法",       // weapon
        "cuff"          : "拳法",       // weapon
        "hand"          : "手法",       // weapon
        "finger"        : "指法",       // weapon
        "claw"          : "爪法",       // weapon

        "attack"        : "攻击",       // weapon
        "parry"         : "招架",       // armor
        "dodge"         : "躲闪",       // armor
        "defense"       : "防御",       // armor

        "ref_neili"     : "内力恢复",   // armor/rings
        "ref_qi"        : "生命恢复",   // armor/rings
        "ref_jing"      : "精气恢复",   // armor/rings
        "suck_neili"    : "偷取内力",   // weapon/rings 命中偷取内力：命中敌人时有一定概率按伤害值的一定比率回复内力
        "suck_qi"       : "偷取生命",   // weapon/rings 命中偷取生命：命中敌人时有一定概率按伤害值的一定比率回复生命

        "gold_find"     : "获取黄金几率",       // weapon/rings
        "magic_find"    : "寻宝率(MF值)",       // weapon/rings

        // 火焰伤害，冷冻伤害，闪电伤害，毒素伤害，抗火，抗寒，抗闪电，抗毒
        "add_poison"    : "毒伤害",     // weapon
        "add_metal"     : "金伤害",     // weapon
        "add_wood"      : "木伤害",     // weapon
        "add_water"     : "水伤害",     // weapon
        "add_fire"      : "火伤害",     // weapon
        "add_earth"     : "土伤害",     // weapon
        "reduce_metal"  : "抗金",       // armor
        "reduce_wood"   : "抗木",       // armor
        "reduce_water"  : "抗水",       // armor
        "reduce_fire"   : "抗火",       // armor
        "reduce_earth"  : "抗土",       // armor
        "reduce_poison" : "抗毒",       // armor
        "avoid_poison"  : "忽视中毒",   // armor/rings

        "research_effect"       : "研究效果",   // weapon/armor/rings
        "practice_effect"       : "练习效果",   // weapon/armor/rings
        "study_effect"          : "读书效果",   // weapon/armor/rings
        "learn_effect"          : "学习效果",   // weapon/armor/rings
        "derive_effect"         : "汲取效果",   // weapon/armor/rings
        "research_times"        : "研究次数",   // weapon/armor/rings
        "learn_times"           : "学习次数",   // weapon/armor/rings
        "practice_times"        : "练习次数",   // weapon/armor/rings
        "study_times"           : "读书次数",   // weapon/armor/rings
        "derive_times"          : "汲取消耗",   // weapon/armor/rings
        // 以上都是基本属性

        "ap_power"      : "绝招攻击力",         // weapon/rings
        "dp_power"      : "绝招防御力",         // armor
        "da_power"      : "绝招伤害力",         // weapon/rings
        "avoid_defense" : "攻击无视目标防御",   // weapon/rings
        "avoid_parry"   : "攻击无视目标招架",   // weapon/rings
        "avoid_dodge"   : "攻击无视目标躲闪",   // weapon/rings
        "avoid_force"   : "攻击无视内功防御",   // weapon/rings
        "avoid_attack"  : "无视目标特殊攻击",   // armor

        //"trace"         : "擒踪",       // weapon/rings 无视对方招架
        //"escape"        : "遁隐",       // armor 躲闪几率
        //"proficient"    : "精通",       // weapon/rings 精通是perform伤害加成
        //"fatal_chance"  : "暴击",       // weapon/rings 会心一击
        //"antifatal_chance": "防暴击",   // armor

        "attack_chance" : "连击率",             // weapon/rings 急速就是增加出招的几率
        "double_damage" : "双倍伤害",           // weapon/rings 增加杀气：加一点杀气，暴击（双倍伤害）的概率增加1%
        "through_armor" : "破甲",               // weapon/rings 破甲-攻击时无视目标防具的保护力through_armor

        "qi_vs_neili"   : "受损的生命转为内力", // rings 30%的机会受损的生命x%转换为内力

        //"block_heal"    : "防止对手自疗",       // weapon
        "absorb_blood"  : "天魔附体",           // weapon/rings 召唤天魔战斗

        "add_reward"    : "获取额外奖励",       // weapon/rings
        "add_exp"       : "获取额外经验",       // weapon/rings
        "add_pot"       : "获取额外潜能",       // weapon/rings
        "add_mar"       : "获取额外体会",       // weapon/rings
        "add_force"     : "获取额外先天真气",   // weapon/rings

        // 对友方的增强buff
        // 对怪物的debuff

        "add_blind"     : "致盲",                       // weapon 终极兵器 致盲-让对手失明
        "add_freeze"    : "冰冻",                       // weapon 终极兵器 冰冻-迟缓，减缓对方攻击，攻击pfm速度降低，无任何防御，无躲闪，无招架，就是挨打
        "add_burning"   : "灼烧",                       // weapon 终极兵器 灼烧-一定时间内目标不停的减少内力和气血condition
        "add_dizziness" : "眩晕",                       // weapon 终极兵器 昏睡-眩晕，不能进行任何行动，但生命通常会加速回复，受到攻击会醒来，否则15秒内一直不动，解除战斗状态，昏睡本来就是一个混战时，先把一个敌人排除出战斗，专心对付其他人的技能
        "add_forget"    : "遗忘",                       // weapon 终极防具 遗忘-使对方忘记所有技能的绝招add_oblivion
        "add_weak"      : "虚弱",                       // weapon 终极兵器
        "add_busy"      : "忙乱",                       // weapon 终极兵器

        "avoid_blind"   : "忽视致盲",                   // armor/rings 终极防具
        "avoid_freeze"  : "忽视冰冻",                   // armor/rings 终极防具
        "avoid_burning" : "忽视灼烧",                   // armor/rings 终极防具
        "avoid_dizziness": "忽视眩晕",                  // armor/rings 终极防具
        "avoid_forget"  : "忽视遗忘",                   // armor/rings 终极兵器
        "avoid_weak"    : "忽视虚弱",                   // armor/rings 终极防具
        "avoid_busy"    : "忽视忙乱",                   // armor/rings 终极防具
        "reduce_busy"   : "化解忙乱",                   // armor/rings 终极防具

        "fatal_blow"    : "必杀",                       // weapon 终极兵器 必杀率-拥有20%的几率损伤目标的生命x%
        "slaughter"     : "杀戮",                       // weapon 杀戮-攻击时有几率对当前房间所有敌人进行一次攻击
        //"anti_fatal"    : "防必杀率",
        "add_skill"     : "所有技能",                   // weapon/rings 终极兵器
        "add_damage"    : "追加伤害",                   // weapon 终极兵器
        "reduce_damage" : "化解伤害",                   // armor 终极防具
        "full_self"     : "战神附体",                   // armor 终极防具 战神附体-气血自动恢复
        "avoid_call"    : "忽视致命",                   // armor/rings 终极防具
        "counter_damage": "伤害反射",                   // armor 终极防具 受到伤害时30%几率的伤害x%反射给对方
]);


// 宝石分为4个等级，碎片，完好1，稀有1+1，神之1+2
// 一个固定的属性(金木水火土)+1-2个随机属性

// 百分比的属性
string *percent_props = ({
        "gold_find", "magic_find", "add_metal", "add_wood", "add_water", "add_fire", "add_earth",
        "add_poison", "reduce_metal", "reduce_fire", "reduce_wood", "reduce_water", "reduce_earth",
        "reduce_poison", "avoid_poison", "research_effect", "learn_effect", "practice_effect",
        "derive_effect", "study_effect", "ap_power", "dp_power", "da_power", "avoid_attack",
        "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "trace,escape", "attack_chance",
        "double_damage", "through_armor", "qi_vs_neili", "block_heal", "absorb_blood", "add_reward",
        "add_exp", "add_pot", "add_mar", "add_force", "add_blind", "add_freeze", "add_burning", "add_dizziness",
        "add_forget", "add_weak", "add_busy", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness",
        "avoid_forget", "avoid_weak", "avoid_busy", "reduce_busy", "fatal_blow", "anti_fatal", "slaughter",
        "add_damage", "reduce_damage", "full_self", "avoid_call", "counter_damage",
});

// 宝石属性值
mapping prop_values = ([
        "damage1"       : ({ 600, 800, 1000, 1200, 1400, 1600, 2000, }),
        "armor1"        : ({ 300, 400, 500, 600, 700, 800, 900, }),
        "damage2"       : ({ 4600, 6600, 9600, 13600, 18600, 24600, 31600, 39600, 50000, }),
        "armor2"        : ({ 2200, 2900, 3700, 4600, 5600, 7700, 8900, 10200, 11500, }),

        "str,con,dex,int,kar,per"     : ({ 1, 2, 3, }),         // 200
        "attribute"     : ({ 1, 2, 3, }),       // 27

        "max_qi"        : ({ 2500, 3500, 4500, }),              // 200000
        "max_jing"      : ({ 1200, 1700, 2200, }),              // 100000
        "max_jingli"    : ({ 2500, 3500, 4500, }),              // 200000
        "max_neili"     : ({ 6000, 8000, 10000, }),             // 500000
        "max_potential,max_experience"  : ({ 30000, 40000, 50000, }),   // 2000000

        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 100, 150, 200, }),        // 500
        "defense,parry,dodge"  : ({ 50, 60, 70, }),

        "ref_jing,ref_qi"       : ({ 10, 15, 20, }),    // 1000
        "suck_qi,suck_jing,suck_neili"  : ({ 200, 300, 400, }),   // 1000

        "gold_find"     : ({ 2, 3, 4, }),       // 92
        "magic_find"    : ({ 1, 2, 3, }),       // 70

        "add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 1, 2, 3, }),       // 42
        "add_poison"    : ({ 1, 2, 3, }),       // 42
        "reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 1, 1, }), // 35
        "reduce_poison,avoid_poison"    : ({ 1, 1, 1, }),       // 44

        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 5, 10, 15, }),    // 1000
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 1, 2, 3, }), // 180

        "ap_power,dp_power,da_power"    : ({ 1, 2, 3, }),       // 70
        "avoid_attack,avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, }),       // 70

        "trace,escape"  : ({ 1, 2, 3, }),
        "attack_chance" : ({ 1, 2, 3, }),       // 70
        "double_damage,through_armor"   : ({ 1, 2, 3, }),       // 70
        "qi_vs_neili"   : ({ 5, 6, 7, }),       // 63
        "block_heal"    : ({ 3, 4, 5, }),       // 63
        "absorb_blood"  : ({ 1, 2, 3, }),       // 70

        "add_reward"    : ({ 1, 2, 3, }),       // 70
        "add_exp,add_pot,add_mar,add_force"     : ({ 2, 3, 4, }),       // 92

        "add_blind,add_freeze,add_burning,add_dizziness,add_forget,add_weak,add_busy"   : ({ 1, 2, 3 }),        // 42
        "avoid_blind,avoid_freeze,avoid_burning,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 1, 1, }), // 44
        "fatal_blow"    : ({ 3, 4, 5, }),       // 60
        "anti_fatal"    : ({ 1, 2, 3 }),
        "slaughter"     : ({ 1, 2, 3 }),        // 42
        "add_skill"     : ({ 10, 15, 20, }),    // 500
        "add_damage"    : ({ 3, 4, 5, }),       // 60
        "reduce_damage" : ({ 1, 1, 1, }),       // 35
        "full_self"     : ({ 1, 1, 1, }),       // 35
        "avoid_call"    : ({ 1, 1, 1, }),       // 44
        "counter_damage": ({ 1, 1, 1, }),       // 70
]);

// 属性强化值1-9星
mapping steady_values = ([
        "damage1,damage2"       : ({ 4600,6600,9600,13600,18600,24600,31600,39600,50000 }),
        "armor1,armor2"         : ({ 2200,2900,3700,4600,5600,7700,8900,10200,11500 }),

        "str,con,dex,int,kar,per,attribute"     : ({ 5, 7, 9, 11, 14, 17, 20, 25, 30, }),

        "max_qi"        : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_jing"      : ({ 500, 1000, 1500, 2500, 3500, 4500, 6000, 7500, 10000, }),
        "max_jingli"    : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_neili"     : ({ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 100000, }),
        "max_potential,max_experience"  : ({ 200000, 400000, 600000, 1000000, 1500000, 2000000, 3000000, 4000000, 6000000, }),

        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 20, 30, 40, 60, 80, 110, 150, 200 }),
        "dodge,parry,defense"   : ({ 10, 15, 20, 25, 30, 35, 40, 45, 60 }),

        "ref_jing,ref_qi"       : ({ 60, 70, 80, 100, 120, 140, 160, 180, 200, }),
        "suck_qi,suck_jing,suck_neili"  : ({ 20, 40, 60, 100, 150, 200, 250, 300, 400, }),

        "gold_find"     : ({ 2, 4, 6, 8, 10, 12, 14, 16, 20, }),
        "magic_find"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),

        "add_poison,add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 6, 8, 10, 13, 16, 19, 22, 25, 28, }),
        "reduce_poison,avoid_poison,reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 2, 3, 4, 5, 5, 5, 5, 5, }),

        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 10, 25, 20, 25, 30, 35, 40, 45, 50 }),
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 8, 10, 12, 15, 18, 21, 25, 35, 40, }),

        "ap_power,da_power"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "dp_power"      : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "avoid_attack"  : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),

        "trace,escape"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "attack_chance" : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "double_damage,through_armor"   :  ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "qi_vs_neili"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "block_heal"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "absorb_blood"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),

        "add_reward"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "add_exp,add_pot,add_mar,add_force"     : ({ 5, 7, 9, 12, 15, 18, 22, 26, 30, }),

        "add_blind,add_freeze,add_burning,add_dizziness,add_forget,add_weak,add_busy"   : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "avoid_blind,avoid_freeze,avoid_burning,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "fatal_blow"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "anti_fatal"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "slaughter"     : ({ 6, 8, 10, 13, 16, 19, 22, 25, 29, }),
        "add_skill"     : ({ 20, 30, 40, 60, 80, 110, 150, 250 }),
        "add_damage"    : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "reduce_damage" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "full_self"     : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_call"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "counter_damage": ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
]);

// 装备的品级有6级，前2个品级属性没有特殊，从稀有（第三个）品级开始有特殊属性
// 宝石的等级有3级，宝石的属性应该和装备前2个品级的属性一样
// qlvl1只有基本属性，qlvl2才有宝石属性，qlvl3拥有宝石属性，qlvl4拥有史诗属性，qlvl5拥有传说属性，qlvl6拥有神奇属性
mixed weapon_props = ({
        ({ "damage1", "int", "str", "con", "dex", "kar", "skill", "attack",
           "suck_neili", "suck_qi", "gold_find", "magic_find", "add_poison",
           "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect",
           "derive_effect", "study_effect", "ap_power", "da_power", "avoid_defense",
           "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance", "double_damage",
           "through_armor", "absorb_blood", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "add_blind", "add_freeze", "add_burning", "add_dizziness", "add_weak",
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage",
           "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential", "max_experience",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "attack", "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "suck_qi",
           "suck_neili", "avoid_force", "add_exp", "add_pot", "add_mar", "add_force", "skill", // skill特殊处理
        }),
        ({ "through_armor", "slaughter", "double_damage", "add_reward", "absorb_blood",
           "add_blind", "suck_qi", "suck_neili", "add_exp", "add_pot", "add_mar", "add_force",
           "research_effect", "practice_effect", "study_effect", "derive_effect", "add_reward",
           "ap_power", "da_power",
        }),
        ({ "add_reward", "add_blind", "add_freeze", "add_burning", "add_dizziness", "add_weak",
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage",
           "research_effect", "practice_effect", "derive_effect", "add_reward",
           "ap_power", "da_power", "through_armor",
        }),
});

mixed armor_props = ({
        ({ "armor1", "int", "str", "con", "dex", "kar", "max_neili", "max_qi", "max_jing",
           "max_jingli", "max_potential", "max_experience", "parry", "dodge", "defense",
           "ref_neili", "ref_jing", "ref_qi", "reduce_poison", "avoid_poison", "research_times",
           "learn_times", "practice_times", "derive_times", "study_times", "research_effect",
           "learn_effect", "practice_effect", "derive_effect", "study_effect", "dp_power", "avoid_attack",
           "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_call", "counter_damage",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "reduce_poison", "avoid_poison", "max_qi", "max_jing",
        }),
        ({ "ref_neili", "ref_jing", "ref_qi", "avoid_attack", "dp_power", "avoid_blind", "avoid_call",
           "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
        }),
        ({ "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_call", "counter_damage",
           "research_effect", "practice_effect", "derive_effect", "dp_power",
        }),
});

// 项链amulet、戒指ring、护身符属性charm
mixed ring_props = ({
        ({ "per", "attribute", "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential",
           "max_experience", "ref_neili", "ref_jing", "ref_qi", "suck_neili", "suck_qi", "gold_find",
           "magic_find", "avoid_poison", "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect", "derive_effect", "study_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance",
           "double_damage", "through_armor", "qi_vs_neili", "absorb_blood", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "add_skill", "avoid_call",
        }),
        ({ "attribute", "gold_find", "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect",
           "reduce_poison", "avoid_poison", "max_qi", "max_jing", "add_exp", "add_pot", "add_mar", "add_force",
        }),
        ({ "magic_find", "suck_neili", "suck_qi" "qi_vs_neili", "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "attack_chance", "absorb_blood",
           "add_exp", "add_pot", "add_mar", "add_force", "add_reward",
        }),
        ({ "add_reward", "avoid_blind", "avoid_freeze", "avoid_burning", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "add_skill", "avoid_call", "magic_find", "qi_vs_neili", "double_damage", "through_armor",
           "research_effect", "practice_effect", "derive_effect","add_exp", "add_pot", "add_mar", "add_force", "add_reward",
        }),
});

// 套化的兵器属性
string *suit_weapon_props = ({
        "double_damage", "avoid_forget", "add_damage", "add_skill", "fatal_blow", "add_busy", "add_weak", "add_dizziness",
        "add_burning", "add_freeze",

});
// 套化的防具属性
string *suit_armor_props = ({
        "reduce_busy", "avoid_busy", "avoid_weak", "avoid_dizziness", "avoid_burning",
        "counter_damage", "add_forget", "avoid_call", "full_self", "reduce_damage",
});
// 套化的护身符属性
string *suit_ring_props = ({
        "magic_find", "add_exp", "add_pot", "add_mar", "add_force", "suck_neili", "suck_qi",
        "add_reward", "full_self", "avoid_busy", "avoid_forget", "avoid_call", "antifatal_chance",
});

void create()
{
        seteuid(getuid());
        set("name", "装备精灵");
        set("id", "equipmentd");
}

// 为属性名称匹配中文
varargs string chinese(string prop, int value)
{
        string desc;

        if( !undefinedp(all_props[prop]) )
                desc = all_props[prop];
        else
                desc = to_chinese(prop);

        if( !value ) return desc;

        if( member_array(prop, percent_props) != -1 )
                desc = sprintf(HIB "%s %s%d%s" NOR, desc,
                               value > 0 ? "+" : "-", abs(value), "%");
        else
                desc = sprintf(HIB "%s %s%d" NOR, desc,
                               value > 0 ? "+" : "-", abs(value));

        return desc;
}

// 获取装备部件的属性
varargs int query_prop_value(string prop, int ilvl, int s)
{
        int i, j, flag;
        int *value;
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

                return value[ilvl-1];
        }
        return value[random(sizeof(value))];
}

// 装备绿化时候获得的属性
mapping apply_ultimate_prop(object ob, string type, int ilvl)
{
        string *props;
        string prop;
        mapping apply;
        int value, n;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
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

                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 生成宝石属性
varargs mapping apply_gem_prop(string type, int ilvl, int n)
{
        string *props;
        string prop;
        mapping apply;
        int value;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "hands"
        ||  type == "finger" )
                props = weapon_props[0]; // 获取对应的品质属性
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // 护身符·左
        ||  type == "myheart2"  // 护身符·右
        ||  type == "neck" )
                props = ring_props[0];
        else
                props = armor_props[0];

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
                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 设置装备属性
mapping apply_props(string type, int ilvl, int n)
{
        mapping applied_prop;
        mapping enchase_prop;
        mapping data = ([]);
        string *apply;
        mixed insert;
        int i, j;

        applied_prop = ([]);
        insert = ([]);

        if( !n ) return data;
        for( i=1; i<=n; i++ ) // 凹槽数
        {
                enchase_prop = copy(apply_gem_prop(type, ilvl));
                apply = keys(enchase_prop);
                for( j=0; j<sizeof(apply); j++ )
                {
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[apply[j]]) )
                                applied_prop[apply[j]] = enchase_prop[apply[j]];
                        else
                                applied_prop[apply[j]] += enchase_prop[apply[j]];
                }
                insert[to_string(i)] = (["name" : HIM"玄石"NOR, "id" : "magic stone", "apply_prop" : enchase_prop]);
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
        mapping temp_map, temp_map2;

        temp_status = ([ ]);

        // 解析insert
        if( sscanf(mark, "%s<insert>%s</insert>", mark, temp_str2) == 2 )
        {
                while (sscanf(temp_str2, "%*s[%s]%s[/%s]%s", key, temp_str, key, temp_str2) > 3)
                {
                        temp_map = ([ ]);
                        temp_map2 = ([ ]);
                        temp_arr = explode(temp_str, "\n");
                        if( sizeof(temp_arr) < 2 ) {
                                if( atoi(temp_str) )
                                        temp_map2[key] = atoi(temp_str);
                                else
                                        temp_map2[key] = temp_str;

                        } else {
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
                                temp_map2[key] = temp_map;
                        }
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

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 1, temp_function);
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

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 1, temp_function);
                set("mod_mark", num, ob);
                set("can_sign", 1, ob); // 装备签名
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
        mapping insert;
        string *all_id, *types;
        string id;
        string *file;
        string color, filename;
        string base_type;
        object ob;
        int qlvl;
        int rate, n, uf, sf, rf;
        string prop, *props;

        if( !ilvl || ilvl < 1 )
                return 0;

        if( !obj_type || obj_type == "" ) { // 随机生成装备种类或宝石
                rate = random(100);
                if( rate < 30 ) obj_type = "weapon";
                else if( rate < 70 ) obj_type = "armor";
                else if( rate < 90 ) obj_type = "rings";
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
        rate = random(100);
        if( rate < 40 ) data["str"] = ilvl*2 + random(ilvl);
        else if( rate < 60 ) data["con"] = ilvl*2 + random(ilvl);
        else if( rate < 80 ) data["dex"] = ilvl*2 + random(ilvl);
        else data["int"] = ilvl*2 + random(ilvl);

        data["level"] = ilvl;
        temp_status["require"] = copy(data); // 设置装备要求

        if( base_type != "gem" ) // 掉落装备，非宝石
        {
                // 凹槽数量：普通0、精制1、珍稀2、史诗3、传说4、神器5
                // 武器6孔，防具4孔，护身符3孔，盾牌4孔

                if( !mf ) mf = 0;

                if( mf <= 10 )
                        uf = sf = rf = mf;

                uf = mf*20/(mf+20);  // 传说品级
                sf = mf*200/(mf+200);  // 史诗品级
                rf = mf*600/(mf+600);  // 珍稀品级

                rate = random(100);
                if( rate < uf )
                {
                        if( base_type == "weapon" )
                                n = 4;       // 凹槽数量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 护身符
                                n = 3;
                        qlvl = 5;
                        color = HIY; // 传说
                } else
                if( rate < sf )
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
                data = ([]);
                if( n > 1 )
                        n = random(n); // 随机凹槽数
                if( n > 0 )
                {
                        data = apply_props(obj_type, ilvl/10, n);
                        data["flute"] = n; //socket
                        data["used"] = n;
                        insert = data["insert"];
                        map_delete(data, "insert");
                        temp_status["enchase"] = copy(data); // 设置装备属性 buff/enchase ?
                        temp_status["insert"] = insert;      // 插槽宝石属性
                }
                if( qlvl > 5 ) // 神器
                {
                        if( base_type == "weapon" )          // 兵器、防具、护身符
                                props = weapon_props[3];
                        else if( base_type == "armor" )
                                props = armor_props[3];
                        else
                                props = ring_props[3];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);
                }
                if( qlvl > 4 ) // 传说
                {
                        if( base_type == "weapon" )
                                props = weapon_props[2];
                        else if( base_type == "armor" )
                                props = armor_props[2];
                        else
                                props = ring_props[2];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);
                }
                if( qlvl > 3 ) // 史诗
                {
                        if( base_type == "weapon" )
                                props = weapon_props[1];
                        else if( base_type == "armor" )
                                props = armor_props[1];
                        else
                                props = ring_props[1];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);
                }
                if( qlvl > 2 ) // 珍稀
                {
                        if( base_type == "weapon" )
                                props = weapon_props[0];
                        else if( base_type == "armor" )
                                props = armor_props[0];
                        else
                                props = ring_props[0];

                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl);
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

                ob = TEMPLATE_D->create_object(filename, obj_type, temp_status, 1);
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
                ob = new("/clone/tessera/gem.c");
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
        int i, n, value, level, team_size, mf, uf, sf, rf;
        int rand, times, score;
        object where;

        if(  !mapp(drops) || !sizeof(drops) )
                return;

        where = environment(victim);
        obs = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
        team_size = sizeof(filter_array(obs, (: objectp($1) && environment($1) == environment($(killer)) :)));

        times = ACTION_D->query_action("boss_reward");
        if( !times ) times = ACTION_D->query_action("fuben_reward");
        if( !times ) times = 1;
        //if( killer->is_vip() ) times = times * 2;
        mf=query_temp("apply/magic_find", killer);
        if( mf <= 10 )
                uf = sf = rf = mf;

        uf = mf*250/(mf+250);  // 传说品级
        sf = mf*500/(mf+500);  // 史诗品级
        rf = mf*600/(mf+600);  // 珍稀品级

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
                                                default         :
                                                        break;
                                                }
                                        }
                                }
                                if( objectp(ob) ) {
                                        // HIW+treasure_level+NOR" 级"HIC"稀"NOR CYN"有"NOR"物品
                                        if( query("quality_level", ob) == 3 ) // 珍稀
                                                CHANNEL_D->channel_broadcast("news",
                                                        killer->name() + "杀死" + victim->name() + NOR YEL"，从其尸体上捡起了一"+query("unit", ob)+HIR" 珍"NOR RED"稀"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 4 ) // 史诗
                                                CHANNEL_D->channel_broadcast("news",
                                                        killer->name() + "杀死" + victim->name() + NOR YEL"，从其尸体上捡起了一"+query("unit", ob)+HIM" 史"NOR MAG"诗"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 5 ) // 传说
                                                CHANNEL_D->channel_broadcast("news",
                                                        killer->name() + "杀死" + victim->name() + NOR YEL"，从其尸体上捡起了一"+query("unit", ob)+HIY" 传"NOR YEL"说"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 6 ) // 神器
                                                CHANNEL_D->channel_broadcast("news",
                                                        killer->name() + "杀死" + victim->name() + NOR YEL"，从其尸体上捡起了一"+query("unit", ob)+HIY" 神"NOR YEL"器"HIW"级 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        //message_vision(HIC "当~~一声，从$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
                                        ob->move(killer);
                                }
                        }
                }
        }
        mf=query_temp("apply/gold_find", killer);
        if( random(100) < mf )
        {
                ob = new("/clone/money/gold");
                ob->set_amount(random(20)+20);
                ob->move(where);
                message_vision(HIC "叮~~一声，从$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
        }

        // 特殊活动爆物品，统一调用giftd接口
        //GIFT_D->boss_drops(this_object());

        return;
}
