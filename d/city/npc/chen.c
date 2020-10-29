// chen.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("陈有德", ({ "chen youde", "chen" }));
        set("long", "陈有德是扬州武馆馆长。\n");
        set("gender", "男性");
        set("age", 45);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("claw", 80);
        set_skill("hand", 80);
        set_skill("strike", 80);
        set_skill("finger", 80);
        set_skill("cuff", 80);
        set_skill("blade", 80);
        set_skill("club", 80);
        set_skill("staff", 80);
        set_skill("sword", 80);
        set_skill("throwing", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);

        set("vendor_goods", ({
                "/clone/book/basic-sword",
                "/clone/book/basic-blade",
                "/clone/book/basic-dagger",
                "/clone/book/basic-unarmed",
                "/clone/book/basic-dodge",
                "/clone/book/basic-parry",
                "/clone/book/basic-force",
                "/clone/book/basic-staff",
                "/clone/book/basic-whip",
                "/clone/book/basic-throwing",
                "/clone/book/basic-cuff",
                "/clone/book/basic-hand",
                "/clone/book/basic-strike",
                "/clone/book/basic-finger",
                "/clone/book/basic-claw",
                "/clone/book/basic-club",
        }));

        setup();
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

int accept_object(object who, object ob)
{
        if( query("combat_exp", who) >= 3500 )
        {
                message_vision("陈有德望着$N说：你的武功应该"
                               "历练江湖才能再长进，不能埋没在这里了。\n", who);
                return 0;
        }

        if( query("money_id", ob) && ob->value() >= 500 )
        {
                set_temp("marks/yangzhou_paied", 1, who);
                message_vision("陈有德对$N说：好！这位" + RANK_D->query_respect(who) +
                               "想学什么呢？\n" , who);
                return 1;
        } else
                message_vision("陈有德皱眉对$N说：钱我不在乎"
                               "。可你也给的也太少了点儿吧？\n", who);
        return 0;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/yangzhou_paied", ob) == 1 )
                return 0;

        return 1;
}