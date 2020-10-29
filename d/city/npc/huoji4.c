// huoji. 当铺伙计

#include <ansi.h>
inherit BUNCHER; 
inherit F_DEALER;

int redeem(string arg);

void create()
{
        set_name("当铺伙计", ({ "dangpu huoji", "huoji" }));
        set("str", 20);
        set("gender", "男性");
        set("age", 18);
        set("long", "他是唐楠从乡下招来帮忙的。\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        
        set_max_encumbrance(800000000000);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_sell", "sell");
        add_action("do_value", "value");
        //add_action("do_redeem", "redeem");
        // add_action("do_pawn", "pawn");
        add_action("do_check", "check");
        add_action("do_look", ({"guankan", "kan"}));
}

void unconcious()
{
        die();
}

void die()
{
        message_vision("\n$N死了。\n", this_object());
        destruct(this_object());
}

