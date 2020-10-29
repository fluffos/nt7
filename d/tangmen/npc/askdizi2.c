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
        set("d2name","");
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
        string str,where;
        object me = this_player();
        object ob = this_object();
        
        if ( !arg || arg != "wenzi")
             return notify_fail("你想询问什么，你倒是说啊！\n");
        
        if( query("dname") != query("id", me) )
             return notify_fail("我不想说，你不要问，问了也白问！\n");
             
        if( (query_temp("askok", me)) )
             return notify_fail("关于你的问题，我要考虑一下，你现在是不是觉得有点热啊！\n");
        
        if( !(query_temp("asked", me)) )
             return notify_fail("你这个真奇怪，有问路的，有问要钱的，有问吃的，没听有问蚊子的。\n");
        
        switch( random(6))
        {
            case 0 : str = "唐家铺子";where = "/d/tangmen/tjpuzi";break;
            case 1 : str = "唐门酒楼";where = "/d/tangmen/jiulou";break;
            case 2 : str = "客店";where = "/d/tangmen/kedian";break;
            case 3 : str = "药铺";where = "/d/tangmen/hcfdian";break;
            case 4 : str = "兵器铺";where = "/d/tangmen/tmbingqi";break;
            default : str = "唐氏钱庄";where = "/d/tangmen/tsqianz";break;
        }
        
        tell_object(me,HIC"你去"+str+"找找啊！\n"NOR);    
        
        set_temp("mingchen", str, me);
        set_temp("where", where, me);
            
        set_temp("askok", 1, me);
        delete_temp("asked", me);
                        
        tell_object(me,HIC"话音刚落，一个纵身没有影了！\n"NOR);
        destruct(ob);
        return 1;   
        
}                  
