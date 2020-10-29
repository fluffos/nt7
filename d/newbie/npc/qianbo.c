#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("钱伯", ({ "qian bo", "qian", "bo" }));
        set("nickname", HIM "见利忘义" NOR);
        set("title", "杂货铺老板");
        set("long", @LONG
一个胖胖的老板，卖一些普通的物品。可使用 list 查看可购买的物品。
LONG);
        set("gender", "男性");
        set("age", 44);
        set("per", 24);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);
        set("combat_exp", 800000);
        set("no_get", "1");
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/xingxiu/obj/fire",
                "/d/henshan/obj/mujian",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
        }));
        
        set("no_pk", 1);
	setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{        
        object ob; 

        ob = this_player();

        ::init(); 
        add_action("do_buy", "buy"); 
        add_action("do_list", "list"); 

        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say(CYN "钱伯笑着说道：这位" + RANK_D->query_respect(ob)+ "你需"
            "买些什么，请随便看（输入指令 list 查看）。\n" NOR);

        return;
}











