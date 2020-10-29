// This program is a part of NT MudLIB

#include <ansi.h>

// "str","角色力量值提高１点\t",500,

mapping max_ability = ([
        "str"   : 500,
        "int"   : 500,
        "con"   : 500,
        "dex"   : 500,
        "kar"   : 70,
        "max_qi"    : 10,
        "max_jing"  : 10,
        "max_neili" : 10,
        "max_jingli": 10,
        "qi_recover": 20,
        "jing_recover" : 20,
        "neili_recover": 20,
        "attack": 10,
        "dodge" : 10,
        "parry" : 10,
        "double_damage": 10,
        "avoid_poison" : 10,
        "avoid_busy": 10,
        "avoid_weak": 10,
        "reduce_damage": 10,
]);

// 基本能力
string *bas_ability = ({
        "str",
        "int",
        "con",
        "dex",
        "kar",
        "max_qi",
        "max_jing",
        "max_neili",
        "max_jingli",
        "qi_recover",
        "jing_recover",
        "neili_recover",
        "attack",
        "dodge",
        "parry",
        "double_damage",
        "avoid_poison",
        "avoid_busy",
        "avoid_weak",
        "reduce_damage",
});

string *bas_ability_info = ({
        "角色力量值提高１点\t","角色才智值提高１点\t","角色体质值提高１点\t",
        "角色身法值提高１点\t","角色运气值提高１点\t","最大气血值提高１％\t",
        "最大精气值提高１％\t","最大内力值提高１％\t","最大精力值提高１％\t",
        "恢复气血提高５０点\t","恢复精气提高５０点\t","恢复内力提高５０点\t",
        "直接命中机会增１％\t","直接闪避机会增１％\t","直接招架机会增１％\t",
        "触发暴击机会增１％\t","免疫毒素机会增１％\t","免疫忙乱机会增１％\t",
        "免疫虚弱机会增１％\t","化解伤害比例增１％\t",
});

mapping bas_ability_pot = ([
        "attack":       2,
        "dodge":        2,
        "parry":        2,
        "double_damage":3,
        "avoid_poison": 3,
        "avoid_busy":   3,
        "avoid_weak":   3,
        "reduce_damage":3,
]);

mapping fam_ability_pot = ([
        //5
]);

mapping fam_ability_data = ([
        //5
]);

