// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "精舍");
        set("long", @LONG
这座精舍全是以绿色大方竹搭成，屋外攀满青藤，使人一见之下心中
顿生凉意。周围环以奇花异草，闻之足可忘俗。精舍虽看似粗糙，但细观
之下，却发觉精舍竟与四周景物浑然天成，如同自然生成的一般，当真是
巧夺天工，好一片清凉洞天。西面有条小径通向桃花深处，门前有一对白
雕(diao)。
LONG );
         set("exits", ([
                       "west"  : __DIR__"taolin",
                "south" : __DIR__"bibochi",
                "enter" : __DIR__"shuilong",
        ]));

        set("item_desc", ([
                "diao" : "一对白雕正展翅欲飞。如果是桃花岛的弟子，\n"
                "骑上(mount)就可以飞到中原。\n",
        ]));
        
         set("objects", ([
                 "/d/taohua/npc/shagu" : 1,
                "/d/taohua/npc/shitong" : 1,
                CLASS_D("taohua") + "/first" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        "/clone/board/taohua_b"->foo();
}

int valid_leave(object me, string dir)
{

        if( (query("family/master_name", me) != "程英" )
         && (query("family/master_name", me) != "黄药师" )
         && userp(me)
         && (!query_temp("shagu_pass", me) )
        && (dir == "enter")
        && present("sha gu", this_object()) )
        return notify_fail("\n傻姑傻笑了几声，伸开双手一拦，说到：要进去先陪我玩一会儿吧，\n这里人都不理我，闷死了！\n");
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_ride", "mount");
}
int do_ride(string arg)
{
        mapping myfam;
        object ob = this_player () ;
        
        myfam=query("family", ob);
/*
        if( !myfam || myfam["family_name"] != "桃花岛" || !query("out_family", ob) )
        {
                message_vision("$N一跃身跨上了白雕。只见白雕仰天长唳，突然猛然一颠......\n" +
                               HIR "结果$N摔了个鼻青脸肿！\n" NOR +
                               "看来白雕对$N并不感兴趣，它只认识桃花岛的弟子。\n" , ob ) ;
                ob -> receive_damage ("qi", 50) ;
                ob -> receive_wound  ("qi", 50) ;
                return 1;
        }
*/
        if( (int)query("sb_ride") ) 
                return notify_fail("现在白雕正忙着,请过一会再乘坐!\n" ) ;
        addn("sb_ride", 1) ;
        message_vision("$N一跃身跨上了白雕。只见白雕仰天长唳，突然展翅高飞。\n\n"
                       "但看一雕一人身形渐渐缩小，终至不见。\n" , ob );
        ob->move("/d/taohua/lantian") ;
        tell_object(ob, CYN  "\n你不断地飞呀飞，万水千山身下飘过 ......\n\n" NOR ) ;
        call_out("taohua", 2 , ob );
        addn("sb_ride", -1) ;
        return 1 ;
}
void taohua( object ob )
{
        if (base_name(environment(ob)) != "/d/taohua/lantian")
                return;
        tell_object(ob, "你终于飞到了中原，白雕落了下来。\n\n"  ) ;
        ob -> move ("/d/guiyun/dayuan");
}
