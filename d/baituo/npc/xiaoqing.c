//NPC /npc/xiaoqing.c
#include <ansi.h>
inherit NPC;

void greeting(object);
void init();
string inquiry_gao();

void create()
{
        set_name("小青", ( { "qing", "xiao qing" }) );
        set("title", "药剂师");
        set("gender", "女性" );
        set("age", 17);
        set("long",
              "这是个聪明乖巧的小姑娘，打扮的很朴素，一袭青衣，却也显得落落有致。\n"
             );
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 20);
        set("int", 29);
        set("con", 23);
        set("dex", 22);

        set("max_qi", 430);
        set("max_jing", 220);
        set("neili", 320);
        set("max_neili", 320);

        set("combat_exp", 60000);
        set("score", 1000);

        set_skill("force", 40);
        set_skill("dodge", 50);
        set_skill("unarmed", 35);
        set_skill("parry", 40);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 17);
        set_temp("apply/armor", 10);

        set_temp("dan",0);
        set_temp("times",5);

        set("inquiry", ([
            "海口大碗" : "这『海口大碗』你可以拿到顶东头小院儿去，灌水喝。\n",
            "药罐" : "药罐在那儿，你自己看吧！\n",
            "蛇胆膏" : (: inquiry_gao :),
        ]));

        setup();
        carry_object("/d/baituo/obj/qingpao")->wear();
        carry_object("/d/baituo/obj/zheng");
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{

        if( !ob || environment(ob) != environment() ) return;
        if(random(2)==1)
        {
                say("小青笑吟吟地说道：这位" + RANK_D->query_respect(ob) +
                    "请进，见到你真高兴。\n");
                return;
        } else
        {
                say("小青笑了笑说道：这位" + RANK_D->query_respect(ob) +
                    "快请进吧。 \n");
                return;
        }
}

string inquiry_gao()
{
        object ob = this_player();

        if (query_temp("dan") == 3)
                return "你没见我已经作好了嘛！\n";

        if (query_temp("times") < 1)
                return "庄主现在已经不叫我做『蛇胆膏』了！\n";

        say("这位" + RANK_D->query_respect(ob)+
            "不瞒您说。师傅让我作『蛇胆膏』，\n可我",ob);
        switch (query_temp("dan"))
        {
        case 0: write(HIY "差一只青蛇胆，一只金蛇胆。\n" NOR);
                break;
        case 1: write(HIY "还差一只金蛇胆。\n" NOR);
                break;
        case 2: write(HIY "还差一只青蛇胆。\n" NOR);
                break;
        }
        return "不知哪位好心人能帮帮我呢？\n";
}


int accept_object(object who, object ob)
{
        object obn;
        
        if( ob->is_character() ) return 0;
        if( query("id", ob) != "qingdan" && 
            query("id", ob) != "jindan" )
        {
                command("shake");
                command("say 这是啥呀？我可不要哦。");
                return 0;
        }

        if (query_temp("times") < 1)
        {
                command("sigh");
                command("say 我现在已经不做『蛇胆膏』了。");
                return 0;
        }

        if( query("id", ob) == "jindan" )
        {
                if (query_temp("dan") == 2)
                {
                        message_vision("小青一看是金蛇胆，满脸遗憾地对\n"
                                       "$N说：我还差青蛇胆，不缺金蛇胆。\n", who);
                        return 0;
                }
                addn_temp("dan", 2);
                if (query_temp("dan") == 2)
                {
                        message_vision("你把金蛇胆递给了小青，她高兴得跳了起来。\n"
                                       "搂着$N的脖子说：还差青蛇胆就大功告成了！\n",who);
                        destruct(ob);
                        return 1;
                }
        }
        if( query("id", ob) == "qingdan" )
        {
                if (query_temp("dan") == 1)
                {
                        message_vision("小青一看是青蛇胆，满脸遗憾\n"
                                       "地对$N说：我还差金蛇胆，不缺青蛇胆。\n",who);
                        return 0;
                }
                addn_temp("dan", 1);
                if (query_temp("dan") == 1)
                {
                        message_vision("你把青蛇胆递给了小青，她高兴得跳了起来。\n"
                                       "搂着$N的脖子说：还差就金蛇胆大功告成了！\n",who);
                        destruct(ob);
                        return 1;
                }
        }

        command("kiss "+query("id", who));
        write(HIY "只见小青手脚麻利地把两只蛇胆投入药罐中，又加入一些\n"
              "不知是什么的药粉，然后把稀里哗啦一摇，嘿！『蛇胆膏』做\n"
              "成了。\n" NOR );
        message_vision("小青很神秘地凑近$N悄悄说了些什么。\n", who);
        tell_object(who,"我偷偷拿了一点『蛇胆膏』送给你，庄主不会发现的。\n");
        message_vision("小青深情地望了$N一眼，脸红了。\n",who);
        obn = new("/d/baituo/obj/shedangao");
        obn->move(who);
        set_temp("dan",0);
        addn_temp("times", -1);
        destruct(ob);
        return 1;
}