mapping fam_ability = ([
        "少林派": ({
                "dodgeup-shaolin-shenfa", "parryup-jingang-buhuaiti", "cd-jgbht-protect", "cd-yjj-buddha", "ap_power-ryb-shang",
                "da_power-ryb-shang", "ap_power-lhj-lunhui", "da_power-lhj-lunhui", "cd-lhj-lunhui",
        }),

        "武当派": ({
                "dodgeup-tiyunzong", "parryup-taiji-quan", "parryup-taiji-jian", "ap_power-tjq-tu", "da_power-tjq-tu", "cd-tjq-tu",
                "ap_power-tjq-zhen", "da_power-tjq-zhen", "ap_power-tjj-jian", "da_power-tjj-jian", "cd-tjj-jian",
        }),

        "峨嵋派": ({
                "dodgeup-zhutian-bu", "parryup-piaoxue-zhang", "ap_power-pxz-zhao", "parryup-huifeng-jian", "ap_power-hfj-jue", "da_power-hfj-jue", "cd-ljz-niepan"
        }),

        "华山派": ({
                "powerup-zxsg-ziqi", "dodgeup-feiyan-huixiang", "parryup-lonely-sword", "ap_power-dgjj-hun", "da_power-dgjj-hun", "fatal_blow-dgjj-hun",
                "cd-dgjj-hun", "ap_power-dgjj-xiao", "da_power-dgjj-xiao", "fatal_blow-dgjj-xiao",
        }),

        "桃花岛": ({
                "dodgeup-luoying-shenfa", "parryup-yuxiao-jianfa", "parryup-tanzhi-shentong", "ap_power-yxjf-bihai", "da_power-yxjf-bihai",
                "ap_power-tzst-dian", "da_power-tzst-dian", "cd-tzst-dian", "ap_power-tzst-zhuan", "da_power-tzst-zhuan", "cd-tzst-lingxi",
        }),

        "欧阳世家":({
                "dodgeup-chanchu-bufa", "parryup-hamagong", "powerup-hmg-reserve", "ap_power-hmg-zhen", "da_power-hmg-zhen",
                "cd-hmg-nizhuan",
        }),

        "段氏皇族":({
                "full-krcg-kurong", "dodgeup-tiannan-bu", "parryup-six-finger", "ap_power-lmsj-gz", "da_power-lmsj-gz",
                "ap_power-lmsj-tian", "da_power-lmsj-tian", "cd-lmsj-tian", "ap_power-yyz-die", "da_power-yyz-die",
                "ap_power-yyz-jian", "da_power-yyz-jian",
        }),

        "丐帮"  : ({
                "dodgeup-feiyan-zoubi", "parryup-dragon-strike", "ap_power-dgb-tian", "ap_power-xlsbz-hui", "da_power-xlsbz-hui",
                "double_damage-xlsbz-hui","ap_power-xlsbz-long", "da_power-xlsbz-long", "double_damage-xlsbz-long", "cd-xlsbz-long",
        }),

        "全真教": ({
                "dodgeup-jinyan-gong", "parryup-kongming-quan", "ap_power-hubo", "ap_power-xtg-xian", "da_power-xtg-xian", "cd-xtg-xian",
                "ap_power-xtg-jian", "da_power-xtg-jian", "ap_power-xtg-shen", "da_power-xtg-shen",
        }),

        "古墓派": ({
                "powerup-nhkt-haixiao", "dodgeup-yunv-shenfa", "parryup-xuantie-jian", "parryup-sad-strike", "parryup-yunv-jian", "ap_power-hubo",
                "ap_power-arxhz-tuo", "da_power-arxhz-tuo", "cd-arxhz-tuo", "cd-ynxf-wuzhi",
        }),

        "明教"  : ({
                "dodgeup-qingfu-shenfa", "parryup-qiankun-danuoyi", "ap_power-jysg-ri", "da_power-jysg-ri", "cd-jysg-ri",
                "ap_power-qkdny-yi", "da_power-qkdny-yi", "cd-qkdny-nuozhuan", "power-qkdny-nuozhuan", "ap_power-shl-can",
        }),

        "魔教"  : ({
                "powerup-cykzj-huaxue", "dodgeup-jiutian-xiaoyaobu", "parryup-moshen-zhenshen", "ap_power-tymyd-mingyue", "da_power-tymyd-mingyue",
                "ap_power-yywd-ting", "da_power-yywd-ting", "fatal_blow-yywd-ting", "ap_power-yywd-dao", "da_power-yywd-dao",
                "fatal_blow-yywd-dao", "cd-yywd-ting", "cd-yywd-dao",
        }),

        "日月神教":({
                "powerup-rygh-richu", "dodgeup-pixie-jian", "parryup-pixie-jian", "add-khxf-sneaky", "ap_power-pxj-you",
                "da_power-pxj-you", "powerup-pxj-jian",
        }),

        "星宿派": ({
                "powerup_hgdf-suck", "dodgeup-feixing-shu", "parryup-chousui-zhang", "ap_power-csz-shi", "da_power-csz-shi", "ap_power-csz-tao",
                "da_power-csz-tao", "cd-freezing-hanmo",
        }),

        "逍遥派": ({
                "powerup-bmsg-suck", "dodgeup-lingbo-weibu", "parryup-liuyang-zhang", "parryup-zhemei-shou", "cd-lbwb-shen", "ap_power-lyz-hui",
                "da_power-lyz-hui", "ap_power-zms-hua", "da_power-zms-hua",
        }),

        "灵鹫宫": ({
                "dodgeup-yueying-wubu", "parryup-liuyang-zhang", "ap_power-lyz-zhen", "da_power-lyz-zhen", "ap_power-lyz-zun", "da_power-lyz-zun",
                "cd-bhg-protect",
        }),

        "神龙教": ({
                "dodgeup-yixing-bufa", "parryup-shedao-qigong", "ap_power-bssl-zhou", "ap_power-sdqg-xian", "da_power-sdqg-xian",
                "ap_power-sdqg-hou", "da_power-sdqg-hou",
        }),

        "血刀门": ({
                "powerup-xhmg-jixue", "dodgeup-shenkong-xing", "parryup-xuedao-daofa", "ap_power-xddf-xue", "da_power-xddf-xue",
                "ap_power-szj-ying", "da_power-szj-ying", "ap_power-xddf-huan", "da_power-xddf-huan", "cd-xddf-huan",
        }),

        "雪山寺": ({
                "dodgeup-shenkong-xing", "parryup-longxiang-gong", "ap_power-lxbrg-zhen", "da_power-lxbrz-zhen", "ap_power-ryl-lian",
                "ap_power-lxbrg-longxiang", "da_power-lxbrg-longxiang", "cd-lxbrg-longxiang",
        }),

        "密宗": ({
                "powerup-xhmg-jixue", "dodgeup-shenkong-xing", "parryup-xuedao-daofa", "ap_power-xddf-xue", "da_power-xddf-xue",
                "ap_power-szj-ying", "da_power-szj-ying", "ap_power-xddf-huan", "da_power-xddf-huan", "cd-xddf-huan",
                "dodgeup-shenkong-xing", "parryup-longxiang-gong", "ap_power-lxbrg-zhen", "da_power-lxbrz-zhen", "ap_power-ryl-lian",
                "ap_power-lxbrg-longxiang", "da_power-lxbrg-longxiang", "cd-lxbrg-longxiang",
        }),

        "五毒教": ({
                "dodgeup-wudu-yanluobu", "ap_power-wdsg-arrow", "parryup-qianzhu-wandushou", "ap_power-qzwds-chuan", "da_power-qzwds-chuan",
                "ap_power-qzwds-qzwd", "da_power-qzwds-qzwd", "cd-qzwds-qzwd", 
                "cd-bdjcg-summon", "max-bdjcg-summon", "chance-bdjcg-protect", "n-bdjcg-grow1", "n--bdjcg-grow2", 
                "cd-bdjcg-wpin", "ap_power-bdjcg-wpin", "da_power-bdjcg-wpin", "da_power-bdjcg-wpin2", "da_power-bdjcg-wpin3",
                "chance-bdjcg-cpin", "hp-bdjcg", "reduce_damage-bdjcg", "avoid_die-bdjcg",
        }),

        "关外胡家":({
                "dodgeup-sixiang-bufa", "parryup-daojian-guizhen", "defdown-lengyue", "ap_power-hjdf-pi", "da_power-hjdf-pi",
                "ap_power-djgz-tian", "da_power-djgz-tian", "ap_power-djgz-jiu", "da_power-djgz-jiu", "cd-djgz-jiu",
                "power-msqd-despel",
        }),

        "慕容世家":({
                "dodgeup-beidou-xianzong", "parryup-douzhuan-xingyi", "ap_power-chz-canhe", "da_power-chz-canhe",
                "ap_power-dzxy-yi", "cd-dzxy-yi",
        }),

        "唐门世家":({
                "dodgeup-qiulin-sheye", "parryup-boyun-suowu", "ap_power-tmaq-san", "da_power-tmaq-san",
                "ap_power-tmaq-hua", "da_power-tmaq-hua", "ap_power-tmaq-shijie", "cd-tmaq-shijie",
        }),
]);

