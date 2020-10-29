// This program is a part of NITAN MudLIB 
// mud 2015-3
#include <ansi.h>

inherit NPC;
int accept_object(object me, object obj)
{
        if (this_object()->is_busy())
        {
                tell_object(me, CYN + name() + "皱眉对你说道：没见我正忙着吗？ \n" + NOR); 
                return 0;
        }
        if (!query("money_id", obj))
        {
                tell_object(me, CYN + name() + "皱眉对你说道：我只收「钱」！ \n" + NOR); 
                return 0;
        }
        
        if (obj->value() < 100000000)
        {
                tell_object(me, CYN + name() + "皱眉对你说道：找回秘籍，一次一万！\n" + NOR); 
                return 0;
        }
        if (me->is_busy())
        {
                tell_object(me, CYN + name() + "皱眉对你说道：先把你的事儿忙完再说好不？ \n" + NOR); 
                return 0;
        }
        else 
                me->start_busy(3);

        this_object()->command("say 有钱就是好办事！");
        this_object()->command("pat " + query("id", me));       
        addn_temp("invent/paid", obj->value(), me);
        destruct(obj); 
        
        return 1;
}

int ask_skill()
{
        object me, ob, obj;
        string book, *invent;
        mapping invent_skills;  
        int i;
        me = this_player();
        ob = this_object();
        
        invent_skills = query("invent", me);
        
        if( !invent_skills || !mapp(invent_skills) || !sizeof(invent_skills))
        {
                tell_object(me,CYN + query("name") + "瞪了你一眼说：你还没有自创武功吧？\n"+ NOR); 
                return 1;
        }      
        if( query_temp("invent/gived_"+query("id",me),ob)){
                tell_object(me,CYN + query("name") + "嘿嘿一笑：下次重启再来要吧！\n"+ NOR); 
                return 1;
        }   
        if( ! query_temp("invent/paid",me)){
                tell_object(me,CYN + query("name") + "满脸堆笑地说：有钱能使鬼推磨，先交钱吧，一次一万，不二价！\n"+ NOR); 
                return 1;
        }
    
        invent = keys(invent_skills);

        for(i=0;i<sizeof(invent);i++)
         {  
            book = invent_skills[invent[i]];
            obj = get_object("/data/book/" + book);
            obj->move(me);
            message_vision(MAG"$N默念口诀，无数的星光从四面八方飞来，渐渐聚集，凝结！\n"NOR,ob);
            message_vision(MAG"突然间，霞光一闪，$N手中多了一本"+obj->name()+NOR+MAG+"！\n"NOR,ob);         
            message_vision("$N拿出"HIW+HBRED+obj->name()+NOR"秘籍交给$n!\n",ob,me);
         }
        ob->command("sweat");
        set_temp("invent/paid",0,me);
        set_temp("invent/gived_"+query("id",me),1,ob);
        
        return 1;
}      
  
void create()
{
        set_name("泥潭使者", ({ "nitan shizhe", "shizhe", "shi" }));
        set("nickname", HIW"天神仆从"NOR);

        set("long", @LONG
这是泥潭公共NPC，天神派遣下来为玩家提供各种服务的使者。
LONG);
        set("gender", "男性" );
        set("age", 30);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("combat_exp", 1200000);
        set("inquiry", ([
                "自创武功" : (: ask_skill :),
                "武功秘籍" : (: ask_skill :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}


