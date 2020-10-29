// This program is a part of NITAN MudLIB
// yu.c 俞莲舟

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_me();

void create()
{
        set_name("俞莲舟", ({ "yu lianzhou", "yu" }));
        set("nickname", "武当二侠");
        set("long",
                "他就是张三丰的二弟子俞莲舟。\n"
                "他今年五十岁，身材魁梧，气度凝重。\n"
                "虽在武当七侠中排名第二，功夫却是最精。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 32);
        set("dex", 32);

        set("max_qi", 4800);
        set("max_jing", 2400);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 100);
        set("combat_exp", 1600000);
        set("score", 50000);

        set_skill("force", 195);
        set_skill("yinyun-ziqi", 195);
        set_skill("taiji-shengong", 195);
        set_skill("dodge", 170);
        set_skill("tiyunzong", 170);
        set_skill("unarmed", 180);
        set_skill("taiji-quan", 180);
        set_skill("strike", 180);
        set_skill("wudang-zhang", 180);
        set_skill("hand", 180);
        set_skill("paiyun-shou", 180);
        set_skill("claw", 180);
        set_skill("huzhua-shou", 180);
        set_skill("parry", 180);
        set_skill("sword", 185);
        set_skill("wudang-jian", 185);
        set_skill("taiji-jian", 185);
        set_skill("taoism", 160);
        set_skill("literate", 100);
        set_skill("medical", 160);
        set_skill("liandan-shu", 160);

        set("no_teach", ([
                "taiji-shengong" : "要想学习太极神功请向张真人请教。",
                "taiji-jian"     : "太极剑必须张真人亲传。",
                "taiji-quan"     : "太极拳必须张真人亲传。",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("hand", "paiyun-shou");
        map_skill("claw", "huzhua-shou");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("武当派", 2, "弟子");

        set("inquiry", ([
                "虎爪绝户手": (: ask_me :),
                "绝户": (: ask_me :),
                "绝招"  : (: ask_me :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.sui" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<15000 )
        {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 80)
        {
                command("say 我武当派最注重内功心法" + RANK_D->query_respect(ob)+
                        "是否应该在武当心法上多下点功夫啊?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 80)
        {
                command("say 习武是为了强身健体，一味的练武是不可取的。");
                command("say 我看你还需要在修身养性方面多锻炼锻炼，以提高"
                        "你的道德心法。");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("say 希望你能好好用功，发扬我武当精神！");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huzhua-shou/juehu", me) )
                return "这一招你不是已经会了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "不是我们武当派的人，何出此言？";

        if (me->query_skill("huzhua-shou", 1) < 1)
                return "你连虎爪绝户手都没学，还谈什么绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你为我武当派效力还不够，这招我先不忙传你。";

        if( query("shen", me)<100000 )
                return "这一招太过阴恨，如果被你用去我恐怕不放心！";

        if (me->query_skill("force") < 180)
                return "你的内功的修为不够，练高了再来吧。";

        if (me->query_skill("huzhua-shou", 1) < 120)
                return "你的虎爪绝户手还不到家，还是自己先下去多多练习吧。";

        message_vision(HIY "$n" HIY "叹了口气，在$N" HIY "耳边轻"
                       "声说了几句虎爪绝户手\n的精要，隔了良久，"
                       "又叹了一口气。\n" NOR, me, this_object());
        command("sigh");
        command("say 这便是绝户手的精要所在，你懂了多少？");
        command("say 绝户手太易使人重残，因而使用前一定要慎重考虑。");
        tell_object(me, HIC "你学会了「绝户神抓」。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("huzhua-shou"))
                me->improve_skill("huzhua-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huzhua-shou/juehu", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