mapping fam_ability_info = ([
// 命中，伤害，躲闪，招架，减CD, 特殊效果时间持续，暴击几率，致命一击
// 冰冻效果，忙乱，遗忘，虚弱
        "少林派": ({
                "少林身法闪避机会＋５％\t",
                "金刚不坏体招架机会＋５％",
                "金刚不坏CD时间减少５秒\t",
                "佛光普照CD时间减少５秒\t",
                "伤字诀命中机会＋５％\t",
                "伤字诀伤害力＋５％\t",
                "六道轮回命中机会＋５％\t",
                "六道轮回伤害力＋５％\t",
                "六道轮回CD时间减少５秒\t",
        }),

        "武当派": ({
                "梯云纵闪避机会＋５％\t",
                "太极拳招架机会＋５％\t",
                "太极剑招架机会＋５％\t",
                "太极图命中机会＋５％\t",
                "太极图伤害力＋５％\t",
                "太极图CD时间减少５秒\t",
                "真武除邪命中机会＋５％\t",
                "真武除邪伤害力＋５％\t",
                "太極劍意命中机会＋５％\t",
                "太極劍意伤害力＋５％\t",
                "太極劍意CD时间减少５秒\t",
        }),

        "峨嵋派"  : ({
                "诸天化身步闪避机会＋５％",
                "飘雪穿云掌招架机会＋５％",
                "佛光普照命中机会＋５％\t",
                "回风拂柳剑招架机会＋５％",
                "绝剑命中机会＋５％\t",
                "绝剑伤害力＋５％\t",
                "凤凰涅磐CD时间减少５秒\t",
        }),

        "华山派": ({
                "紫气东来加持伤害效果＋５％",
                "飞燕回翔闪避机会＋５％\t",
                "独孤九剑无招特防机会＋５％",
                "剑魂命中机会＋５％\t",
                "剑魂伤害力＋５％\t",
                "剑魂追加致命一击触发几率＋５％",
                "剑魂CD时间减少５秒\t",
                "沧海笑命中机会＋５％\t",
                "沧海笑伤害力＋５％\t",
                "沧海笑追加致命一击触发几率＋５％",
        }),

        "桃花岛": ({
                "落英身法闪避机会＋５％\t",
                "玉箫剑法招架机会＋５％\t",
                "弹指神通招架机会＋５％\t",
                "碧海潮生按玉箫命中机会＋５％",
                "碧海潮生按玉箫伤害力＋５％",
                "隔空点穴命中机会＋５％\t",
                "隔空点穴伤害力＋５％\t",
                "隔空点穴CD时间减少５秒\t",
                "转乾坤命中机会＋５％\t",
                "转乾坤伤害力＋５％\t",
                "灵犀一指CD时间减少５秒\t",
        }),

        "欧阳世家": ({
                "蟾蜍步法闪避机会＋５％\t",
                "蛤蟆功招架机会＋５％\t",
                "经脉倒转加持攻防效果＋５％",
                "蟾震九天命中机会＋５％\t",
                "蟾震九天命伤害力＋５％\t",
                "逆转九阴CD时间减少５秒\t",
        }),

        "段氏皇族": ({
                "枯荣心法的回血效果＋５％",
                "天南步法闪避机会＋５％\t",
                "六脉神剑招架机会＋５％\t",
                "六脉归宗命中机会＋５％\t",
                "六脉归宗伤害力＋５％\t",
                "天脉神剑命中机会＋５％\t",
                "天脉神剑伤害力＋５％\t",
                "天脉神剑CD时间减少５秒\t",
                "阳关三叠命中机会＋５％\t",
                "阳关三叠伤害力＋５％\t",
                "先天功乾阳剑气命中机会＋５％",
                "先天功乾阳剑气伤害力＋５％",
        }),

        "丐帮"  : ({
                "飞檐走壁闪避机会＋５％\t",
                "降龙十八掌招架机会＋５％",
                "天下无狗命中机会＋５％\t",
                "亢龙有悔命中机会＋５％\t",
                "亢龙有悔伤害力＋５％\t",
                "亢龙有悔追加暴击触发几率＋５％",
                "龍嘯九天命中机会＋５％\t",
                "龍嘯九天伤害力＋５％\t",
                "龍嘯九天追加暴击触发几率＋５％",
                "龍嘯九天CD时间减少５秒\t",
        }),

        "全真教": ({
                "金雁功闪避机会＋５％\t",
                "空明拳招架机会＋５％\t",
                "左右互博的命中＋５％\t",
                "先天罡气命中机会＋５％\t",
                "先天罡气伤害力＋５％\t",
                "先天罡气CD时间减少５秒\t",
                "先天功乾阳剑气命中机会＋５％",
                "先天功乾阳剑气伤害力＋５％",
                "纯阳神通功命中机会＋５％",
                "纯阳神通功伤害力＋５％\t",
        }),

        "古墓派": ({
                "海天一啸效果＋５％\t",
                "玉女身法闪避机会＋５％\t",
                "玄铁剑法招架机会＋５％\t",
                "黯然销魂掌招架机会＋５％",
                "玉女剑法招架机会＋５％\t",
                "左右互博的命中＋５％\t",
                "拖泥带水命中机会＋５％\t",
                "拖泥带水伤害力＋５％\t",
                "拖泥带水CD时间减少５秒\t",
                "所向无滞CD时间减少５秒\t",
        }),

        "明教"  : ({
                "青蝠身法闪避机会＋５％\t",
                "乾坤大挪移招架机会＋５％",
                "魔光日无极命中机会＋５％",
                "魔光日无极伤害力＋５％\t",
                "魔光日无极CD时间减少５秒",
                "大挪移命中机会＋５％\t",
                "大挪移伤害力＋５％\t",
                "挪转乾坤CD时间减少５秒\t",
                "挪转乾坤反伤效果＋５％\t",
                "残血令命中机会＋５％\t",
        }),

        "魔教"  : ({
                "神刀化血加持伤害效果＋５％",
                "九天逍遥步闪避机会＋５％",
                "魔神真身招架机会＋５％\t",
                "天涯明月命中机会＋５％\t",
                "天涯明月伤害力＋５％\t",
                "小楼一夜听春雨命中机会＋５％",
                "小楼一夜听春雨伤害力＋５％",
                "小楼一夜听春雨追加致命一击触发几率＋５％",
                "刀至上-至上刀命中机会＋５％",
                "刀至上-至上刀伤害力＋５％",
                "刀至上-至上刀追加致命一击触发几率＋５％",
                "小楼一夜听春雨群伤CD时间减少５秒",
                "刀至上-至上刀CD时间减少５秒",
        }),

        "日月神教":({
                "日出东方加持伤害效果＋５％",
                "辟邪剑闪避机会＋５％\t",
                "辟邪剑招架机会＋５％\t",
                "鬼隐时间＋５秒\t",
                "幽冥一击命中机会＋５％\t",
                "幽冥一击伤害力＋５％\t",
                "辟邪劍影命中及伤害＋５％",
        }),

        "星宿派": ({
                "化工大法吸取内力效果＋５％",
                "飞星术闪避机会＋５％\t",
                "抽髓掌招架机会＋５％\t",
                "腐尸毒命中机会＋５％\t",
                "腐尸毒伤害力＋５％\t",
                "碧焰滔天命中机会＋５％\t",
                "碧焰滔天伤害力＋５％\t",
                "寒魔玄力CD时间减少５秒\t",
        }),

        "逍遥派": ({
                "北冥神功吸取内力效果＋５％",
                "凌波微步闪避机会＋５％\t",
                "天山六阳掌招架机会＋５％",
                "折梅手招架机会＋５％\t",
                "神光离合CD时间减少５秒\t",
                "灰飞湮灭命中机会＋５％\t",
                "灰飞湮灭伤害力＋５％\t",
                "化妖功命中机会＋５％\t",
                "化妖功伤害力＋５％\t",
        }),

        "灵鹫宫": ({
                "月影舞步闪避机会＋５％\t",
                "天山六阳掌招架机会＋５％",
                "一掌震天命中机会＋５％\t",
                "一掌震天伤害力＋５％\t",
                "八荒独尊掌命中机会＋５％",
                "八荒独尊掌伤害力＋５％\t",
                "八荒独尊掌CD时间减少５秒",
                "唯我独尊CD时间减少５秒\t",
        }),

        "神龙教": ({
                "意形步法闪避机会＋５％\t",
                "蛇岛奇功招架机会＋５％\t",
                "咒法命中机会＋５％\t",
                "神龙再现命中机会＋５％\t",
                "神龙再现伤害力＋５％\t",
                "吼字决命中机会＋５％\t",
                "吼字决伤害力＋５％\t",
        }),

        "血刀门": ({
                "祭血大法加持伤害效果＋５％",
                "身空行闪避机会＋５％\t",
                "血刀刀法招架机会＋５％\t",
                "噬血穹苍命中机会＋５％\t",
                "噬血穹苍伤害力＋５％\t",
                "无影神拳命中机会＋５％\t",
                "无影神拳伤害力＋５％\t",
                "我必还之命中机会＋５％\t",
                "我必还之伤害力＋５％\t",
                "我必还之CD时间减少５秒\t",
        }),

        "雪山寺": ({
                "身空行闪避机会＋５％\t",
                "龙象般若功招架机会＋５％",
                "真·般若极命中机会＋５％",
                "真·般若极伤害力＋５％\t",
                "五轮连转命中和伤害＋５％",
                "十龙十象命中机会＋５％\t",
                "十龙十象伤害力＋５％\t",
                "十龙十象CD时间减少５秒\t",
        }),

        "密宗": ({
                "祭血大法加持伤害效果＋５％",
                "身空行闪避机会＋５％\t",
                "血刀刀法招架机会＋５％\t",
                "噬血穹苍命中机会＋５％\t",
                "噬血穹苍伤害力＋５％\t",
                "无影神拳命中机会＋５％\t",
                "无影神拳伤害力＋５％\t",
                "我必还之命中机会＋５％\t",
                "我必还之伤害力＋５％\t",
                "我必还之CD时间减少５秒\t",
                "身空行闪避机会＋５％\t",
                "龙象般若功招架机会＋５％",
                "真·般若极命中机会＋５％",
                "真·般若极伤害力＋５％\t",
                "五轮连转命中和伤害＋５％",
                "十龙十象命中机会＋５％\t",
                "十龙十象伤害力＋５％\t",
                "十龙十象CD时间减少５秒\t",
        }),

        "五毒教": ({
                "五毒烟萝步闪避机会＋５％",
                "碧血箭命中机会＋５％\t",
                "千蛛万毒手招架机会＋５％",
                "万毒穿心命中机会＋５％\t",
                "万毒穿心伤害力＋５％\t",
                "千蛛万毒命中机会＋５％\t",
                "千蛛万毒伤害力＋５％\t",
                "千蛛万毒CD时间减少５秒\t",
                "金蚕蛊召唤CD时间减半\t",
                "金蚕蛊最大召唤数＋０.５\t",
                "金蚕蛊护主机会＋５％\t",
                "金蚕蛊成长速度＋１０％\t",
                "金蚕蛊成长速度再＋１０％\t",
                "金蚕蛊白针CD时间减少１秒\t",
                "金蚕蛊白针命中机会＋５％\t",
                "金蚕蛊白针伤害力＋５％\t",
                "金蚕蛊针对NPC伤害力＋５０％\t",
                "金蚕蛊针对NPC伤害力再＋２５％\t",
                "金蚕蛊彩针触发机会提高\t",
                "金蚕蛊的ＨＰ提升２０％\t",
                "金蚕蛊减免伤害的能力翻倍\t",
                "金蚕蛊死亡豁免的几率提高\t",
        }),

        "关外胡家":({
                "四象步法闪避机会＋５％\t",
                "刀剑归真招架机会＋５％\t",
                "冷月寒气影响对手闪避－５％",
                "开天劈地命中机会＋５％\t",
                "开天辟地伤害力＋５％\t",
                "刀剑七重天命中机会＋５％",
                "刀剑七重天伤害力＋５％\t",
                "刀剑九重天命中机会＋５％",
                "刀剑九重天伤害力＋５％\t",
                "刀剑九重天CD时间减少５秒",
                "妙手驱毒效果＋５％\t",
        }),

        "慕容世家":({
                "北斗仙踪闪避机会＋５％\t",
                "斗转星移招架机会＋５％\t",
                "参合剑气命中机会＋５％\t",
                "参合剑气伤害力＋５％\t",
                "斗转星移命中机会＋５％\t",
                "斗转星移CD时间减少５秒\t",
        }),

        "唐门世家":({
                "秋林拾叶闪避机会＋５％\t",
                "拨云锁雾招架机会＋５％\t",
                "散花天女命中机会＋５％\t",
                "散花天女伤害力＋５％\t",
                "唐花命中机会＋５％\t",
                "唐花伤害力＋５％\t\t",
                "一花一世界命中机会＋５％",
                "一花一世界CD时间减少５秒",
        }),
]);

