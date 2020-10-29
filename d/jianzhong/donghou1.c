#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","谷后树林");
        set("long",@LONG
树林里郁郁葱葱，鸟语花香，光线从树叶的缝隙中洒
向大地，微风吹来，树影一阵婆娑。四周全是树，一片绿
色，在碧绿的海洋中，你渐渐地迷失了方向。
LONG
        );
        set("exits",([
                "east":__FILE__,
                "west":__FILE__,
                "north":__FILE__,
                "south":__FILE__,
        ]));
        set("snake_count",5);
        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -420);
        set("coor/z", 0);
        setup();
}
void init()
{
        object ob1,ob2;
        object me=this_player();
        if( (random(10)<2) && (query("snake_count", this_object())>0) && (query_temp("dugu_visit", me) != 0) && (!present("pusi qushe",environment(this_player()))) )
        {        
                ob1=new(__DIR__"npc/pusiqushe");
                ob1->move(this_object());
                addn("snake_count", -1, this_object());
        }
}
int valid_leave(object me, string dir)
{
        int i;
        string msg;
        if( !query_temp("dugu_visit", me) )
        {
                if(dir=="north")
                {i=query_temp("zhongnan/tree", me);
                        if( (i>0) && (i<10))addn_temp("zhongnan/tree", -1, me);
                        if( (i>9) && (i<12))addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="south")
                {i=query_temp("zhongnan/tree", me);
                        if((i<4)||(i==14)) 
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="east")
                {i=query_temp("zhongnan/tree", me);
                        if((i>3)&&(i<10))
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="west")
                {i=query_temp("zhongnan/tree", me);
                        if((i>11)&&(i<14))
                                addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if( query_temp("zhongnan/tree", me) >= 15 )
                 {
                                 me->move(__DIR__"donghou");
                           delete_temp("zhongnan/tree", me);
                        message("vision",query("name", me)+"一脸倦容地从树林中钻了出来。\n",environment(me),me);
                             write("你走了半天，终于走出了这片树林。\n");
                             return -1;
                 } else
                if( query_temp("zhongnan/tree", me)<i )
                {
                        message("vision",query("name", me)+"胡乱地在树林中钻来钻去。\n",environment(me),me);
                        msg="你走了几步，发现你走进了树林的更深处。\n";
                } else
                if( query_temp("zhongnan/tree", me) == i )
                {
                        message("vision",query("name", me)+"钻进了树林，可是一会儿又走回了原地。\n",environment(me),me);
                        msg="你钻进了树林，可是一会儿又走回了原地。\n";
                } else
                {
                        message("vision",query("name", me)+"似乎胸有成竹地钻进了树林里。\n",environment(me),me);
                        msg="你走了几步，发现这儿你似乎曾经走过。\n";
                }
                return notify_fail(msg);//::valid_leave(me,dir);
        }else 
        if( query_temp("dugu_visit", me) == 1 )
        {        if(dir=="north")
                {
                        message("vision",query("name", me)+"向树林深处走去，消失树林之中……\n",environment(me),me);
                        me->move(__DIR__"qiaobi");
                        delete_temp("dugu_visit", me);
                        message("vision",query("name", me)+"从树林中走了过来。\n",environment(me),me);
                        write("你往北走了里许，来到了一座峭壁之前。\n");
                        return -1;
                } else
                {
                        message_vision("$N在树林里信步而行，边走边欣赏风景。\n",me);
                        return ::valid_leave(me,dir);
                }
        }
}
