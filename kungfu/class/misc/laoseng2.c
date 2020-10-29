// laoseng.c 雪山老僧

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("雪山老僧", ({ "lao seng", "seng" }));
        set("long",  "此人一副雪山派的打扮，神采飘逸，一看便是得道高僧。\n");
        set("gender", "男性");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 33);
        set("int", 36);
        set("con", 34);
        set("dex", 33);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 25000000);
        set("score", 10000000);

        set_skill("force", 2700);
        set_skill("xiaowuxiang", 2700);
        set_skill("mizong-neigong", 2700);
        set_skill("dodge", 2400);
        set_skill("shenkong-xing", 2400);
        set_skill("parry", 2700);
        set_skill("sword", 2200);
        set_skill("mingwang-jian", 2200);
        set_skill("lamaism", 2500);
        set_skill("literate", 2200);
        set_skill("strike", 2700 );
        set_skill("huoyan-dao", 2700);
        set_skill("cuff", 2600);
        set_skill("yujiamu-quan", 2600);
        set_skill("hand", 2700);
        set_skill("dashou-yin", 2700);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("hand", "dashou-yin");

        create_family("密宗", 0, "高僧");
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bei" :),
                (: perform_action, "strike.fen" :),
                (: perform_action, "cuff.chen" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
}