string *talent_ability = ({
        "research_effect",
        "derive_effect",
        "practice_effect",
        "add_exp",
        "magic_find",
        "add_con",
        "qi_recover",
        "jing_recover",
        "neili_recover",
        "avoid_boss_perform",
        "add_boss_defense",
        "add_boss_damage",
        "attack",
        "parry",
        "dodge",
        "double_damage",
        "avoid_dodge",
        "reduce_cd",
        "avoid_busy",
        "avoid_weak",
        "add_damage",
        "reduce_damage",
        "add_forget",
        "avoid_pot_penalty",
        "powerup_blade",
        "powerup_sword",
        "powerup_unarmed",
        "powerup_throwing",
        "powerup_poison",
        "avoid_die",
        "full_self",
        "fatal_blow",
});

mapping max_talent_ability = ([
        "research_effect" : 1,
        "derive_effect"   : 1,
        "practice_effect" : 1,
        "add_exp"         : 2,
        "magic_find"      : 2,
        "add_con"         : 2,
        "qi_recover"      : 3,
        "jing_recover"    : 2,
        "neili_recover"   : 2,
        "avoid_boss_perform" : 3,
        "add_boss_defense"   : 4,
        "add_boss_damage"    : 3,
        "attack"          : 3,
        "parry"           : 3,
        "dodge"           : 3,
        "double_damage"   : 5,
        "avoid_dodge"     : 5,
        "reduce_cd"       : 2,
        "avoid_busy"      : 3,
        "avoid_weak"      : 3,
        "add_damage"      : 5,
        "reduce_damage"   : 3,
        "add_forget"      : 3,
        "avoid_pot_penalty"  : 5,
        "powerup_blade"   : 5,
        "powerup_sword"   : 5,
        "powerup_unarmed" : 5,
        "powerup_throwing" : 5,
        "powerup_poison" : 5,
        "avoid_die"       : 5,
        "full_self"       : 5,
        "fatal_blow"      : 5,
]);

