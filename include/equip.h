
// This program is a part of NT MudLIB

#define PART_ID                 0       // 部位代号
#define PART_AMOUNT             1       // 此部位可装备的装备数量
#define PART_CONFLICT           2       // 部位的冲突资料


// 装备部位类型   ({ 部位,        可装备数量,     装备部位冲突 })
nomask nosave mapping part_set = ([
        "head"  : ({ "head",              1,          ({})     }),      // 头盔
        "neck"  : ({ "necklace",          1,          ({})     }),      // 项链
        "medal" : ({ "medal",             1,          ({})     }),      // 勋章
        "medal2": ({ "medal",            21,          ({})     }),      // 勋章
        "medal3": ({ "medal",            21,          ({})     }),      // 勋章
        "mymask": ({ "mask",              1,          ({})     }),      // 面具
        "myheart":({ "heart",             1,          ({})     }),      // 胸口
        "myheart2":({"heart",             1,          ({})     }),      // 胸口
        "earring":({ "earring",           1,          ({})     }),      // 耳坠
        "hairpin":({ "hairpin",           1,          ({})     }),      // 发饰
        "charm" : ({ "charm",             1,          ({})     }),      // 护身符
        "surcoat":({ "surcoat",           1,          ({})     }),      // 披风
        "armor" : ({ "armor",             1,          ({})     }),      // 护甲
        "cloth" : ({ "cloth",             1,          ({})     }),      // 衣服
        "rings" : ({ "ring",              1,          ({})     }),      // 戒指
        "hand"  : ({ "hand",              2,          ({ "twohand" })     }),      // 单手
        "hands" : ({ "hand",              2,          ({ "twohand" })     }),      // 单手
        "finger": ({ "hand",              2,          ({ "twohand" })     }),      // 单手
        "shield": ({ "hand",              2,          ({ "twohand" })     }),      // 单手
        "twohand":({ "twohand",           1,          ({ "hand" })        }),      // 双手
        "wrists": ({ "wrists",            1,          ({})     }),      // 护腕
        "waist" : ({ "waist",             1,          ({})     }),      // 腰带
        "pants" : ({ "leggings",          1,          ({})     }),      // 腿甲
        "boots" : ({ "boots",             1,          ({})     }),      // 鞋子
        "horse" : ({ "mount",             1,          ({})     }),      // 座骑
]);
