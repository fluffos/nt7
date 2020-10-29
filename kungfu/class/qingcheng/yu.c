// yu.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;
#include "qingcheng.h"

void create()
{
        set_name("余沧海", ({ "yu canghai", "yu", "canghai" }));
        set("gender", "男性");
        set("age", 52);
        set("long", "他身形矮小，可是神情凝重，俨然一派大宗师气。\n");
        set("class", "taoist");
        set("combat_exp", 3000000);
        set("class", "taoist");
        set("shen_type", -1);
        set("max_neili", 2500);
        set("neili", 2500);
        set("max_jing", 1500);
        set("max_qi", 2500);
        set("jiali", 250);
        set("apprentice_available", 3);

        set_skill("sword", 600);
        set_skill("dodge", 600);
        set_skill("parry", 600);
        set_skill("strike", 600);
        set_skill("unarmed", 600);
        set_skill("force", 600);
        set_skill("hammer", 600);
        set_skill("throwing", 600);
        set_skill("literate", 600);
//        set_skill("qingzi9da", 150);
        set_skill("qingzi9da", 600);
//        set_skill("chengzi18po", 150);
        set_skill("chengzi18po", 600);
        set_skill("bixie-sword", 600);
        set_skill("songfeng-jian", 600);
        set_skill("chuanhua", 600);
        set_skill("wuying-leg", 600);
        set_skill("cuixin-zhang", 600);
        set_skill("qingming-xuangong", 600);
        map_skill("force", "qingming-xuangong");
        map_skill("unarmed", "wuying-leg");
        map_skill("strike", "cuixin-zhang");
        map_skill("dodge", "chuanhua");
        map_skill("parry", "songfeng-jian");
        map_skill("sword", "songfeng-jian");
        prepare_skill("unarmed", "wuying-leg");
        prepare_skill("strike", "cuixin-zhang");

        set("no_get",1);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.dieying" :),
                (: perform_action, "strike.cuixin" :),
                (: perform_action, "unarmed.fanti" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        create_family("青城派", 5, "掌门");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/d/qingcheng/obj/key");
}
void attempt_apprentice(object ob)
{
        return;
        if (! permit_recruit(ob))
                return;

        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 老道今天已经收了三个弟子，不想再收徒了。");
        }
}

void do_recruit(object ob)
{
        if( query("int", ob)<20 )
                command("say 我青城派以暗器见长，依我看"+RANK_D->query_respect(ob)+"不适合于学暗器。");
        else {
                command("say 好，很好。");
                command("recruit "+query("id", ob));
        }
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        addn("apprentice_availavble", -1);
}