mapping talent_ability_data = ([
        "research_effect" : 20,
        "derive_effect"   : 20,
        "practice_effect" : 20,
        "add_exp"         : 5,
        "magic_find"      : 5,
        "add_con"         : 5,
        "qi_recover"      : 10,
        "jing_recover"    : 10,
        "neili_recover"   : 10,
        "avoid_boss_perform" : 10,
        "add_boss_defense"   : 5,
        "add_boss_damage"    : 5,
        "attack"          : 3,
        "parry"           : 3,
        "dodge"           : 3,
        "double_damage"   : 4,
        "avoid_dodge"     : 4,
        "reduce_cd"       : 5,
        "avoid_busy"      : 3,
        "avoid_weak"      : 3,
        "add_damage"      : 4,
        "reduce_damage"   : 5,
        "add_forget"      : 3,
        "avoid_pot_penalty"  : 5,
        "powerup_blade"   : 4,
        "powerup_sword"   : 4,
        "powerup_unarmed" : 4,
        "powerup_throwing" : 4,
        "powerup_poison" : 4,
        "avoid_die"       : 2,
        "full_self"       : 2,
        "fatal_blow"      : 2,
]);

string *talent_ability_info = ({
        "神研：研究效率提高20%",
        "神思：汲取效率提高20%",
        "神练：练习效率提高20%",
        "神蕴：任务中获取经验额外增加5%、10%点",
        "神运：装备掉落几率增加5%、10%点",
        "神佑：门派贡献额外增加5%、10%点",
        "战神：战斗时自动恢复气血速度提高10%、20%、30%",
        "战灵：战斗时自动恢复精气速度10%、20%",
        "战狂：战斗中自动恢复内力速度10%、20%",
        "明镜：使玩家有10%、20%、30%的几率防止怪物的必杀技",
        "金刚：增加对boss怪物的绝对防御5%、10%点、15%、20%",
        "伏魔：增加对boss怪物的绝对伤害5%、10%点、15%点",
        "鹰眼：命中增加3%、6%、9%",
        "格挡：招架增加3%、6%、9%",
        "迷踪：躲闪增加3%、6%、9%",
        "暴击：双倍伤害几率增加4%、8%、12%、16%、20%",
        "强袭：4%、8%、12%、16%、20%的机率让轻功的特殊防御均无效",
        "归真：特殊武功大招的冷却时间降低5秒、10秒",
        "逍遥：战斗中有3%、6%、9%的机率消除忙乱",
        "武神：增加抵抗虚弱能力3%、6%、9%",
        "极境：增加4%、8%、12%、16%、20%的伤害效果",
        "守护：减少5%、10%、15%的伤害效果",
        "遗忘：让对手有3%、6%、9%的几率遗忘绝招",
        "天赐：死亡时有5%、10%、15%、20%、25%的机率不掉潜能",
        "刀皇：使用刀法武功增加4%、8%、12%、16%、20%的命中及伤害",
        "剑圣：使用剑法武功增加4%、8%、12%、16%、20%的命中及伤害",
        "拳王：使用拳法武功增加4%、8%、12%、16%、20%的命中及伤害",
        "飞仙：使用暗器技能增加4%、8%、12%、16%、20%的命中及伤害",
        "毒君：增加4%、8%、12%、16%、20%的几率破除怪体等对毒的免疫",
        "涅槃：忽视死亡的几率提高2%、4%、6%、8%、10%",
        "神战：气血内力自动恢复几率提高2%、4%、6%、8%、10%",
        "神杀：战斗中造成致命一击的几率提高2%、4%、6%、8%、10%",
});

