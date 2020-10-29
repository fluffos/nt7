// yaoshi.c 药师
inherit NPC;
inherit F_VENDOR;
void create()
{
        set_name("药师", ({ "yao shi", "yao", "shi" }) );       
        set("gender", "男性" );
        set("age", 34);
        set("long","这是一位教主亲手调教出来的药师。\n");
        set("combat_exp", 400);
        set("unique", 1); 
        set("attitude", "peaceful");
        set("vendor_goods", ({
        }));
        setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
       if( !ob || environment(ob) != environment() ) return;
        command("say 这位"+RANK_D->query_respect(ob)+"请了，请问要买什么药？");
}
