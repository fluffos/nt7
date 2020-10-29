// Created by Smallfish For HUAXIA@2004, 2004/4/24

#include <ansi.h>

#define CHECK_DIR(x)    ("/quest/questsj/" + x)
#define CHECK_HEAD      CHECK_DIR("head_obj")
#define CHECK_ARMOR     CHECK_DIR("armor_obj")
#define CHECK_CLOTH     CHECK_DIR("cloth_obj")
#define CHECK_SWORD     CHECK_DIR("sword_obj")
#define CHECK_BLADE     CHECK_DIR("blade_obj")
#define CHECK_HAMMER    CHECK_DIR("hammer_obj")
#define CHECK_STAFF     CHECK_DIR("staff_obj")
#define CHECK_KNOWLEDGE CHECK_DIR("knowledge_obj")
#define CHECK_MIJI      CHECK_DIR("miji_obj")


mapping *quest = ({
        ([
                "id":                 "HEAD_OBJ",
                "name":               "头胸护具、饰品",
                "msg0":               "武林同盟最近准备培训一批女杀手，缺少头部护具、头饰、胸饰等物品，",
                "msg1":               "据报白驼山打算进攻中原，武林同盟必须未雨绸缪，最近头部护具、头饰、胸饰等物品紧缺，",
                "msg2":               "武林同盟库房物资缺乏，尤其是头部护具、头饰、胸饰等物品，",
                "msg3":               "头部、胸部是人体要害，一定要防护妥当，头部护具、头饰、胸饰等物品甚为紧要！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "件",
                "check_file":         CHECK_HEAD,
                "type":               "收",
        ]),
        ([
                "id":                 "ARMOR_OBJ",
                "name":               "身体护具",
                "msg0":               "最近江湖纠纷不断，我们的身体护具等物资消耗很大，",
                "msg1":               "据报白驼山打算进攻中原，武林同盟必须未雨绸缪，",
                "msg2":               "上次去会见一位老友，看到他门下弟子护甲齐整，看来我们也要整顿一下，",
                "msg3":               "武林同盟新到了一大批兵器，现在身体护具等物资相较而言颇为紧缺，",
                "max_num":            35,
                "min_num":            25,
                "unit":               "件",
                "check_file":         CHECK_ARMOR,
                "type":               "收",
        ]),
        ([
                "id":                 "CLOTH_OBJ",
                "name":               "衣服",
                "msg0":               "最近新来了一帮兄弟，个个都很穷，连一件象样的衣服都没有，",
                "msg1":               "前阵子安排一帮兄弟去西荒之地完成一个任务，结果个个搞得衣衫褴褛回来了，",
                "msg2":               "这天气有些反常，看来就要换季了，",
                "msg3":               "武林同盟库房物资缺乏，尤其缺少衣服！",
                "max_num":            50,
                "min_num":            30,
                "unit":               "件",
                "check_file":         CHECK_CLOTH,
                "type":               "收",
        ]),
        ([
                "id":                 "SWORD_OBJ",
                "name":               "剑器",
                "msg0":               "剑乃百兵之首，兄弟们虽说不需人人都精通剑法，但也得熟知剑道，",
                "msg1":               "最近我刚创出一个威力巨大的剑阵，正准备安排人手演练一番，",
                "msg2":               "学武可以强身键体，虽然是老百姓也应该会个一招两式，武林同盟最近准备开个免费培训班，",
                "msg3":               "前天晚上武林同盟兵器库居然失窃！真是岂有此理！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_SWORD,
                "type":               "收",
        ]),
        ([
                "id":                 "BLADE_OBJ",
                "name":               "刀器",
                "msg0":               "俗话说快刀斩乱麻，行走江湖的话，还是用刀比较畅快淋漓！",
                "msg1":               "弟兄们最近日子过得安逸，刀法也生疏了不少，得敦促他们好好练习练习，",
                "msg2":               "对付仇家最畅快的就是乱刀齐下剁为肉泥，有个家伙老跟我作对，我已经安排好了弟兄去料理他，",
                "msg3":               "我想了解一下江湖中目前使用刀法的人士，对刀法的研究究竟到了何种境界！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_BLADE,
                "type":               "收",
        ]),
        ([
                "id":                 "HAMMER_OBJ",
                "name":               "锤类兵器",
                "msg0":               "锤法是相当难练的一种武艺，我打算亲自给弟兄们指点一下此门功夫，",
                "msg1":               "锤法要使的好，关键是兵器要设计的恰当！",
                "msg2":               "最近刚招募了一帮东北大汉，身高体壮，最是适合修炼锤法，",
                "msg3":               "我对大部分兵器也算颇有研究，只是对锤类兵器不甚明了！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "柄",
                "check_file":         CHECK_HAMMER,
                "type":               "收",
        ]),
        ([
                "id":                 "STAFF_OBJ",
                "name":               "棍、杖类兵器",
                "msg0":               "修炼武功，棍法是很好的奠基功夫，新来的兄弟必须好好掌握棍法，",
                "msg1":               "棍、杖向来是冷门兵器，我最近颇为空闲，准备对其好好研究一番，",
                "msg2":               "弟兄们日常操练，刀剑容易伤人，棍、杖最为合适！",
                "msg3":               "听说最近江湖中颇多高手使用杖法，我也想研究一下棍法、杖法的深奥之处！",
                "max_num":            35,
                "min_num":            25,
                "unit":               "根",
                "check_file":         CHECK_STAFF,
                "type":               "收",
        ]),
        ([
                "id":                 "KNOWLEDGE_OBJ",
                "name":               "知识类书籍",
                "msg0":               "武林同盟新建立一座藏经阁，准备收藏天下所有经书典籍，",
                "msg1":               "古人云：活到老，学到老！我准备读遍天下经书典籍，",
                "msg2":               "不知我可否称得上学富五车、才高八斗？不知我可否有未曾读过的经书典籍？",
                "msg3":               "习武之人最紧要的就是修心养性，最近弟兄们大多心浮气燥，得约束约束他们了！",
                "max_num":            30,
                "min_num":            20,
                "unit":               "本",
                "check_file":         CHECK_KNOWLEDGE,
                "type":               "收",
        ]),
        ([
                "id":                 "MIJI_OBJ",
                "name":               "武功秘笈",
                "msg0":               "武林同盟新建立一座藏经阁，准备收藏天下所有武功秘笈，",
                "msg1":               "少林有个藏经楼收藏了七十二般武功秘笈，我们武林同盟难道比少林略有逊色？",
                "msg2":               "我已经读过无数武功秘笈，不知可有我未曾知晓的武技？",
                "msg3":               "将天下所有武功秘笈搜括囊中是我一生最大的宏愿之一！",
                "max_num":            30,
                "min_num":            20,
                "unit":               "本",
                "check_file":         CHECK_MIJI,
                "type":               "收",
        ]),
});

mapping query_good()
{
        return quest[random(sizeof(quest))];
}
