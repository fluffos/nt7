#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "jian seng",
                "name":        "剑僧",
                "type":        "杀",
                "bonus":       72,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5jian.c",
        ]),
        ([
                "id":          "gongye qian",
                "name":        "公冶乾",
                "type":        "杀",
                "bonus":       87,
                "msg":        "",
                "object":      "/d/yanziwu/npc/gongye.c",
        ]),
        ([
                "id":          "dao seng",
                "name":        "刀僧",
                "type":        "杀",
                "bonus":       74,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5dao.c",
        ]),
        ([
                "id":          "yu canghai",
                "name":        "余沧海",
                "type":        "杀",
                "bonus":       105,
                "msg":        "",
                "object":      "/kungfu/class/qingcheng/yu.c",
        ]),
        ([
                "id":          "feng boe",
                "name":        "风波恶",
                "type":        "杀",
                "bonus":       73,
                "msg":        "",
                "object":      "/d/yanziwu/npc/feng.c",
        ]),
        ([
                "id":          "zhao banshan",
                "name":        "赵半山",
                "type":        "杀",
                "bonus":       105,
                "msg":        "",
                "object":      "/d/hangzhou/honghua/zhao.c",
        ]),
        ([
                "id":          "deng baichuan",
                "name":        "邓百川",
                "type":        "杀",
                "bonus":       100,
                "msg":        "",
                "object":      "/d/yanziwu/npc/deng.c",
        ]),
        ([
                "id":          "bai zhen",
                "name":        "白振",
                "type":        "杀",
                "bonus":       70,
                "msg":        "",
                "object":      "/d/hangzhou/npc/baizhen.c",
        ]),
        ([
                "id":          "yuzhen zi",
                "name":        "玉真子",
                "type":        "杀",
                "bonus":       85,
                "msg":        "",
                "object":      "/d/guanwai/npc/yuzhenzi.c",
        ]),
        ([
        "id":          "fei bin",
                "name":        "费彬",
                "type":        "杀",
                "bonus":       85,
                "msg":        "",
                "object":      "/kungfu/class/songshan/fei.c",
        ]),
        ([
                "id":          "bao butong",
                "name":        "包不同",
                "type":        "杀",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/yanziwu/npc/bao.c",
        ]),
        ([
                "id":          "mu wanqing",
                "name":        "木婉清",
                "type":        "杀",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/wanjiegu/npc/mu.c",
        ]),
        ([
                "id":          "nv lang",
                "name":        "蒙面女郎",
                "type":        "杀",
                "bonus":       75,
                "msg":        "",
                "object":      "/d/lingjiu/npc/nvlang.c",
        ]),
        ([
                "id":          "lazhang huofo",
                "name":        "拉章活佛",
                "type":        "杀",
                "bonus":       72,
                "msg":        "",
                "object":      "/kungfu/class/xueshan/lazhang.c",
        ]),
        ([
                "id":          "sheng di",
                "name":        "胜谛",
                "type":        "杀",
                "bonus":       89,
                "msg":        "",
                "object":      "/kungfu/class/xuedao/shengdi.c",
        ]),
        ([
                "id":          "zhang danyue",
                "name":        "张淡月",
                "type":        "杀",
                "bonus":       82,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/zhang.c",
        ]),
        ([
                "id":          "wugen daozhang",
                "name":        "无根道长",
                "type":        "杀",
                "bonus":       97,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/wugen.c",
        ]),
        ([
                "id":          "su quan",
                "name":        "苏荃",
                "type":        "杀",
                "bonus":       87,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/su.c",
        ]),
        ([
                "id":          "yu hongxing",
                "name":        "余洪兴",
                "type":        "杀",
                "bonus":       80,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/yu-hx.c",
        ]),
        ([
                "id":          "quan guanqing",
                "name":        "全冠清",
                "type":        "杀",
                "bonus":       75,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/quan-gq.c",
        ]),
        ([
                "id":          "li sheng",
                "name":        "黎生",
                "type":        "杀",
                "bonus":       73,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/li-sh.c",
        ]),
});
mapping query_questdg()
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
