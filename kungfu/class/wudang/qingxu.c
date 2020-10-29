// guxu.c 清虚

//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

string ask_me();

void create()
{
        set_name("清虚道长", ({ "qingxu daozhang", "qingxu" }));
        set("long",
                "他就是俞莲舟的弟子清虚道长。\n"
                "他今年二十多岁，主管复真观的杂事。\n"
                "专门在这里看守本派的各种道经");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("max_qi", 1800);
        set("max_jing", 900);
        set("neili", 2400);
        set("max_neili", 2400);
        set("jiali", 30);

        set("combat_exp", 70000);
        set("score", 8500);

        set_skill("force", 85);
        set_skill("yinyun-ziqi", 85);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 80);
        set_skill("strike", 85);
        set_skill("wudang-zhang", 85);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 50);
          set_skill("literate", 50);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        create_family("武当派", 3, "弟子");
        set("class", "taoist");

        set("inquiry", ([
                "道德经" : (: ask_me :),
                "武当派" : "贫道便是武当派弟子，不知这位"+ RANK_D->query_respect(this_player())+"有何见教？",
                "太极剑法" : "嗯……这我不大清楚，你得去问冲虚师兄。",
                "武当剑" : "嗯……武当剑的质地柔韧不足，坚硬易脆，对方如果使用重器械，则不宜与其硬碰硬撞。",
                "两仪剑法" : "两仪剑法中有阴有阳，亦刚亦柔，神妙精微无比。",
                "武当两仪剑" : "两仪剑法中有阴有阳，亦刚亦柔，神妙精微无比。",
                "绕指柔剑" : "这路剑法我可不会使。",
                "神门十三剑" : "这路剑法我可不会使。",
                "武当长拳" : "拳脚功夫非贫道所长。",
                "绵掌" : "拳脚功夫非贫道所长。",
                "震山掌" : "拳脚功夫非贫道所长。",
                "虎爪绝户手" : "嗯……曾听说敝派有这一路武功，但从未见师伯师叔使过。",
                "张三丰" : "敝派创派祖师，近年来常年闭关不出。",
                "张真人" : "敝派创派祖师，近年来常年闭关不出。",
                "宋远桥" : "那是敝派掌门大师伯。",
                "宋大侠" : "那是敝派掌门大师伯。",
                "俞莲舟" : "那是二师伯。",
                "俞二侠" : "那是二师伯。",
                "俞岱岩" : "那是三师伯。",
                "俞三侠" : "那是三师伯。",
                "张松溪" : "贫道的授业恩师",
                "张四侠" : "贫道的授业恩师",
                "张翠山" : "………那是贫道的五师叔。",
                "张五侠" : "………那是贫道的五师叔。",
                "殷梨亭" : "那是六师叔。",
                "殷六侠" : "那是六师叔。",
                "莫声谷" : "那是七师叔。",
                "莫七侠" : "那是七师叔。",
                "宋青书" : "好久没见到宋师哥了，听说他和莫七叔吵过架，就此再没回武当过。",
                "冲虚" : "他是贫道的师兄，三代弟子中也就他会使太极剑法。",
                "冲虚道长" : "他是贫道的师兄，三代弟子中也就他会使太极剑法。",
                "谷虚" : "谷虚师兄是三代弟子中的佼佼者，近年来负责在山上主持武当事务。",
                "谷虚道长" : "谷虚师兄是三代弟子中的佼佼者，近年来负责在山上主持武当事务。",
                "清虚道长" : "贫道便是清虚，不知这位"+ RANK_D->query_respect(this_player())+"有何见教？",
                "凌虚" : "凌虚师弟在遇真宫，负责制造香火。",
                "凌虚道长" : "凌虚师弟在遇真宫，负责制造香火。",
                "制香" : "凌虚师弟在遇真宫，负责制造香火。",
                "制香道长" : "凌虚师弟在遇真宫，负责制造香火。",
                "灵虚" : "灵虚师弟在山门，负责接待来客。",
                "灵虚道长" : "灵虚师弟在山门，负责接待来客。",
                "知客" : "灵虚师弟在山门，负责接待来客。",
                "知客道长" : "灵虚师弟在山门，负责接待来客。",
                "成高" : "他是贫道的师侄，以前曾与贫道在西域住过十几年，现在负责看守榔梅园。",
                "成高道长" : "他是贫道的师侄，以前曾与贫道在西域住过十几年，现在负责看守榔梅园。",
                "守园" : "他是贫道的师侄，以前曾与贫道在西域住过十几年，现在负责看守榔梅园。",
                "守园道长" : "他是贫道的师侄，以前曾与贫道在西域住过十几年，现在负责看守榔梅园。",
                "炸药" : "嗯……这我不大清楚，你得去问成高师侄。",
                "火药" : "嗯……这我不大清楚，你得去问成高师侄。",
                "制造炸药" : "嗯……这我不大清楚，你得去问成高师侄。",
                "制造火药" : "嗯……这我不大清楚，你得去问成高师侄。",
                "机关" : "贫道曾在西域向当地工匠学过机关削器之术。",
                "机关削器" : "贫道曾在西域向当地工匠学过此术。",
        ]));

        set("book_count", 1);

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}


string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player()) )
            || fam["family_name"] != "武当派")
        {
                return RANK_D->query_respect(this_player()) +
                       "与本派素无来往，不知此话从何谈起？";
        }

        if (query("book_count") < 1)
                return "你来晚了，本派的道德真经不在此处。";

        addn("book_count", -1);
        ob = new("/clone/book/daodejing-ii");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿回去好好钻研。";
}
