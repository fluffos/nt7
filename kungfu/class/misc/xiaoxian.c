// xiaoxian.c 星宿小仙

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("星宿小仙", ({ "xingxiu xiaoxian", "xiaoxian" }));
        set("long",  "她是一个小女孩，看上去年纪不大。\n");
        set("gender", "女性");
        set("age", 24);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 36);
        set("con", 38);
        set("dex", 33);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 55000000);
        set("score", 10000000);

        set_skill("force", 6000);
        set_skill("huagong-dafa", 6000);
        set_skill("guixi-gong", 6000);
        set_skill("throwing", 6000);
        set_skill("feixing-shu", 6000);
        set_skill("dodge", 6000);
        set_skill("zhaixing-gong", 6000);
        set_skill("strike", 6000);
        set_skill("chousui-zhang", 6000);
        set_skill("claw", 6000);
        set_skill("sanyin-wugongzhao", 6000);
        set_skill("whip", 6000);
        set_skill("chanhun-suo", 6000);
        set_skill("parry", 6000);
        set_skill("staff", 6000);
        set_skill("poison", 2550);
        set_skill("tianshan-zhang", 6000);
        set_skill("literate", 1200);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");

        create_family("星宿派", 0, "奇人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.fugu" :),
                (: perform_action, "staff.xue" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