int do_ability_cost(object ob, string arg, int flag);
int check_ability(object me,string arg, int flag);
int check_ability_count(object me,string arg, int flag);
int improve_ability(object me,string arg, int flag);
int valid_ability_improve(object me, string arg, int flag);
string get_ability_idf(object me,string arg, int flag);
string get_ability_info(object ob, string arg, int flag);

int valid_ability_improve(object me, string arg, int flag)
{
        int level;
        int a_lvl;
        int u_lvl;

        a_lvl = check_ability_count(me, arg, flag);
        if( flag == 2 )
                level = max_talent_ability[arg];
        else
                level = max_ability[arg];
        if( !level ) level = 5;
        if( a_lvl >= level )
                return 0;

        u_lvl = query("level", me);
        if( flag == 0 && u_lvl < 10 ) {
                return 0;
        }
        if( flag == 1 && u_lvl < 20 ) {
                return 0;
        }
        if( flag == 2 ) {
                return 1;
        }

        return 1;
}

varargs int check_ability(object me,string arg, int flag)
{
        int result;

        if( flag == 2 )
                // 天赋技能
                result = query("talent/" + arg, me);
        else
                // Ability 门派
                result=query("ability2/"+query("family/family_name", me)+"/"+arg, me)+query("ability1/"+arg, me);

        return result;
}

