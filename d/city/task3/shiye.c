#include <ansi.h>
inherit NPC;

string ask_me();

void create()
{
        set_name("谭友纪", ( { "tan youji", "tan" }) );
        set("title", "扬州府师爷");
        set("gender", "男性" );
        set("age", 57);

        set("combat_exp", 30000);
        set_skill("unarmed", 50);
        set_skill("dodge", 60);
        set_temp("apply/attack",  20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage",  20);
        set("shen_type", 0);

        set("inquiry", ([
                "叫化鸡" : (: ask_me :),
                "扬州府":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "官府":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "当官":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "捕快":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "任务":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "task":"只要加入官府(join guanfu)，就可以为朝廷出力。\n",
                "quest":"只要加入官府(join guanfu)，就可以为朝廷出力。\n"
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
                "谭师爷道：现在想当官的人越来越多了！\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;
        mapping myfam;
        ob = this_player();
        ::init();
        add_action("do_join", "join");
}

int do_join(string arg)
{
        object ob = this_player();
        if(!arg || arg!="guanfu") return notify_fail("谭友纪道：你要加入什么组织？\n");
        if( query("officerlvl", ob)>0 )
        {
                message_vision(HIC"谭友纪说道：你已经是扬州府捕快了。\n"NOR,ob);
                return 1;
        }
        if( query("combat_exp", ob)<20000 )
        {
                message_vision(HIC "谭友纪对$N摇头道：你的实战经验太低。\n" NOR,ob);
                return 1;
        }
        if( query("class", ob) != "bonze" && 
                query("class", ob) != "lama" && 
                query("class", ob) != "quanzhen" && 
                query("class", ob) != "eunach" )
                set("class", "officer", ob);
        set("officerlvl", 1, ob);
        message_vision(HIY "谭友纪对$N道：从现在起你就是个实习捕快！\n" NOR,ob);
        addn("weiwang", 10, ob);
        message_vision(HIC "$N的江湖威望提高了！\n" NOR,ob);
        tell_object(ob,"你现在的江湖威望是"+chinese_number((query("weiwang", ob)))+"。\n"NOR);
        return 1;
}
string ask_me()
{
        if( query_temp("marks/鸡", this_player()) )
        {
                say("好小子，你怎么知道我喜欢吃叫化鸡？\n");
                command("lick");
                say("既然你我成了食友，我就告诉你吧。付耳过来！\n");
                command("whisper"+query("id", this_player())+"你去北京找全聚德的老板，只要告诉他是我叫你去的，他就会...");
                delete_temp("marks/鸡", this_player());
                set_temp("marks/鸡2", 1, this_player());
                return "今天嗯....啊....那个天气很好....\n";
        }
        else if( query_temp("marks/鸡2", this_player()) )
                return "我是个浙江人，也没有你那么罗嗦！\n";
        else
                return "泥缩丝米偶钉布懂\n";
}