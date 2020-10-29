//xiao-tong2.c 小僮
inherit NPC;
#include <ansi.h>
string ask_tea();

void create()
{
        set_name("小僮",({"xiao tong", "xiao", "tong"}));
               set("long","她就是专门侍茶的小僮。她长得眉清目秀。\n");
        set("gender", "女性");
        set("age", 16);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);        
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 1);
        set("combat_exp", 1000);
        set("score", 50000);
        set_skill("unarmed",20);
        set_skill("parry",20);
        set_skill("dodge",20);
        set_skill("force", 20);
        set_skill("sword", 20);
        set("inquiry", ([
              "茶" : (: ask_tea :),
        ]));
        setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
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
        say(CYN"小僮笑吟吟地说道：这位" + RANK_D->query_respect(ob)
             + "请了，" + "我这就给您泡茶。\n"NOR);
}

string ask_tea()
{
        object ob;
        object me;
        ob=this_object();
        me=this_player();
               if( (query("water", me)*10/me->max_water_capacity())>8 )
                return "你怎么喝饱了还想要？";
        if ( present("suanmei tang", this_player()))
                return "先喝完了我给你的再说吧。";
        if ( present("suanmei tang",  environment(me)) )
                return "那不是有吗？先喝完了再说。";
        ob = new("/d/mingjiao/obj/tang");
        ob->move(environment(this_object()));
        return "这杯又甜又热的酸梅汤给你吧，请慢点喝哟。";
}
