#include <ansi.h>
inherit NPC;

int ask_me();

void create()
{
        set_name("唐讹化", ({ "tang ehua", "tang", "ehua" }) );
        set("title", HIB"药王谷"NOR+HIC"医师"NOR);
        set("long", "他是回春堂的坐堂老医师，负责给看病。\n" );
        set("gender", "男性" );
        set("age", 52);
        set("combat_exp", 100);
        set("attitude", "friendly");

        set("inquiry", ([
                "heal" : (: ask_me :),
        ]));

        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{

        if( query("family/family_name", ob) == "药王谷"){
                command("say 这位兄弟辛苦了，快请进！\n");
                return 1;}
        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}

int ask_me()
{
        object me;      int i, obj;

        me = this_player();
        i=(query("max_qi", me)-query("eff_qi", me));
        obj=query("max_qi", me);

        if( !query_temp("heal", me)){
                command("say "+RANK_D->query_respect(me)+
                        "你先交诊金"+MONEY_D->price_str(i*10)+"吧！\n");
                return 1;
        }
        delete_temp("heal", me);
        set("eff_qi", obj, me);
        set("qi", obj, me);
        message_vision ("唐讹化为$N把了把脉，拿出一根银针在$N穴位上扎了几下。\n", me);
        command("say 你的伤好得差不多了！");
        return 1;
}

int accept_object(object me, object ob)
{
        int i=(query("max_qi", me)-query("eff_qi", me));

        if(i<5) i=5;

        command("smile");
        command("say 呵呵，多谢这位" + RANK_D->query_respect(me) + " ！");

        if( query("money_id", ob) )
        {
                if(ob->value() < (i*10))
                {
                        command("say 这位给的未免少了点。");
                        return 1;
                }
                else
                {
                        set_temp("heal", 1, me);
                        command("say 好我收下了！");
                        return 1;
                }
        }
        return 1;
}
