// popo.c 婆婆

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("老婆婆", ({ "lao popo", "popo" }));
        set("long",  "这是古墓派不出世的高人，江湖上鲜有人知。\n");
        set("gender", "女性");
        set("age", 53);
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
        set("combat_exp", 55000000);
        set("score", 10000000);

        set_skill("force", 2800);
        set_skill("yunv-xinfa", 2800);
        set_skill("sword", 2700);
        set_skill("yunv-jian", 2700);
        set_skill("quanzhen-jian", 2700);
        set_skill("dodge", 2500);
        set_skill("yunv-shenfa", 2500);
        set_skill("parry", 2700);
        set_skill("unarmed",2500);
        set_skill("meinv-quan", 2500);
        set_skill("strike", 1600);
        set_skill("fireice-strike", 1600);
        set_skill("literate", 1800);
        set_skill("taoism", 2400);
        set_skill("medical", 2700);
        set_skill("yunv-xinjing", 2700);
        set_skill("throwing", 2600);
        set_skill("yufeng-zhen", 2600);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "fireice-strike");

        prepare_skill("unarmed", "meinv-quan");
        prepare_skill("strike", "fireice-strike");

        create_family("古墓派", 0, "高人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "uanrmed.you" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
