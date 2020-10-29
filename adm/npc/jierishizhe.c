inherit NPC;
inherit F_VENDOR;
int get_reward();
void create()
{
        set_name("节日使者", ({ "jieri shizhe" }) );
        set("gender", "女性" );
        set("age", 14);
        set("title", "如花似玉");
        set("long",
                "节日使者。。。。你可以问她有关奖励的事情（reward）\n");
        set("combat_exp", 500000);
        set("attitude", "friendly");
        set("per",30);
        set("vendor_goods", ([
                __DIR__"obj/white_towel":11,
        ]) );
        set("inquiry", ([
                "reward" : (: get_reward :),
        ]));
        setup();
        carry_object(__DIR__"obj/green_cloth")->wear();
} 
void init()
{       
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
} 
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(3) ) {
                case 0:
                        message_vision("$N在百忙中抬起头望了$n一眼。\n",this_object(),ob);
                        break;
        }
}
int get_reward()
{
        object me;
        string ret;
        me =this_player();
        ret=FESTIVAL_D->get_reward(me);
        tell_object(me,ret);
        return 1;
}      

