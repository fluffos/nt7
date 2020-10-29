#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("衡山隐士", ({ "yin shi", "yin", "shi" }));
        set("long",  "他就是衡山派的高手，据说长年隐藏于山中。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", 1);
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

        set_skill("force", 240);
        set_skill("henshan-xinfa", 240);   
        set_skill("zhenyue-jue", 240);
        set_skill("dodge", 240);
        set_skill("henshan-shenfa", 240);
        set_skill("cuff", 240);
        set_skill("henshan-quan", 240);
        set_skill("sword", 260);
        set_skill("henshan-jian", 260); 
        set_skill("tianzhu-jian", 260);
        set_skill("zigai-jian", 260);
        set_skill("furong-jian", 260);
        set_skill("shilin-jian", 260);
        set_skill("strike", 240);
        set_skill("biluo-zhang", 240);
        set_skill("liuyun-zhang", 240); 
        set_skill("parry", 240);
        set_skill("literate", 240);
        set_skill("tanqin-jifa", 300);
        set_skill("xiaoxiang-yeyu", 300);
        set_skill("martial-cognize", 220);

        map_skill("strike", "liuyun-zhang");
        map_skill("cuff", "henshan-quan");
        map_skill("sword", "shilin-jian");
        map_skill("force", "zhenyue-jue");
        map_skill("dodge", "henshan-shenfa");
        map_skill("parry", "shilin-jian");
        map_skill("tanqin-jifa", "xiaoxiang-yeyu");

        prepare_skill("strike", "liuyun-zhang");
             

        create_family("衡山派", 0, "隐士");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.luo" :),
                (: perform_action, "strike.pai" :),
                (: perform_action, "strike.die" :),
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
