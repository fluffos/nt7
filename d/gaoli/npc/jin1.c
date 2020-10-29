#include <ansi.h>

inherit NPC;
inherit F_DEALER;
void create()
{
        set_name("金算盘", ({"jin suanpan", "jin"}));
        set("title", "当铺掌柜");
        set("gender", "男性");
        set("age", 34);

        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);

        set("kee", 500); 
        set("max_qi", 500);
        set("gin", 100);
        set("max_gin", 100);
        set("sen",300);
        set("max_jing",300);
        set("combat_exp",300000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("env/wimpy", 50);

        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 200);
                set_skill("cuff",120);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);

        setup();
        carry_object("/d/gaoli/obj/pao")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sell", "sell");
        add_action("do_value", "value");
}

void die()
{
        message_vision("\n$N死了。\n", this_object());
        destruct(this_object());
}
