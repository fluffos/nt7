#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("绝情谷隐士", ({ "yin shi", "yin", "shi" }));
        set("long",  "他就是绝情谷的高手，据说长年隐藏于山中。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
         set("shen_type", 0);
        set("age", 40);
        set("str", 35);
        set("con", 35);
        set("int", 25);
        set("dex", 35);
        set("max_qi", 6000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 3000000);
        set_skill("force", 240);
        set_skill("jueqing-xinfa", 240);
        set_skill("fenxin-jue", 240);
        set_skill("dodge", 240);
        set_skill("jueqing-shenfa", 240);
        set_skill("strike", 240);
        set_skill("jueqing-zhang", 240);
        set_skill("guhong-zhang", 240);
        set_skill("cuff", 240);
        set_skill("pokong-quan", 240);
        set_skill("medical", 240);
        set_skill("jueqing-yaoli", 240);
        set_skill("sword", 260);
        set_skill("yinyang-ren", 260);
        set_skill("zilei-jian", 260);
        set_skill("guxing-jian", 260);
        set_skill("blade", 260);
        set_skill("tianjue-dao", 260);
        set_skill("luoyun-dao", 260);
        set_skill("poguang-dao", 260);
        set_skill("parry", 240);
        set_skill("literate", 240);
        set_skill("medical", 240);
        set_skill("jueqing-yaoli", 240);
        set_skill("martial-cognize", 220);

        map_skill("strike", "jueqing-zhang");
        map_skill("sword", "yinyang-ren");
        map_skill("blade", "yinyang-ren");
        map_skill("force", "fenxin-jue");
        map_skill("dodge", "jueqing-shenfa");
        map_skill("parry", "yinyang-ren");
        map_skill("parry", "jueqing-yaoli");

        prepare_skill("strike", "jueqing-zhang");

        create_family("绝情谷", 0, "隐士");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.huan" :),
                (: perform_action, "sword.heng" :),
                (: perform_action, "strike.hun" :),
                (: perform_action, "strike.wan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}
