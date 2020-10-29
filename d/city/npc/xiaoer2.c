#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }));
        set("gender", "男性" );
        set("age", 22);
        set("long", "这位店小二正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");

        set("rank_info/respect", "小二哥");
        set("vendor_goods", ({
                __DIR__"obj/jitui",
                __DIR__"obj/jiudai",
                __DIR__"obj/baozi",
                __DIR__"obj/kaoya",
                __DIR__"obj/zui",
                "/clone/fam/pill/food",
                "/clone/fam/pill/water",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        switch(random(2))
        {
        case 0:
                say(CYN "店小二笑咪咪地说道：这位" + RANK_D->query_respect(ob) +
                    CYN "，进来喝杯茶，歇歇腿吧。\n" NOR);
                break;
        case 1:
                say(CYN "店小二用脖子上的毛巾抹了抹手，说道：这位" +
                    RANK_D->query_respect(ob) + CYN "，请进请进。\n" NOR);
                break;
        }
}

int accept_object(object me, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(me, CYN "小二一哈腰，说道：多谢您老，客官请上楼歇息。\n" NOR);
                set_temp("rent_paid", 1, me);
                return 1;
        }
        return 0;
}