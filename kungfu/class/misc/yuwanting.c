#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("于万亭", ({ "yu wanting", "yu", "wanting" }));
        set("long",  "这是早已归隐的红花会上代总舵主于万亭。\n");
        set("gender", "男性");
        set("age", 67);
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
        set_skill("tianchi-neigong", 2800);
        set_skill("honghua-xinfa", 2600);
        set_skill("dodge", 2600);
        set_skill("yanzi-chuanyun", 2600);
        set_skill("parry", 2600);
        set_skill("strike", 2600);
        set_skill("benlei-zhang", 2600);
        set_skill("blade", 2400);
        set_skill("hanwang-qingdao", 2400);
        set_skill("whip", 2800);
        set_skill("jiandun-zhusuo", 2800);
        set_skill("martial-cognize", 2600);
        set_skill("literate", 2600);

        map_skill("force" , "tianchi-neigong");
        map_skill("blade" , "hanwang-qingdao");
        map_skill("strike" , "benlei-zhang");
        map_skill("dodge" , "yanzi-chuanyun");
        map_skill("parry" , "jiandun-zhusuo");
        map_skill("whip", "jiandun-zhusuo");

        prepare_skill("strike", "benlei-zhang");

        create_family("红花会", 0, "总舵主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "whip.qian" :),
                (: perform_action, "whip.fu" :),
                (: perform_action, "strike.lei" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
