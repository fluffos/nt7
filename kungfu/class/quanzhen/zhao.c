// zhao.c 赵志敬
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

string *bd_fighters = ({
        ("/kungfu/class/quanzhen/wangzhitan.c"),
        ("/kungfu/class/quanzhen/shen.c"),
        ("/kungfu/class/quanzhen/cui.c"),
        ("/kungfu/class/quanzhen/chen.c"),
        ("/kungfu/class/quanzhen/li.c"),
        ("/kungfu/class/quanzhen/yin.c")
});

string ask_beidouzhen();

void create()
{
        set_name("赵志敬", ({"zhao zhijing", "zhao"}));
        set("gender", "男性");
        set("age", 26);
        set("class", "taoist");
        set("long",
                "他就是全真教第三代弟子中的好手，王处一的大弟子赵志敬。 \n"
                "他相貌端正，但眉宇间似乎隐藏着一丝狡猾的神色。\n"
                "他是一个长须道人，看起来却有些煞气。\n");
        set("attitude", "friendly");
        set("shen_type",-1);
        set("str", 25);
        set("int", 26);
        set("con", 26);
        set("dex", 25);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 60);

        set("combat_exp", 160000);

        set_skill("force", 80);
        set_skill("quanzhen-xinfa", 80);
        set_skill("sword", 80);
        set_skill("quanzhen-jian",80);
        set_skill("dodge", 70);
        set_skill("jinyan-gong", 70);
        set_skill("parry", 80);
        set_skill("unarmed",80);
        set_skill("finger",80);
        set_skill("zhongnan-zhi", 80);
        set_skill("literate", 60);
        set_skill("taoism", 60);
        set_skill("array", 120);
        set_skill("beidou-zhenfa", 120);

        map_skill("array","beidou-zhenfa");
        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        prepare_skill("finger", "zhongnan-zhi");

        create_family("全真教", 3, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
                 "天罡北斗阵" : (: ask_beidouzhen :),
                "beidouzhen" : (: ask_beidouzhen :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greyrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_beidouzhen()
{
        string msg, name;
        object me = this_player();

        command("look"+query("id", me));

        if( !query("family", me) || query("family/family_name", me) != "全真教" )
          {
                msg = "「天罡北斗阵」是我全真教的剑阵，威力无穷!";
                return msg;
          }

        if( query_temp("asked_beidouzhen", me) )
        {
                msg="急什么？时辰一到就会开始练习「天罡北斗阵」！\n";
                return msg;
        }

        if( query_temp("pending/beidouzhen", me) )
        {
                msg="好好练习「天罡北斗阵」！\n";
                command("addoil"+query("id", me));
                return msg;
        }

        if( query_temp("pending/beidouzhen") || query_temp("beidou_time") )
        {
                msg="没看到我正在忙吗？\n";
                return msg;
        }

        if( query("eff_qi") < query("max_qi")/2 )
        {
                msg="没看到我全身是伤吗？\n";
                return msg;
        }

        if(query_temp("count")>=6)
        {
                msg="可惜现在人已够了！\n";
                return msg;
        }

        if ( me->query_skill("quanzhen-jian",1) <60 ||
             query("combat_exp", me)<50000 || 
             me->query_skill("dodge") <60)
        {
                msg="可惜"+query("name", me)+"武功太差，不够练习「天罡北斗阵」。\n";
                return msg;
        }

        set_temp("asked_beidouzhen", 1, me);
        msg = "好，你先做好准备，等一会儿就让你跟随贫道一起练习「天罡北斗阵」！\n";
        set_temp("fighter/"+time(),query("id", me));
        delete_temp("qz/bdgranted", me);
        addn_temp("count",1);

        command("halt");
        command("yun recover");

        remove_call_out("start");
        call_out( "start", 30+ random(30) );
        return msg;
}


int start()
{
        object me = this_object();
        object ob1,ob2,ob3,ob4,ob5,ob6,ob7,ob;
        object here = environment(me);
        mapping fighter;
        int i, *times,j;
        string arg;

        if( !(fighter=query_temp("fighter", me)) )
                return 0;

        times = keys(fighter);
        j = 0;

        for(i = 0; i < sizeof(times); i++)
        {
                if( !( ob = present( fighter[times[i]],here) ) )
                {
                        if( ( ob = find_player( fighter[times[i]]) ) )
                        {
                                tell_object(ob,"赵志敬告诉你：跑哪儿去了？不好好跟我练习阵法，当心我告诉掌教真人！\n");
                                delete_temp("asked_beidouzhen", ob);
                        }
                        continue;
                }

                message_vision(HIY"$N道：$n请做好准备！\n"NOR, me,ob);
                delete_temp("asked_beidouzhen", ob);
                ob->move("/d/quanzhen/dajiaochang");
                if (j==0) ob1=ob;
                else if(j==1)ob2=ob;
                else if(j==2)ob3=ob;
                else if(j==3)ob4=ob;
                else if(j==4)ob5=ob;
                else if(j==5)ob6=ob;
                else if(j==6)ob7=ob;
                  j++;
        }

        command("halt");
        message_vision(HIY"$N道：来人呐！\n"NOR, me);

        for( i = j;i<6;i++)
        {
                if(i==0){
                        if( !(ob1 = present( "wang zhidan",here ) ) )
                        {
                                ob1=new( bd_fighters[i] );
                                ob1->move(environment(me));
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob1);
                        }
                }
                else if(i==1)
                {
                        if( !(ob2 = present( "shen zhifan",here ) ) )
                        {
                                ob2=new( bd_fighters[i] );
                                ob2->move("/d/quanzhen/dajiaochang");
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob2);
                        }
                }
                  else if(i==2)
                {
                        if( !(ob3 = present( "cui zhifang",here ) ) )
                        {
                                ob3=new( bd_fighters[i] );
                                ob3->move("/d/quanzhen/dajiaochang");
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob3);
                        }
                }
                  else if(i==3){
                        if( !(ob4 = present( "chen zhiyi",here ) ) )
                        {
                                ob4=new( bd_fighters[i] );
                                ob4->move("/d/quanzhen/dajiaochang");
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob4);
                        }
                }
                  else if(i==4)
                {
                        if( !(ob5 = present( "li zhichang",here ) ) )
                        {
                                ob5=new( bd_fighters[i] );
                                ob5->move("/d/quanzhen/dajiaochang");
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob5);
                        }
                }
                else if(i==5)
                {
                        if( !(ob6 = present( "yin zhiping",here ) ) )
                        {
                                ob6=new( bd_fighters[i] );
                                ob6->move("/d/quanzhen/dajiaochang");
                                message_vision(HIY"$N快步走了过来，作楫道：有劳各位道兄久等了！\n"NOR, ob6);
                        }
                  }
        }

        arg=query("id", me)+","+query("id", ob1)+","+query("id", ob2)+","+
                query("id", ob3)+","+query("id", ob4)+","+query("id", ob5)+","+
                query("id", ob6);

        message_vision(HIG"$N清了清喉咙，大声说道：好，时辰已到，现在开始练习「天罡北斗阵」！\n"NOR,me);

        "/d/quanzhen/dajiaochang"->do_beidouzhen2( arg );

        delete_temp("fighter", me);
        delete_temp("count", me);
}
