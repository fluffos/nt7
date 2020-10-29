// This program is a part of NT MudLIB
// murongfu.c 慕容复

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;
inherit F_COAGENT;

string ask_dan1();

void create()
{
        set_name("慕容复", ({ "murong fu", "murong", "fu" }));
        set("long", @LONG
他是姑苏慕容的传人，是慕容博之子，所谓南慕容、北乔峰。
此人正是和乔峰齐名的慕容家高手。他容貌俊雅，风度过人，
的确非寻常人可比。
LONG );
        set("titile", "姑苏慕容");
        set("gender", "男性");
        set("age", 25);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 27);
        set("int", 29);
        set("con", 31);
        set("dex", 28);
        set("per", 28);

        set("qi", 4100);
        set("max_qi", 4100);
        set("jing", 2100);
        set("max_jing", 2100);
        set("neili", 4900);
        set("max_neili", 4900);
        set("jiali", 80);
        set("level", 30);
        set("combat_exp", 1750000);

        set_skill("force", 180);
        set_skill("literate", 140);
        set_skill("cuff", 180);
        set_skill("sword", 180);
        set_skill("blade", 180);
        set_skill("dodge", 180);
        set_skill("strike", 180);
        set_skill("parry", 200);

        set_skill("shenyuan-gong", 180);
        set_skill("zihui-xinfa", 200);
        set_skill("xingyi-zhang", 300);
        set_skill("douzhuan-xingyi", 200);
        set_skill("beidou-xianzong", 180);
        set_skill("qixing-quan", 180);
        set_skill("murong-jianfa", 180);
        set_skill("murong-daofa", 180);
        set_skill("martial-cognize", 140);

        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("strike", "xingyi-zhang");
        map_skill("blade", "murong-daofa");
        map_skill("sword", "murong-jianfa");

        prepare_skill("cuff", "qixing-quan");

        set("inquiry",
        ([
                "name"       : "我就是以彼之道，还施彼身的姑苏慕容复。\n",
                "here"       : "这里是大名鼎鼎的燕子坞，难道你没有听说过？\n",
                "rumors"     : "家父突染恶疾，我连他老人家最后一面都没见到，此事顶有蹊跷！\n",
                "姑妈"       : "我的姑妈住在曼佗罗山庄，那里有闻名天下的娘缳玉洞。\n",
                "王语嫣"    : "语嫣是我表妹，我一直把她当小妹妹看待。\n",
                "南慕容"    : "“南慕容北乔峰”，那是江湖上的朋友抬爱了！\n",
                "慕容复"    : "那是贱名。请教尊驾是？\n",
                "邓百川"    : "你问邓大哥啊？他在他青风庄上呢。\n",
                "公冶乾"    : "公冶二哥把信鸽传书一编码，就没几个人读得懂了。\n",
                "包不同"    : "包三哥最爱抬杠了，你见了他还是闭嘴的好。\n",
                "风波恶"    : "风四哥最是豪爽了，他从不与人计较什么。\n",
                // "还施水阁"   : (: ask_ge :),
                // "王语嫣"     : (: ask_wang :),
                // "归元丹"     : (: ask_dan :),
                "玉露清新散" : (: ask_dan1 :),
                // "武学修养"   : (: ask_learn :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: perform_action, "parry.yi" :),
                (: perform_action, "blade.feng" :),
                (: perform_action, "cuff.zhai" :),
        }));

        create_family("慕容世家", 16, "传人");

        set("coagents", ({
                ([ "startroom" : "/d/yanziwu/canheju",
                   "id"        : "murong bo" ]),
        }));

        set("master_ob",3);
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 200);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>0 )
        {
                command("say 我慕容世家向来不和你们这些所谓正道人士交往。");
                command("say 你还是请回吧！");
                return;
        }


        command("nod");
        command("say 今日我就暂且收下你，日后定须刻苦练武，光复大燕。");
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

        case "摘星式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qixing-quan/zhai",
                           "name"    : "摘星式",
                           "sk1"     : "qixing-quan",
                           "lv1"     : 40,
                           "gongxian": 140,
                           "shen"    : -4000, ]));
                break;

        case "剑转七星" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/xing",
                           "name"    : "剑转七星",
                           "sk1"     : "murong-jianfa",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "白虹贯日" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-jianfa/hong",
                           "name"    : "白虹贯日",
                           "sk1"     : "murong-jianfa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "日月同辉" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/riyue",
                           "name"    : "日月同辉",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     :  40,
                           "gongxian":  200,
                           "shen"    : -6000, ]));
                break;

        case "星光点点" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xingyi-zhang/xing",
                           "name"    : "星光点点",
                           "sk1"     : "xingyi-zhang",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        case "刀影掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/murong-daofa/ying",
                           "name"    : "刀影掌",
                           "sk1"     : "murong-daofa",
                           "lv1"     : 80,
                           "force"   : 90,
                           "gongxian": 320,
                           "shen"    : -9000, ]));
                break;

        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}

*/

string ask_dan1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "姑苏慕容" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if (query("san_count") < 1)
                return "你来晚了，本派的玉露清新散不在此处。";
        addn("san_count", -1);
        ob = new("/clone/medicine/nostrum/yulusan");
        ob->move(this_player());
        return "好吧，这玉露清新散你拿去吧。";
}
