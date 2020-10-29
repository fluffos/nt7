// wangjiantong.c 汪剑通

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("汪剑通", ({"wang jiantong", "wang", "jiantong"}));

        set("gender", "男性");
        set("age", 54);
        set("long", "他体态魁梧，相貌威严。\n");
        set("attitude", "peaceful");
        
        set("str", 35);
        set("int", 30);
        set("con", 33);
        set("dex", 31);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xianglong" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.ban" :),
                (: exert_function, "recover" :),
        }) );

        set("qi", 60000);
        set("max_qi", 60000);
        set("jing", 30000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);

        set("combat_exp", 56000000);
        set("score", 10000000);

        set_skill("force", 2700);
        set_skill("huntian-qigong", 2700);
        set_skill("dodge", 2500);
        set_skill("feiyan-zoubi", 2500);
        set_skill("parry", 2500);
        set_skill("staff", 2700);
        set_skill("strike", 2700);
        set_skill("dragon-strike", 2700);
        set_skill("dagou-bang", 2700);
        set_skill("begging", 2000);
        set_skill("checking", 2000);
        set_skill("training", 1800);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "dragon-strike");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");

        create_family("丐帮", 0, "名宿");

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
}
