// guoxiang.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("郭襄", ({ "guo xiang", "guo" }));
        set("long", "她是峨嵋派的开山祖师。\n");
        set("nickname", HIM "小东邪" NOR);
        set("gender", "女性");
        set("age", 24);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "strike.bashi" :),
                (: exert_function, "recover" :),
        }));

        set("str", 29);
        set("int", 39);
        set("con", 37);
        set("dex", 37);

        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 70000);
        set("max_neili", 70000);
        set("jingli", 150);

        set("combat_exp", 24000000);
        set("score", 10000000);

        set_skill("force", 2700);
        set_skill("dodge", 2700);
        set_skill("finger", 2700);
        set_skill("parry", 2700);
        set_skill("strike", 2700);
        set_skill("sword", 2700);
        set_skill("literate", 2500);
        set_skill("mahayana", 2500);
        set_skill("buddhism", 2500);
        set_skill("jinding-zhang", 2700);
        set_skill("tiangang-zhi", 2700);
        set_skill("huifeng-jian", 2700);
        set_skill("zhutian-bu", 2700);
        set_skill("linji-zhuang", 2700);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        create_family("峨嵋派", 1, "开山祖师");

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}
