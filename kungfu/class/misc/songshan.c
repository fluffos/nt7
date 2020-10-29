#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("怪侠", ({ "guai xia", "guai", "xia" }));
        set("long",  "他就是嵩山派的高手人称怪侠。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 32);
        set("int", 33);
        set("con", 32);
        set("dex", 31);

        set("max_qi", 60000);
        set("max_jing", 3000);
        set("neili", 7500);
        set("max_neili", 7500);
        set("jiali", 150);
        set("combat_exp", 2500000);
        set("score", 10000000);

        set_skill("cuff", 3000);
        set_skill("strike", 3000);
        set_skill("sword", 3000);
        set_skill("force", 3000);
        set_skill("parry", 3000);
        set_skill("dodge", 3000);
        set_skill("lingxu-bu", 3000);
        set_skill("songshan-jian", 3000);
        set_skill("lingyun-jian", 3000);
        set_skill("chuanyue-jian", 3000);
        set_skill("jiuqu-jian", 3000);
        set_skill("poyang-jian", 3000);
        set_skill("songshan-xinfa", 3000);
        set_skill("hanbing-zhenqi", 3000);
        set_skill("hanbing-zhang", 3000);
        set_skill("songshan-zhang", 3000);
        set_skill("songshan-quan", 3000);
        set_skill("literate", 220);
        set_skill("martial-cognize", 2000);

        map_skill("force", "hanbing-zhenqi");
        map_skill("sword", "poyang-jian");
        map_skill("parry", "poyang-jian");
        map_skill("strike", "hanbing-zhang");
        map_skill("cuff", "songshan-quan");
        map_skill("dodge", "lingxu-bu");

        prepare_skill("strike", "hanbing-zhang");

        create_family("嵩山派", 0, "高人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "strike.heng" :),
                (: perform_action, "strike.han" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "freezing" :)
        }));

        set_temp("apply/attack", 1000);
        set_temp("apply/damage", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 2000);

        setup();

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
