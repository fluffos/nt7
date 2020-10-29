#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "fuchen",
                "name":        "拂尘",
                "type":        "寻",
                "bonus":       62,
                "msg1":        "",
                "object":      "/d/dali/obj/fuchen.c",
        ]),
        ([
                "id":          "putuan",
                "name":        "小蒲团",
                "type":        "寻",
                "bonus":       50,
                "msg1":        "",
                "object":      "/d/xiaoyao/obj/putuan.c",
        ]),
        ([
                "id":          "dress",
                "name":        "[1;37m梨花飘雪裳[2;37;0m",
                "type":        "寻",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/wanjiegu/npc/obj/pink-dress.c",
        ]),
        ([
                "id":          "key",
                "name":        "钥匙",
                "type":        "寻",
                "bonus":       68,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/key.c",
        ]),
        ([
                "id":          "xuan tie",
                "name":        "[36m玄铁石[2;37;0m",
                "type":        "寻",
                "bonus":       100,
                "msg1":        "",
                "object":      "/d/item/obj/xuantie.c",
        ]),
        ([
                "id":          "qing xin",
                "name":        "信",
                "type":        "寻",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/letter.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "布衣",
                "type":        "寻",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/cloth.c",
        ]),
        ([
                "id":          "huang shan",
                "name":        "[1;33m黄衫[2;37;0m",
                "type":        "寻",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/huangshan.c",
        ]),
        ([
                "id":          "qing yi",
                "name":        "青衣",
                "type":        "寻",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/qingyi.c",
        ]),
        ([
                "id":          "dou peng",
                "name":        "斗篷",
                "type":        "寻",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/doupeng.c",
        ]),
        ([
                "id":          "18 muou",
                "name":        "十八木偶",
                "type":        "寻",
                "bonus":       70,
                "msg1":        "",
                "object":      "/clone/book/18muou.c",
        ]),
        ([
                "id":          "18 niou",
                "name":        "十八泥偶",
                "type":        "寻",
                "bonus":       70,
                "msg1":        "",
                "object":      "/clone/book/18niou.c",
        ]),
        ([
                "id":          "jiuyin zhenjing1",
                "name":        "「九阴真经」上册",
                "type":        "寻",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/book/jiuyin1.c",
        ]),
        ([
                "id":          "jiuyin zhenjing2",
                "name":        "「九阴真经」下册",
                "type":        "寻",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/book/jiuyin2.c",
        ]),
        ([
                "id":          "jin",
                "name":        "金丝甲",
                "type":        "寻",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/jin.c",
        ]),
        ([
                "id":          "silk",
                "name":        "薄绢",
                "type":        "寻",
                "bonus":       85,
                "msg1":        "",
                "object":      "/clone/book/book-silk.c",
        ]),
        ([
                "id":          "jian pu",
                "name":        "天羽奇剑剑谱",
                "type":        "寻",
                "bonus":       85,
                "msg1":        "",
                "object":      "/clone/book/qijianpu.c",
        ]),
        ([
                "id":          "short sword",
                "name":        "[1;36m短剑[2;37;0m",
                "type":        "寻",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/shortsword.c",
        ]),
        ([
                "id":          "cui yu",
                "name":        "[1;32m翠羽[2;37;0m",
                "type":        "寻",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/cuiyu.c",
        ]),
        ([
                "id":          "armor",
                "name":        "铁甲",
                "type":        "寻",
                "bonus":       65,
                "msg1":        "",
                "object":      "/d/city/obj/tiejia.c",
        ]),
        ([
                "id":          "duanjian",
                "name":        "短剑",
                "type":        "寻",
                "bonus":       92,
                "msg1":        "",
                "object":      "/d/city/obj/duanjian.c",
        ]),
        ([
                "id":          "gang jian",
                "name":        "[1;37m钢剑[2;37;0m",
                "type":        "寻",
                "bonus":       67,
                "msg1":        "",
                "object":      "/d/beijing/npc/obj/sword2.c",
        ]),
        ([
                "id":          "tie di",
                "name":        "[1;34m铁笛[2;37;0m",
                "type":        "寻",
                "bonus":       92,
                "msg1":        "",
                "object":      "/kungfu/class/dali/obj/tiedi.c",
        ]),
        ([
                "id":          "zi pao",
                "name":        "[35m紫袍[2;37;0m",
                "type":        "寻",
                "bonus":       92,
                "msg1":        "",
                "object":      "/kungfu/class/dali/obj/magcloth.c",
        ]),
});
mapping query_questkh()
{
        int i;
        mapping the_quest,random_quest;
        string *quest_key;

        random_quest = quest[random(sizeof(quest))];
        the_quest = ([]);

        quest_key = keys(random_quest);
        for (i = 0;i < sizeof(quest_key);i++)
                the_quest[quest_key[i]] = random_quest[quest_key[i]];

        return the_quest;
}
