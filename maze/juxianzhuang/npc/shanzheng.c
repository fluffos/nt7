// shanzheng.c 单正

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("单正", ({ "shan zheng", "shan" }));

        set("gender", "男性");
        set("age", 62);
        set("long", "他体态魁梧，相貌威严，长的一副童颜鹤发。\n");
        set("attitude", "peaceful");

        set("nickname", HIR "铁面判官" NOR);

        set("str", 35);
        set("int", 36);
        set("con", 31);
        set("dex", 30);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.duan" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("shen_type", 1);

        set("qi", 300000);
        set("max_qi", 300000);
        set("jing", 150000);
        set("max_jing", 150000);
        set("neili", 450000);
        set("max_neili", 450000);
        set("jiali", 500);

        set("combat_exp", 800000000);
        set("score", 5000000);

        set_skill("force", 850);
        set_skill("huntian-qigong", 850);
        set_skill("dodge", 860);
        set_skill("feiyan-zoubi", 850);
        set_skill("parry", 850);
        set_skill("blade", 850);
        set_skill("unarmed", 850);
        set_skill("taiji-quan", 850);
        set_skill("wuhu-duanmendao", 850);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");

        set_temp("apply/attack", 800);
        set_temp("apply/defense", 800);
        set_temp("apply/damage", 2000);
        set_temp("apply/unarmed_damage", 2000);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
