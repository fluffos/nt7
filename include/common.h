// common.h

// 普通物品列表

// weapon : 武器
// sword　: 剑
// knife　: 匕首
// axe　　: 斧头
// mace　 : 杖
// club　 : 棍
// bow　　: 弓
// javelin: 标枪
// spear　: 矛
// hammer : 锤

// equip　: 装备
// helmet : 头盔
// armor　: 护甲
// shield : 盾
// gloves : 手套
// boots　: 靴子
// belt　 : 腰带
// ring　 : 戒指
// amulet : 护符
// charm　: 饰物 - 特大, 大型, 小型
// other　: 其他

mapping common_list = ([
        "weapon" : ([   "sword" : ([ "short sword": "短剑", "scimitar" : "弯刀",
　　　　　　　　　　　　　　　　　 "sabre"　　　: "马刀", "fachion"　: "伶月刀",
　　　　　　　　　　　　　　　　　 "long sword" : "长剑", "war sword": "战剑",
　　　　　　　　　　　　　　　　　 "crystal sword"　: "水晶剑", "broad sword"　: "阔剑",
　　　　　　　　　　　　　　　　　 "two-hand sword" : "双手剑", "claymore"　　 : "双刃刀",
　　　　　　　　　　　　　　　　　 "giant sword"　　: "巨剑",　 "bastard sword": "奇行剑",
　　　　　　　　　　　　　　　　　 "flamberge"　　　: "火焰剑", "great sword"　: "巨人剑", ]),

                        "knife" : ([ "dagger" : "短剑",　 "dirk"　: "匕首",
　　　　　　　　　　　　　　　　　 "kris"　 : "蛇刃剑", "blade" : "刀",
　　　　　　　　　　　　　　　　　 "throwing knife" : "投掷刀", "balanced knife" : "平衡刀", ]),

                        "axe"　 : ([ "hand exe"　 : "手斧",　 "axe"　　　　　 : "斧", 
　　　　　　　　　　　　　　　　　 "double exe" : "双刃斧", "military pick" : "战镐",
　　　　　　　　　　　　　　　　　 "war axe"　　: "战斧",　 "large axe"　　 : "大斧",
　　　　　　　　　　　　　　　　　 "broad axe"　: "宽斧",　 "battle axe"　　: "战斧",
　　　　　　　　　　　　　　　　　 "great axe"　: "巨斧",　 "giant axe"　　 : "巨斧", ]),

                        "mace"　: ([ "mace" : "杖", "morning star" : "晨星杖", "flail" : "连枷", ]),
　　　　　　　　　　　
                        "club"　: ([ "club" : "棍", "spiked club"　: "钉棍", ]),
　　　　　　　　　　　
                        "bow"　 : ([ "short bow" : "短弓", "hunter's bow"　: "猎弓",
                        "long bow"　: "长弓", "composite bow" : "复合弓",
　　　　　　　　　　　　　　　　　 "short battle bow" : "短战弓", "long battle bow" : "长战弓",
　　　　　　　　　　　　　　　　　 "short war bow"　　: "短战弓", "long war bow"　　: "长战弓", ]),

                        "javelin" : ([ "javelin"　　　　: "标枪", "pilum"　: "重标枪",
　　　　　　　　　　　　　　　　　　 "short spear"　　: "短矛", "glaive" : "戈",
　　　　　　　　　　　　　　　　　　 "throwing spear" : "掷矛", ]),

                        "spear"　 : ([ "spear"　　　 : "矛",　 "trident" : "三叉戟",
　　　　　　　　　　　　　　　　　　 "brandistock" : "长矛", "spetum"　: "长矛",
　　　　　　　　　　　　　　　　　　 "pike"　　　　: "长枪", ]), ]),

        "helmet" : ([ "cap"　　　 : "帽子",　 "skull cap"　: "头盔", "helm"　: "头盔", 
　　　　　　　        "full helm" : "全头盔", "great helm" : "巨盔", "crown" : "冠",
　　　　　　　　　　  "mask"　　　: "面具",　 "bone helm"　: "骨盔", ]),

　　　  "armor"　: ([ "quilted armor"　　　: "软甲",　 "leather armor" : "皮甲",
　　　　　　　　　    "hard leather armor" : "硬皮甲", "studded armor" : "钉甲",
　　　　　　　　　　  "ring mail"　　　　　: "环甲",　 "scale mail"　　: "鳞甲",
　　　　　　　　　　  "chain mail"　　　　 : "锁子甲", "breast plate"　: "胸甲",
　　　　　　　　　    "splint mail"　　　　: "藤甲",　 "plate mail"　　: "钢板甲",
　　　　　　　　　　  "field plate"　　　　: "片甲",　 "gothic plate"　: "哥特甲",
　　　　　　　　　　  "full plate mail"　　: "全身甲", "ancient armor" : "旧甲",
　　　　　　　　　　  "light plate"　　　　: "轻甲", ]),

        "shield" : ([ "buckler"　　　: "小园盾", "small shield"　: "小盾",
　　　　　　　　　　  "large shield" : "大盾",　 "kite shield"　 : "长盾",
　　　　　　　　　　  "tower shield" : "平盾",　 "gothic shield" : "哥特盾",
　　　　　　　　　　  "bone shield"　: "骨盾",　 "spiked shield" : "钉盾", ]),

        "gloves" : ([ "leather gloves" : "皮手套", "heavy gloves"　　: "重手套",
　　　　　　　　　　  "chain gloves"　 : "链手套", "light gauntlets" : "轻铁护手",
　　　　　　　　　　  "gauntlets"　　　: "铁护手", ]),

        "boots"　: ([ "boots"　　　 : "靴子",　 "heavy boots"　　　　: "重靴",
　　　　　　　　　　  "chain boots" : "锁子靴", "light plated boots" : "轻铁靴",
　　　　　　　　　　  "greaves"　　 : "护胫甲", ]),

        "belt"　 : ([ "sash" : "腰带", "light belt" : "轻腰带",
　　　　　　　　　　  "belt" : "腰带", "heavy belt" : "重腰带",
　　　　　　　　　　  "plated belt" : "铁腰带", ]),

        "ring"　 : "戒指",
        "amulet" : "护身符",

        "charm"　: ([ "grand charm" : "豪华饰物", "large charm" : "大饰物",
　　　　　　　　　　  "small charm" : "小饰物", ]),

        "potion" : ([ "healing"　: ([ "minor healing potion"　 : "小生命瓶",
　　　　　　　　　　　　　　　　　　  "light healing potion"　 : "轻生命瓶",
　　　　　　　　　　　　　　　　　　  "healing potion"　　　　 : "轻生命瓶",
　　　　　　　　　　　　　　　　　　  "greater healing potion" : "大生命瓶",
　　　　　　　　　　　　　　　　　　  "super healing potion"　 : "特级生命瓶", ]),
　　　　　　　　　　  "mana"　　 : ([ "minor mana potion"　 : "小魔法瓶",
　　　　　　　　　　　　　　　　　　  "light mana potion"　 : "轻魔法瓶",
　　　　　　　　　　　　　　　　　　  "mana potion"　　　　 : "轻魔法瓶",
　　　　　　　　　　　　　　　　　　  "greater mana potion" : "大魔法瓶",
　　　　　　　　　　　　　　　　　　  "super mana potion"　 : "特级魔法瓶", ]),
　　　　　　　　　　  "antidote potion" : "解毒剂",
　　　　　　　　　　  "thawing potion"　: "解冻剂", ]),

        "key"　 : "钥匙",
        "jewel" : "珠宝",
]);

// 物品出现的几率
array common_rate_table = ({ "weapon", "potion", "armor", "helmet", "shield",
　　　　　　　　　　　　　　　 "key", "gloves", "boots", "belt", "ring", "amulet",
　　　　　　　　　　　　　　　 "charm", "jewel", });

static int max_rate;

int *common_rate_list = ({ 120, 100, 100, 80, 80, 70, 60, 60, 60, 20, 20, 20, 10, });
