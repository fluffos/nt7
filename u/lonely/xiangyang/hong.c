#include <ansi.h>

inherit NPC;

void create()
{
        object ob;
        set_name("洪七公", ({ "hong qigong", "hong", "qigong" }));
        set("long", @LONG
他就是丐帮第十七任帮主，号称九指神丐的洪
七公老爷子。只见他须眉皆白，周身上下邋遢
不已，模样甚是龌龊。可是他目光如电，显得
正义凛然，不怒而自威。
LONG);
        set("nickname", HIW "北丐" NOR);
        set("gender", "男性");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 265000);
        set("max_jing", 265000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 200);
        set("combat_exp", 40000000);
        set("score", 400000);
        set("shen_type", 1);

        set_skill("force", 540);
        set_skill("jiaohua-neigong", 520);
        set_skill("huntian-qigong", 540);
        set_skill("yijin-duangu", 520);
        set_skill("dodge", 520);
        set_skill("feiyan-zoubi", 520);
        set_skill("xiaoyaoyou", 520);
        set_skill("unarmed", 520);
        set_skill("changquan", 520);
        set_skill("jueming-tui", 520);
        set_skill("hand", 580);
        set_skill("chansi-shou", 580);
        set_skill("claw", 580);
        set_skill("suohou-gong", 580);
        set_skill("strike", 540);
        set_skill("xianglong-zhang", 540);
        set_skill("tongchui-zhang", 520);
        set_skill("liuhe-zhang", 520);
        set_skill("parry", 520);
        set_skill("staff", 540);
        set_skill("dagou-bang", 540);
        set_skill("jiaohua-bangfa", 520);
        set_skill("fengmo-zhang", 520);
        set_skill("fumo-zhang", 520);
        set_skill("throwing", 500);
        set_skill("pomie-jinzhen", 500);
        set_skill("begging", 500);
        set_skill("checking", 500);
        set_skill("literate", 540);
        set_skill("martial-cognize", 520);
        set_skill("bixue-danxin", 500);

        map_skill("throwing", "pomie-jinzhen");
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("hand", "chansi-shou");
        map_skill("claw", "suohou-gong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        create_family("丐帮", 17, "帮主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.qu" :),
                (: perform_action, "strike.zhen" :),
                (: perform_action, "strike.fei" :),
                (: perform_action, "dodge.xian" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.chuo" :),
                (: perform_action, "staff.feng" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "staff.tian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 600);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 400);

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void unconcious()
{
        die();
}              
