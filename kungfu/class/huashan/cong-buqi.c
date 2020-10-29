// This program is a part of NITAN MudLIB
// cong-buqi.c  丛不弃

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("丛不弃", ({ "cong buqi", "cong" }) );
        set("gender", "男性");
        set("class", "swordsman");
        set("title", "华山剑宗第十三代弟子");
        set("age", 52);
        set("long",
                "丛不弃是华山剑宗高手。\n");
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 4000);
        set("max_neili", 2400);
        set("jiali", 30);
        set("max_qi",2000);
        set("max_jing",1200);
        set("level", 20);
        set("combat_exp", 1000000);
        set("shen", -200000);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.long" :),
                (: exert_function, "powerup" :),
        }) );

        set_skill("unarmed", 240);
        set_skill("cuff", 240);
        set_skill("strike", 240);
        set_skill("hunyuan-zhang", 240);
        set_skill("sword", 280);
        set_skill("force", 200);
        set_skill("parry", 280);
        set_skill("dodge", 240);
        set_skill("literate", 150);
        set_skill("huashan-sword", 280);
        set_skill("kuangfeng-jian", 380);
        set_skill("huashan-neigong", 200);
        set_skill("poyu-quan", 200);
        set_skill("huashan-quan", 240);
        set_skill("huashan-shenfa", 240);
        set_skill("martial-cognize", 220);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("strike", "hunyuan-zhang");
        map_skill("cuff", "poyu-quan");
        map_skill("dodge", "huashan-shenfa");
        map_skill("unarmed", "huashan-quan");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        create_family("华山剑宗", 13, "弟子");

        set_temp("apply/attack", 220);
        set_temp("apply/defense", 220);
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 老夫不想收徒。");
}
