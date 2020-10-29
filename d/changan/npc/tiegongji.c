//tiegongji.c

inherit BUNCHER; 
inherit F_BANKER;

void create()
{
        set_name("铁公鸡", ({"tie gongji", "tie", "gongji"}));
        set("title", "钱庄老板");
        set("gender", "男性");
        set("age", 46);
        set("kee", 800); 
        set("max_kee", 800);
        set("sen", 200);
        set("max_sen", 200);
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 10);
        set("chat_msg", ({
                "铁公鸡嘿嘿嘿地笑了几声：我这把算盘几十年来可从来没算错过。\n",
                "铁公鸡骄傲的说道：本银号已经有上百年的历史，在长安城可以说是第一家。\n"
        }));
        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
        add_money("silver", 50);
}

void init()
{
        add_action("do_audit", "check");
        add_action("do_audit", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        add_action("do_bcun","bcun");
        add_action("do_bqu","bqu");
        add_action("do_bcheck","bcheck");
}

void enough_rest()
{
        delete_temp("busy");
}
