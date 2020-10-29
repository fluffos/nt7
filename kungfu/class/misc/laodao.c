// laodao.c 老道

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("老道", ({ "lao dao", "dao" }));
        set("long",  "他看上去仙风道骨，相貌不俗。\n");
        set("gender", "男性");
        set("age", 64);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 33);
        set("int", 33);
        set("con", 36);
        set("dex", 32);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 25000000);
        set("score", 10000000);

        set_skill("force", 2800);
        set_skill("xiantian-gong", 2800);
        set_skill("sword", 2600);
        set_skill("quanzhen-jian",2600);
        set_skill("dodge", 2600);
        set_skill("jinyan-gong", 2600);
        set_skill("parry", 2700);
        set_skill("strike", 2700);
        set_skill("chongyang-shenzhang", 2700);
        set_skill("haotian-zhang", 2700);
        set_skill("literate", 1600);
        set_skill("finger", 2500);
        set_skill("taoism", 3000);
        set_skill("finger", 2600);
        set_skill("zhongnan-zhi", 2700);
        set_skill("medical", 2700);
        set_skill("liandan-shu", 2700);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhoangnan-zhi");
        map_skill("strike", "haotian-zhang");

        prepare_skill("finger","sun-finger");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 0, "前辈");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.hua" :),
                (: perform_action, "strike.ju" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
