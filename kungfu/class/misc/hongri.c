// hongri.c 红日法王

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("红日法王", ({ "hongri fawang", "fawang" }));
        set("long",  "他看上去是一个藏僧，胸前绣着一个大大的太阳。\n");
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

        set_skill("lamaism", 2200);
        set_skill("literate", 800);
        set_skill("force", 2300);
        set_skill("parry", 2200);
        set_skill("blade", 2250);
        set_skill("xuedao-daofa", 2250);
        set_skill("sword", 1800);
        set_skill("mingwang-jian", 1800);
        set_skill("dodge", 2100);
        set_skill("mizong-neigong", 2300);
        set_skill("xuehai-mogong", 2300);
        set_skill("shenkong-xing", 2100);
        set_skill("hand", 2000);
        set_skill("dashou-yin", 2000);
        set_skill("cuff", 2000);
        set_skill("yujiamu-quan", 2000);

        map_skill("force", "xuehai-mogong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("血刀门", 0, "法王");
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.shendao" :),
                (: perform_action, "blade.xueyu" :),
                (: perform_action, "hand.jingang" :),
                (: perform_action, "cuff.chen" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/d/xueshan/obj/y-jiasha")->wear();
        // carry_object("/d/xuedao/obj/xblade")->wield();
        carry_object("/clone/weapon/blade")->wield();
}
