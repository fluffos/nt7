#include <ansi.h>
inherit NPC;
inherit F_BANKER;

void create()
{
        set_name("钱多", ({"qian duo", "qian", "duo"}));
        set("title", "钱庄老板");
        set("nickname", "视钱如粪土");
        set("gender", "男性");
        set("age", 35);
        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);
        set("qi", 500);
        set("max_qi", 500);
        set("jing", 100);
        set("max_jing", 100);
        set("shen", 0);

        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 1);

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);
        setup();
}

void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        
        tell_object(this_player(), "\n" +        
        "※※※※※※※※※※※\n" +
        "※                  ※\n" +
        "※     公平交易     ※\n" +
        "※                  ※\n" +
        "※  存钱： deposit  ※\n" +
        "※                  ※\n" +
        "※  取钱： withdraw ※\n" +
        "※                  ※\n" +
        "※  兑换： convert  ※\n" +
        "※                  ※\n" +
        "※  查帐： check    ※\n" +
        "※                  ※\n" +
        "※                  ※\n" +
        "※※※※※※※※※※※\n\n" NOR);
}
