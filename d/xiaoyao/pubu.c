// pubu.c 
// Modified by Lonely June.25 2000

inherit ROOM;

#include <ansi.h>
void create()
{
        set("short", "玉壁瀑布");
        set("long", @LONG
循小路直往后山深处，猛听得水声响亮，轰轰隆隆，便如潮水大至
一般，抬头一看，只见西北角上犹如银河倒悬，一条大瀑布从高崖上直
泻下来。玉壁之前就是剑湖，湖西又是万丈深谷，云雾弥漫，望不到尽
头。。。。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "southdown" : "/d/wuliang/road6",
        ]));
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("coor/x", -71020);
        set("coor/y", -79870);
        set("coor/z", 110);
        setup();
}
 
void init()
{
        add_action("do_jump","jump");
}

int do_jump(string arg)
{
        object ob;
        int new_jing;
        ob = this_player();
        if( query_temp("marks/wuliang", ob) != 1 )
                return notify_fail("有人追杀你啊？这么急想要跳崖自杀？\n");
        new_jing=random(query("max_jing", ob)*3);
        if( new_jing>query("jing", ob))new_jing=query("jing", ob)+1;
        if( !arg || arg=="" ) return 0;
        if( arg != "down" )
                return notify_fail("你想要跳崖自杀？这么想不开啊？\n");
        tell_object(ob, HIR"你不加思索，纵身一跃，跳下了悬崖。。。。\n"NOR);
        message("vision",NOR"只见"+query("name", ob)+"万念俱灰，纵身跳入了悬崖之中。。。。\n"NOR,environment(ob),ob);
        if( (random(query("kar", ob))<5) && (ob->query_skill("dodge")<30) )
        {
                ob->die();
                return 1;
        }
        addn("jing", 0-new_jing, ob);
        ob->move(__DIR__"yanfeng");
        return 1;
}