varargs int check_ability_count(object me,string arg, int flag)
{
        int result;

        if( flag == 2 )
                // 天赋技能
                result = query("talent_count/" + arg, me);
        else
                // Ability 门派
                result=query("ability_count/"+me->query_family()+"/"+arg, me)+query("ability_count/"+arg, me);

        return result;
}

int check_ability_cost(object me, string arg, int flag)
{
        int cost;

        if( flag == 1 ) {
                if( !undefinedp(fam_ability_pot[arg]) )
                        cost = fam_ability_pot[arg];
                else
                        cost = 5;
        } else if( flag == 2 ) {
                cost = 1;
        } else {
                if( member_array(arg, bas_ability) == -1 ) {
                        return 0;
                }
                cost = bas_ability_pot[arg];
                if( !cost ) {
                        cost = 1;
                }
        }
        return cost;
}

// 每次耗费一点能力点及十万点潜能
int do_ability_cost(object me, string arg, int flag)
{
        int cost, pot;

        cost = check_ability_cost(me, arg, flag);
        pot  = cost * 100000;
        if( query("potential", me) - query("learned_potential", me) < pot )
                return 0;

        if( flag == 1 || flag == 0 ) {
                if( cost > query("ability", me)-query("learned_ability", me) ) {
                        return 0;
                }
                addn("learned_ability", cost, me);
                addn("learned_potential", pot, me);
        }

        if( flag == 2 ) {
                if( cost > query("energy", me)-query("learned_energy", me) ) {
                        return 0;
                }
                addn("learned_energy", cost, me);
                addn("learned_potential", pot, me);
        }
        return 1;
}

int improve_ability(object me,string arg, int flag)
{
        int lv, n;
        string myclass;

        myclass = query("family/family_name", me);
        if( !flag ) {
                addn("ability1/"+arg, 1, me);
                addn("ability_count/"+arg, 1, me);
        } else if( flag == 1 ) {
                if( !undefinedp(fam_ability_data[arg]) )
                        n = fam_ability_data[arg];
                else
                        n = 5;
                addn("ability2/"+myclass+"/"+arg, n, me);
                addn("ability_count/"+myclass+"/"+arg, 1, me);
        } else if( flag == 2 ) {
                if( !undefinedp(talent_ability_data[arg]) )
                        n = talent_ability_data[arg];
                else
                        n = 1;
                addn("talent/"+arg, n, me);
                addn("talent_count/"+arg, 1, me);
        }
        return 1;
}

