//shao.c 艄公
//6/12/97 -qingyun
inherit NPC;
#include <ansi.h>
string ask_me();
void create()
{
        set_name("艄公",({"shao gong","shao","gong"}));
        set("long",  "他是一个老水手了。\n");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", 0);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("combat_exp", 1000);
        set_skill("cuff",20);
        set_skill("dodge",20);
        set_skill("force", 20);
        set_skill("parry", 20);        
        set("inquiry", ([
             "出海" : (: ask_me :),
             "here" : "这里是宁波出海口，位置是黄道带以西十五、以南十五个距离，你可要记清楚哦！\n",
             "rumors" : "海里经常会有周期性风暴，你要多加注意。\n",         
          ]));
        set("chat_chance", 3);
        set("chat_msg", ({
"艄公对你说：“昨天借给人一只船，至今没有归还，幸好以前赚下一些老本，新购一只船。”\n",                
"艄公说道：“昨天听人说，有几只渔船在黄道带中心附近遇上了大风暴，看来是回不来了。”\n",
"艄公说道：“有人出海回来说，东海里有几个仙岛，岛上住有仙人，不知是真是假。”\n",
        }));
        setup();
        add_money("silver", 1);
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/mingjiao/obj/luopan");
}

string ask_me()
{
        object me;
        object ob;
        ob=this_player();
        me=this_object();
        set_temp("marks/出1", 1, ob);
        return "由此出海颇为凶险，我可不去，但我的船可以借给你，但我以后的生活.....";
}        

int accept_object(object me, object ob)
{
        me=this_player();
        if( query("money_id", ob) && ob->value() >= 5000
                 && query_temp("marks/出1", me)){
                command("whisper"+query("id", me)+"你要去哪里，就叫(yell)我的海船(chuan)吧。\n");
                set_temp("haichuan_paid", 1, me);
                delete_temp("marks/出1", me);
                return 1;
        }
        return 0;
}
