// This program is a part of NT MudLIB
// ma.c 马大元

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();

void create()
{
        set_name("马大元", ({ "ma dayuan", "ma", "dayuan" }));
        set("long", @LONG
这是一个四十多岁的精壮汉子，身材魁梧，双
目如电。此人就是丐帮副帮主马大元。
LONG);
        set("nickname", CYN "铁爪锁喉" NOR);
        set("title", "丐帮副帮主");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3500);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 220);
        set("combat_exp", 2500000);
        set("level", 30);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 200);
           set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 200);
        set_skill("claw", 240);
        set_skill("suohou-gong", 240);
        set_skill("strike", 200);
        // set_skill("tongchui-zhang", 240);
        set_skill("dragon-strike", 200);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("fumo-zhang", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 260);
        set_skill("martial-cognize", 240);

        set("no_teach", ([
                "dagou-bang"    : "打狗棒法向来只有继位帮主能够学"
                                  "习，要学去找帮主。",
                "dragon-strike" : "降龙十八掌向来只有和帮主学习。",
        ]));

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "chanquan");
        map_skill("strike", "dragon-strike");
        map_skill("staff", "dagou-bang");
        map_skill("claw", "suohou-gong");
        map_skill("parry", "suohou-gong");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("claw", "suohou-gong");

        create_family("丐帮", 18, "副帮主");

        set("inquiry", ([
                "铁爪锁喉" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.suo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你的江湖经验不够，还是先向各位长老学习吧。");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say 你在本帮的地位太低，还是先向各位长老学习吧。");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say 我的武艺以刚猛为主，你膂力不行，还是算了吧。");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say 你的内功火候还不够，还是先向各位长老学习吧。");
                return;
        }
        command("nod");
        command("say 我今日便收你为徒，倘若勤恳努力，将来必有一番作为。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/suohou-gong/suo", me) )
                return "自己下去练习，别老是纠缠不休。";

        if( query("family/family_name", me) != query("family/family_name") )
                return "那是江湖上朋友送的外号，你问这个干嘛？";

        if (me->query_skill("suohou-gong", 1) < 1)
                return "你学过锁喉功吗？不学哪来绝招。";

        if( query("family/gongji", me)<400 )
                return "你在丐帮内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<20000 )
                return "你侠义正事做得不够，这招我暂时还不能传你。";

        if (me->query_skill("suohou-gong", 1) < 150)
                return "你的锁喉功还不到家，要多练练。";

        message_sort(HIY "\n$n" HIY "笑了笑，将$N" HIY "招至身旁，轻"
                     "声在$N" HIY "耳边低声吩咐了几句，不时还握拳成爪"
                     "比划演示，全是锁喉功绝招的精微要诣，$N" HIY "一"
                     "边听一边不住地点头。\n\n" NOR, me, this_object());

        command("nod");
        command("say 这便是锁喉功的要诣所在，可记清楚了？");
        tell_object(me, HIC "你学会了「铁爪锁喉」。\n" NOR);

        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("suohou-gong"))
                me->improve_skill("suohou-gong", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/suohou-gong/suo", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}