string get_ability_info(object ob, string arg, int flag)
{
        int lv, cost, n;
        string desc, msg, myclass;

        //lv = check_ability(ob, arg, flag);
        cost = check_ability_cost(ob, arg, flag);
        desc = get_ability_idf(ob,arg,flag);
        if( flag == 1 ) {
                // ability's 门派技能
                myclass=query("family/family_name", ob);
                if( arrayp(fam_ability[myclass]) ) {
                        n = member_array(arg,fam_ability[myclass]);
                        if( n != -1 ) {
                                msg = fam_ability_info[myclass][n];
                                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR,desc, cost);
                                return msg;
                        }
                }
                return "";
        }

        if( flag == 2 ) {
                n = member_array(arg,talent_ability);
                if( n != -1 ) {
                        msg = talent_ability_info[n];
                        msg = sprintf("%-60s%-12s"HIC"%5d\n"NOR, msg, desc, cost);
                        return msg;
                }
                return "";
        }

        n = member_array(arg, bas_ability);
        if( n != -1 ) {
                msg = bas_ability_info[n];
                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR, desc, cost);
                return msg;
        }
        return "";
}


string get_ability_idf(object me,string arg, int flag)
{
        int level;
        int lev = check_ability_count(me,arg,flag);
        // 1,2,3,4 Basic
        // 5,6,7 Advanced
        // 8,9: Master
        // 10: Grand Master
        string *tough_level_desc = ({
                BLU "一无所知" NOR,
                BLU "毫不足虑" NOR,
                BLU "不足挂齿" NOR,
                BLU "初学乍练" NOR,
                BLU "勉勉强强" NOR,
                HIB "初窥门径" NOR,
                HIB "初出茅庐" NOR,
                HIB "略知一二" NOR,
                HIB "普普通通" NOR,
                HIB "平平淡淡" NOR,
                CYN "平淡无奇" NOR,
                CYN "粗通皮毛" NOR,
                CYN "半生不熟" NOR,
                CYN "马马虎虎" NOR,
                CYN "略有小成" NOR,
                HIC "已有小成" NOR,
                HIC "鹤立鸡群" NOR,
                HIC "驾轻就熟" NOR,
                HIC "青出于蓝" NOR,
                HIC "融会贯通" NOR,
                HIG "心领神会" NOR,
                HIG "炉火纯青" NOR,
                HIG "了然于胸" NOR,
                HIG "略有大成" NOR,
                HIG "已有大成" NOR,
                YEL "豁然贯通" NOR,
                YEL "出类拔萃" NOR,
                YEL "无可匹敌" NOR,
                YEL "技冠群雄" NOR,
                YEL "神乎其技" NOR,
                HIY "出神入化" NOR,
                HIY "非同凡响" NOR,
                HIY "傲视群雄" NOR,
                HIY "登峰造极" NOR,
                HIY "无与伦比" NOR,
                RED "所向披靡" NOR,
                RED "一代宗师" NOR,
                RED "精深奥妙" NOR,
                RED "神功盖世" NOR,
                RED "举世无双" NOR,
                WHT "惊世骇俗" NOR,
                WHT "撼天动地" NOR,
                WHT "震古铄今" NOR,
                WHT "超凡入圣" NOR,
                WHT "威镇寰宇" NOR,
                HIW "空前绝后" NOR,
                HIW "天人合一" NOR,
                MAG "深藏不露" NOR,
                HIM "深不可测" NOR,
                HIR "返璞归真" NOR
        });
        string desc;

        if( flag == 2 )
                level = max_talent_ability[arg];
        else
                level = max_ability[arg];
        if( !level ) level = 5;

        desc = sprintf(HIM"%3d/%3d"NOR, lev, level);
        if( lev >= 10 ) lev = 10;
        return (tough_level_desc[lev]+"（"+ desc+"）");
}

/*
天赋系修改 设置，已完成幸运系。
攻击系
绝世命中：降低对方对你所有物理攻击的躲闪几率！
极度杀戮：提升自己所有物理攻击伤害！
嗜血元神：你有的几率,在击中对方后额外获得一次额外物理攻击击！
防御系
绝世招架：增加自己对所有物理攻击的招架几率！
极品体质：降低所有物理攻击对你所造成伤害！
铜墙铁壁：你有几率,在被击中后对敌人进行一次必中的物理攻击;
文学系
绝世奇才：提高你百分之几的读书和学习效率
神童在世：提高你百分之几的练习和研究效率
博学天才：你有百分之几几率,在技能升级时，使得这个技能;额外再升一级！
恢复系
绝世筋骨：提高你的运功疗伤功效
死而后生：增加你在战斗中自动疗伤效果
千古奇人：战斗中被击中，自动恢复总气血的并且 降低各类毒性发作时间。
幸运系
财神高照：奖励你百分之几的额外金钱数量！
福禄降世：奖励你百分之几的额外经验、潜能、体会！
幸运大师：奖励你百分之几的额外英勇点数、境界修为点数、 仙石数目。遇到仙人、上古秘境、修真机缘、获取极品物品、通过神阵等等的几率更大。
*/
