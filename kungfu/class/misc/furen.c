// furen.c 老夫人

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("老夫人", ({ "lao furen", "furen" }));
        set("long",  "她看上去年纪已经不小了，不过从眉角中依然可看出当年的风姿。\n");
        set("gender", "女性");
        set("age", 69);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 37);
        set("int", 32);
        set("con", 35);
        set("dex", 36);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 25000000);
        set("score", 10000000);

        set_skill("force", 2700);
        set_skill("literate", 2200);
        set_skill("unarmed", 2600);
        set_skill("cuff", 2700);
        set_skill("finger", 2700);
        set_skill("strike", 2600);
        set_skill("hand", 2600);
        set_skill("claw", 2600);
        set_skill("club", 2600);
        set_skill("sword", 2700);
        set_skill("blade", 2600);
        set_skill("staff", 2600);
        set_skill("dodge", 2600);
        set_skill("parry", 2700);
        set_skill("shenyuan-gong", 2700);
        set_skill("douzhuan-xingyi", 2700);
        set_skill("beidou-xianzong", 2700);
        set_skill("canhe-zhi", 2700);
        set_skill("qixing-quan", 2700);
        set_skill("murong-jianfa", 2700);

        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "beidou-xianzong");
        map_skill("cuff",  "qixing-quan");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("finger", "canhe-zhi");
        map_skill("sword", "murong-jianfa");

        prepare_skill("finger", "canhe-zhi");
        prepare_skill("cuff", "qixing-quan");

        create_family("慕容世家", 0, "族人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.qixing" :),
                (: perform_action, "finger.ci" :),
                (: perform_action, "finger.lan" :),
                (: perform_action, "finger.zhi" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
