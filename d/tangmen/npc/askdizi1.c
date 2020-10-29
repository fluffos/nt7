inherit NPC;
#include <ansi.h>;

void create()
{       
        string *order = ({"张", "王", "李", "赵", "孙", "徐", "郑", "周", "吴",
                "蒋", "沈", "杨", "苗", "尹", "金", "魏", "陶", "俞", "柳", "朱"});
        string *orderr = ({"包包", "宝宝", "乖乖", "小小", "磊磊",
                "鸡鸡", "鸦鸦", "狗狗", "猫猫","清清","明明","飞飞"});
        set_name(order[random(20)]+orderr[random(8)], ({ "boy","nanhai" }) );
        set("title", "无知男孩");
        set("gender", "男性" );
        set("age",5+random(3));
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("max_qi",100);
        set("max_jingli",100);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                // (: random_move :)
        }) );
        */
             

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_dating","xunwen");
}       

int do_dating(string arg)
{
        object me = this_player();
        object ob = this_object();
        string str=query("id", me);
       
        if (!arg || arg != "wenzi")
             return notify_fail("你想打听什么，你倒是说啊！\n");
        
        if( query("dname") != query("id", me) )
             return notify_fail("我不想说，你不要问，问了也白问！\n");     
         
        if( !(query_temp("started", me)) )
             return notify_fail("关于你的问题，我要考虑一下，你现在是不是觉得有点热啊！\n");
        
        if( !(query_temp("asked", me)) )
           {
             command("ah");
             command("say 找我，你算找对了，不瞒你说吧！我刚被蚊子叮过，你说我会不会知道啊！\n");
             
             switch(random(2))
             {
                case 0 : command("joke");break;
                case 1 : set_temp("asked",1,me);tell_object(me,HIC"话音刚落，一个纵身没有影了！\n"NOR); 
             destruct(ob);delete_temp("started", me);break;
                default: return 1;
             }
            return 1;                       
            }  
        tell_object(me,"话还没说完，就听见。。。。。。\n");       
        tell_object(me,HIG"一阵“嗡嗡”声，一群蚊子从你身边飞过！\n"NOR);
        tell_object(me,HIR"不要犹豫了，快去追啊！\n"NOR);
        return 1;
                
}
