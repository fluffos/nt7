#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM; 

void create()
{
        set("short", "大榕树上");
        set("long", @LONG
这里是大树的顶端，四周全是浓密的枝叶和湿漉漉的苔藓。一阵
微风吹来，树叶发出唰啦啦的声音。从上面望下去你只觉得一阵眼晕，
心想还是赶快下去吧。
LONG );
        set("no_fight", 1); 
        set("valid_startroom", 1); 
        set("no_sleep_room",1); 
        set("outdoors", "city");
        set("item_desc", ([
                "tree" : GRN "\n这是一棵巨大古老的大榕"
                         "树，枝叶非常的茂密。\n" NOR,
        ]));
        set("exits", ([
                "down" : __DIR__"guangchang",
                "up"  : __DIR__"tree2",
        ]));
        set("objects", ([
               // CLASS_D("xiakedao") + "/shi" : 1,
        ]));
        setup();
        call_other("/clone/board/comm_b", "???");
}

void init() 
{
        add_all_action(); 
        add_action("do_jump", ({ "tiao", "jump" }) );
        add_action("do_climb", ({ "pa", "climb" }) );
}

int do_climb(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "tree" || arg == "up")
        {
                if( objectp(query_temp("is_riding", me)) )
                        return notify_fail("没听说过有人能骑坐骑还能爬树的。\n");

                if (me->is_busy())
                {
                        return notify_fail("你的动作还没有完成，不能移动。\n");
                        return 1; 
                }

            if( me->is_ghost() ) return notify_fail("等你还了阳再说吧。\n"); 
                if( query("gender", me) != "女性" )
                        message("vision",
                                me->name() + "战战兢兢地拉着大榕树的盘根，屁股一扭一扭地往上爬。\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision",
                                me->name() + "轻轻一跳，衣裙飘飘，象仙子般飞上大榕树。\n",
                                environment(me), ({me}) );
                else 
                        message("vision",
                                me->name() + "战战兢兢的抓住树干往上爬去。\n", 
                                environment(me), ({me}) );        

                me->move(__DIR__"tree2");
                
                if( query("gender", me) != "女性" )
                        message("vision",
                                me->name() + "气喘嘘嘘地爬了上来。\n",
                                environment(me), ({me}) );
                else 
                if( query("age", me)<40 && query("per", me)>24 )
                        message("vision","一阵清香飞来，你定眼一看，"+
                                me->name() + "已经婷婷玉立在你眼前。\n",
                                environment(me), ({me}) );
                else  
                        message("vision", me->name() + "战战兢兢地从下面爬了上来。\n", 
                                environment(me), ({me}) );
                                
                return 1;
        }
}

int do_jump(string arg)
{
        object me;
        me = this_player();
        
        if( !arg || arg != "down") return notify_fail("你要往哪跳？\n");
        
        if( me->is_busy() )  
                return notify_fail("你正忙着呢！\n");
        
        message("vision",
                me->name() + "犹豫了一下，鼓起勇气，跳了下去。\n“嘭”的一巨响，似乎听到"+me->name()+"惨嚎了一声!\n",
                environment(me), ({me}) );
        
        me->move(__DIR__"guangchang");
        message("vision",
                me->name() + "惨嚎一声，从树上掉了下来。\n",
                environment(me), ({me}) );
        
        return 1;
}

int valid_leave(object me, string dir)
{

        if ( dir=="down" && !wizardp(me))
                return notify_fail("盘根不知道给哪个坏家伙砍断了猓蠢粗荒跳爬(tiao)下去！\n");

        if ( dir=="up" && !wizardp(me))
                return notify_fail("这里没法直接走，看来你只能爬(climb)上去！\n");

        return 1;
}
