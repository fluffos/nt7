#include <ansi.h>
inherit NPC;

int ask_join();
int ask_box();

void create()
{
        set_name("郭老六", ({ "guo laoliu", "guo", "laoliu", }));
        set("title", HIB"药王谷"NOR+WHT"管事"NOR);
        set("long", "他是回春堂的帐房先生，负责回春堂的所有帐目。\n" );
        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 60);
        set("shen_type", 1);
        set("str", 17);
        set("int", 16);
        set("con", 18);
        set("dex", 20);
        set("max_qi", 150);
        set("max_jing", 150);
        set("jiali", 10);
        set("combat_exp", 5000);

        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);
        set_skill("yaogu-xinfa", 30);
        
        create_family("药王谷", 3, "弟子");
        set("class", "bonze");

        set("inquiry", ([
                "药王谷" : "要加入药王谷，可以ask guo about 加入",
                "join" : (: ask_join :),
                "加入" : (: ask_join :),
                "打工" : (: ask_join :),
                "针灸盒" : (: ask_box :),
                "box" : (: ask_box :),
        ]));

        setup();
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
        if( query_temp("work_pass", ob)){
                command("say 谷主正在药王谷等你，你还不快去！\n");
                return 1; }
        if( query("party/party_name", ob) == "药王谷" )
        {
                if( (int)ob->query_skill("medical",1)>=40) 
                {
                set_temp("work_pass", 1, ob);
                command("say 这位兄弟你的医药口诀大有长进，正是我药王谷需要的人才！\n");
                command("say 如果你愿意可以到药王谷去，叩见谷主进一步学习。\n");
                return 1;
                }
                
        }
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


int ask_join()
{
        mapping party; 
        object me;
        me=this_player();

        if( query("family/family_name", me) == "药王谷" )
                {
                command("say "+RANK_D->query_respect(me)+
                        "你已经是药王谷的人了，还要加入什么？\n");
                return 1; 
                }

        if( query("family/family_name", me) )
                {
                command("say "+RANK_D->query_respect(me)+
                        "你已经有明师指点，还是回去好好吧效忠师门吧！\n");
                return 1; 
                }

        command("ok"+query("id", me));
        command("say 你先在回春堂做事吧，时机成熟了你就可以进入药王谷了！\n");
        command("recruit"+query("id", me));
        if( query("class", me) != "bonze" )
                set("class", "bonze", me);
        set("title", "回春堂跑堂弟子", me);
        command("say "+RANK_D->query_respect(me)+
                "今后要多多努力干活啊！\n");
        return 1;
}

int ask_box()
{
        object ob, me;
        me=this_player();

        if( query("family/family_name", me) != "药王谷"){
                command("say "+RANK_D->query_respect(me)+
                        "你不是药王谷的弟子，针灸盒不能随便给你！\n");
                return 1; }

        if( present("zhenjiu he", me) ) {
                command("say "+RANK_D->query_respect(me)+
                        "你现在身上不是有吗？要哪么多干什么呢？\n");
                return 1; }

        if( (int)me->query_skill("medical",1)<40 ) {
                command("say "+RANK_D->query_respect(me)+
                        "你现在还不会使用针灸盒！\n");
                return 1; }

        ob = new(__DIR__"obj/zhenjiu");
        ob->move(me);

        message_vision(YEL"郭老六给$N一个"+query("name", ob)+"。\n"NOR,me);

        command("say "+RANK_D->query_respect(me)+
                "今后要多多努力啊！\n");
        return 1;
}
