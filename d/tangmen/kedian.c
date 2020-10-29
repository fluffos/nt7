#include <ansi.h>;
#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "客店");
        set("long",
"这是唐门所开的客栈，生意非常兴隆。外地游客多选择这里落脚，唐\n"
"门弟子可以自由的进出，睡觉也是免费的。唐小二里里外外忙得团团转，\n"
"接待来自五湖四海的朋友。客店的主人从不露面，他究竟是谁，有各种各\n"
"样的猜测。不过有点是所有来过的人都知道的：这儿是唐门的地盘，容不\n"
"得外姓人在此胡作非为。\n"
);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room", 1);
        set("item_desc", ([
                "paizi" : "。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"bdajie1",
                "up"   : __DIR__"kedian2",
        ]));

        setup();
        
}

int valid_leave(object me, string dir)
{          
        object ob;
        mapping myfam;

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("唐小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊！这里可是"+HIC"蜀中唐门"NOR+"啊\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        {     
                myfam=query("family", me);
                if (! myfam["family_name"] || myfam["family_name"] != "唐门世家")
                        return notify_fail("唐小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！旁人还以为小店伺候不周呢！\n");
                delete_temp("rent_paid", me);
                me->move("/d/tangmen/bdajie1");
                tell_object(me,"唐小二笑咪咪地说道：这位"+RANK_D->query_respect(ob)+"，欢迎再来"+HIG"唐门客店"NOR+"\n\n");
                return 1;
        }
        return ::valid_leave(me, dir);
}

