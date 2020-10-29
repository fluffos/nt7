// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("狄云", ({ "di yun", "di","yun" }));
        set("long",
                "他就是"+HIR"血刀门"NOR+"弟子狄云。\n"
                "他今年看起来倒满和蔼的。\n");
        set("gender", "男性");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);
        set("level", 40);
        set("combat_exp", 5000000);
        set("score", 60000);

        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("hand", 600);
        set_skill("mizong-neigong", 600);
        set_skill("dashou-yin", 600);
        set_skill("unarmed", 600);
        set_skill("blade", 600);
        set_skill("literate", 600);
        set_skill("xuehai-mogong", 600);
        set_skill("xuedao-daofa", 600);
        set_skill("force", 600);
        set_skill("shenkong-xing", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("liancheng-jianfa", 600);
        set_skill("shenzhaojing", 600);
         set_skill("xueying-dafa", 1000); 

        map_skill("unarmed", "shenjingzhao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("force", "shenzhaojing");
        map_skill("blade", "xuedao-daofa");
        map_skill("parry", "xuedao-daofa");
        map_skill("dodge", "shenkong-xing");
        map_skill("sword", "liancheng-jianfa");

        create_family("密宗", 5, "弟子");

        set("master_ob", 3);
        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( query("shen", ob)<100000 )
        {
                command("sigh");
                command("say 我已经封门不收弟子了，你请回吧。");
                return;
        }
        if ((int)ob->query_skill("xuehai-mogong", 1) < 120) {
                command("say 练血刀刀法最重内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在血海魔功上多下点功夫？");
                return;

        }
        if ((int)ob->query_skill("lamaism", 1) < 100) {
                command("say 入我血刀门，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +


                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("say 好吧，看你还是个人才，血刀门看来得靠你了。");
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "无影神拳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhaojing/ying",
                           "name"    : "无影神拳",
                           "sk1"     : "shenzhaojing",
                           "lv1"     : 100,
                           "sk2"     : "unarmed",
                           "lv2"     : 100,
                           "gongxian": 800, ]));
                break;

        case "无影拳舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhaojing/wu",
                           "name"    : "无影拳舞",
                           "sk1"     : "shenzhaojing",
                           "lv1"     : 120,
                           "sk2"     : "unarmed",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "耳光式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/erguang",
                           "name"    : "耳光式",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 600, ]));
                break;

        case "刺肩式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/cijian",
                           "name"    : "刺肩式",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "去剑势" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liancheng-jianfa/qujian",
                           "name"    : "去剑势",
                           "sk1"     : "liancheng-jianfa",
                           "lv1"     : 120,
                           "sk2"     : "sword",
                           "lv2"     : 120,
                           "gongxian": 600, ]));
                break;

        default:
                return 0;
        }
}
