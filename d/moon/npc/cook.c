// butcher.c

inherit NPC;

void create()
{
        set_name("厨师", ({ "cook" }) );
        set("gender", "男性" );
        set("age", 35);
        set("long", "一个山庄的厨子， 正在忙呢。\n");
        set("str", 29);
        set("int", 14);
        set("combat_exp", 25000);
        set("attitude", "heroism");
        set_skill("dagger", 100);
        set_skill("parry", 100);
        set_skill("dodge", 150);
        setup();
        add_money("silver", 50);
/*
        carry_object("/obj/cloth")->wear();
              carry_object( __DIR__ "obj/badblade")->wield();
*/
 }

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                 say( "厨子擦了擦头上的汗。”\n");
                    break;
                case 1:
                        say( "厨师道：“真累呀。\n");
                        break;
        }
}

 
