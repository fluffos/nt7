// duansh.c 段寿辉

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("段寿辉", ({ "duan shouhui", "duan" }));
        set("long",  "他一副僧人打扮，但是却透露出一股雍容华贵的气质。\n");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 33);
        set("int", 38);
        set("con", 34);
        set("dex", 31);
        
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 25000000);
        set("score", 10000000);

        set_skill("force", 2500);
        set_skill("dodge", 2400);
        set_skill("parry", 2500);
        set_skill("cuff", 2400);
        set_skill("sword", 2400);
        set_skill("staff", 2400);
        set_skill("finger", 2500);
        set_skill("kurong-changong", 2500);
        set_skill("tiannan-bu", 2400);
        set_skill("jinyu-quan", 2400);
        set_skill("duanjia-jian", 2400);
        set_skill("sun-finger", 2500);
        set_skill("literate", 1800);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "duanjia-jian");

        prepare_skill("finger", "sun-finger");

        create_family("段氏皇族", 0, "老僧");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qiankun" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "sword.jing" :),
                (: perform_action, "sword.jue" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
