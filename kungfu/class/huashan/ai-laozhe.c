// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "qizong.h"

void create()
{
        set_name("矮老者", ({ "ai laozhe", "ai" }));
        set("title", HIG "华山第十二代长老" NOR);
        set("long", "他就是华山的长老矮老者。一张严肃"
                    "威严的脸，望而生畏。\n");
        set("gender", "男性");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 35);
        set("con", 31);
        set("dex", 32);
        set("age", 66);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 2600);
        set("max_jing", 2600);
        set("neili", 5200);
        set("max_neili", 5200);
        set("jiali", 70);
        set("level", 30);
        set("combat_exp", 1900000);
        set("score", 70000);

        set_skill("cuff", 610);
        set_skill("force", 610);
        set_skill("blade", 610);
        set_skill("sword", 620);
        set_skill("dodge", 610);
        set_skill("parry", 600);
        set_skill("strike", 610);
        set_skill("zixia-shengong", 610);
        set_skill("huashan-neigong", 610);
        set_skill("huashan-shenfa", 620);
        set_skill("huashan-quan", 650);
        set_skill("huashan-zhang", 650);
        set_skill("poyu-quan", 610);
        set_skill("fanliangyi-dao", 610);
        set_skill("huashan-sword", 620);
        set_skill("hunyuan-zhang", 610);
        set_skill("feiyan-huixiang", 610);
        set_skill("literate", 640);
        set_skill("jianyi", 610);
        set_skill("martial-cognize", 610);

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "fanliangyi-dao");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "huashan-sword");
        map_skill("strike", "hunyuan-zhang");

        create_family("华山派", 12, "弟子");

        set("inquiry", ([
                "紫霞神功" : "那是本门无上的内功心法。据说紫霞密笈缺了最後一页，可惜我至今仍无法叁透，唉！\n",
                "密室"     : "你胡说八道些甚麽？\n",
        ]));

        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "blade.sanshen" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "cuff.leidong" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string ob_fam;

        ob_fam=query("family/family_name", ob);
        if (! permit_recruit(ob))
                return;

        if (ob_fam == "华山派" && ob->query_skill("zixia-shengong", 1) < 120)
        {
                command("say 我看你的紫霞神功还没学到家吧，本派有本的"
                        "紫霞秘籍，你可曾研读？");
                return;
        }

        if ((int)ob->query_skill("sword", 1) < 150)
        {
                command("say 我看你的剑法还没学到家吧，基本剑法都不打"
                        "好基础，谈什么上乘剑术。");
                return;
        }

        if (ob_fam == "华山派" && (int)ob->query_skill("huashan-sword", 1) < 150 ||
            ob_fam == "华山剑宗" && (int)ob->query_skill("kuangfeng-jian", 1) < 150)
        {
                command("say 华山剑法和狂风剑法是本派弟子必须精通的武技，多练练"
                        "剑术你再来。");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say 我华山派乃是堂堂名门正派，对弟子要求极严"
                        "，在德行方面，你还做得不够啊！");
                return;
        }

        if (ob_fam == "华山剑宗")
        {
                command("say 你看看你，也成了剑气之争的受害者，好好研习武功，少些纷争。");
                delete("family", ob);
        }

        command("say 好吧，我就收下你了，不要丢我们华山派的脸。");
        command("recruit " + query("id", ob));
        if( query("class", ob) != "fighter" )
                set("class", "fighter", ob);
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

        case "华岳三神峰" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fanliangyi-dao/sanshen",
                           "name"    : "华岳三神峰",
                           "sk1"     : "fanliangyi-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 26000, ]));
                break;

        case "双刀和璧" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fanliangyi-dao/hebi",
                           "name"    : "华岳三神峰",
                           "sk1"     : "fanliangyi-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 26000, ]));
                break;

        case "混元无极" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hunyuan-zhang/wuji",
                           "name"    : "混元无极",
                           "sk1"     : "hunyuan-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1600,
                           "shen"    : 28000, ]));
                break;

        case "封闭手" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/feng",
                           "name"    : "封闭手",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 600,
                           "shen"    : 30000, ]));
                break;

        case "雷动九天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/lei",
                           "name"    : "雷动九天",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "破石一击" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/po",
                           "name"    : "破石一击",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "剑掌五连环" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/lian",
                           "name"    : "剑掌五连环",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "截手式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/jie",
                           "name"    : "截手式",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        default:
                return 0;
        }
}

#include "zhanglao.h"
