#include <ansi.h>

inherit NPC;

void create()
{
            set_name("一灯大师", ({ "yideng dashi", "yideng", "dashi" }));
            set("long", @LONG
一灯大师乃江湖中人称“东邪西毒，南帝北丐”中
的南帝段皇爷，当年凭着段氏“一阳指”而独步武
林，罕逢敌手。但却在中年时因一段悲情而出家为
僧，之后大彻大悟，成为一位得道高僧。
LONG );
            set("title", "大理国退位皇帝");
            set("nickname", HIY "南帝" NOR);
            set("gender", "男性");
            set("age", 71);
        set("shen_type", 1);
            set("attitude", "friendly");

            set("str", 33);
            set("int", 35);
            set("con", 38);
            set("dex", 33);

            set("qi", 206500);
            set("max_qi", 206500);
            set("jing", 206500);
            set("max_jing", 206500);
            set("neili", 80000);
            set("max_neili", 80000);
            set("jiali", 200);
            set("combat_exp", 40000000);
            set("score", 500000);

        set_skill("force", 540);
        set_skill("xiantian-gong", 540);
        set_skill("duanshi-xinfa", 520);
        set_skill("kurong-changong", 520);
        set_skill("dodge", 520);
        set_skill("tiannan-bu", 520);
        set_skill("cuff", 500);
        set_skill("jinyu-quan", 500);
        set_skill("strike", 500);
        set_skill("wuluo-zhang", 500);
        set_skill("sword", 500);
        set_skill("staff", 500);
        set_skill("duanjia-jian", 500);
        set_skill("finger", 540);
        set_skill("qiantian-zhi", 540);
        set_skill("sun-finger", 540);
        set_skill("parry", 500);
        set_skill("jingluo-xue", 500);
        set_skill("buddhism", 540);
        set_skill("literate", 500);
        set_skill("sanscrit", 500);
        set_skill("martial-cognize", 520);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("段氏皇族", 11, "传人");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.jian" :),
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "finger.die" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 400);

            setup();
            carry_object("/clone/cloth/seng-cloth")->wear();
}
void unconcious()
{
        die();
}   
