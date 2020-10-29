#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("铁掌山隐士", ({ "yin shi", "yin", "shi" }));
        set("long",  "他就是铁掌派的高手，据说长年隐藏于山中。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
          set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("combat_exp", 4000000);
        set("score", 40000);

        set_skill("force", 600);
        set_skill("tiezhang-xinfa", 600);
        set_skill("tianlei-shengong", 600);
        set_skill("dodge", 600);
        set_skill("dengping-dushui", 600);
        set_skill("strike", 600);
        set_skill("parry", 600);
        set_skill("tie-zhang", 600);
        set_skill("chuanxin-zhang", 600);
        set_skill("cuff", 600);
        set_skill("tiexian-quan", 600);
        set_skill("unarmed", 600);
        set_skill("feilong-zhang", 600);
        set_skill("staff", 600);
        set_skill("blade", 600);
        set_skill("tianlei-dao", 600);
        set_skill("club", 600);
        set_skill("zhongping-qiang", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "tianlei-shengong");
        map_skill("unarmed", "chuanxin-zhang");
        map_skill("strike", "tie-zhang");
        map_skill("cuff", "tiexian-quan");
        map_skill("parry", "tie-zhang");
        map_skill("dodge", "dengping-dushui");
        map_skill("staff", "feilong-zhang");
        prepare_skill("strike", "tie-zhang");
        create_family("铁掌帮", 0, "隐士");
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.juesha" :),
                (: perform_action, "strike.lei" :),
                (: perform_action, "strike.yin" :),
                (: perform_action, "cuff.kai" :),
                (: perform_action, "unarmed.zhui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );
        setup();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
