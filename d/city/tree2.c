#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大榕树上");
        set("long", @LONG
人说大树底下好乘凉，没想到大树上更凉快。这棵大榕树真不愧
为千年神木，至今仍绿叶繁茂。当你抬头往上看的时候似乎有个影在
树梢之间移动，不过也许是风吹动所造成的错觉。
LONG
        );

        set("exits", ([
                "up"  : __DIR__"kedian4",
                "down": __DIR__"tree",
                "east"  : "/clone/game/mjroom",
                "west"  : "/clone/game/changan_dufang",
        ]));
        set("objects", ([
                "/adm/npc/obj/cbrune" : 1,
                "/adm/npc/obj/cbgem"  : 1,
        ]));
        
        set("no_fight", 1);

        setup();
}

void init()
{
        add_action("do_jump","climb");
}

int do_jump(string arg)
{
        object me;
        
        me = this_player();
        if( !arg || arg != "down") 
                return notify_fail("你要往哪个方向爬？\n");

        if( query("gender", me) != "女性" )
                message("vision",
                        me->name() + "气喘嘘嘘的抓住树干，屁股一扭一扭地往下爬去。\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision",
                        me->name() + "象仙子般继续向下飘去，转瞬即逝。\n",
                        environment(me), ({me}) );
        else 
                message("vision",
                        me->name() + "战战兢兢的抓住树干往下爬去。\n",    environment(me), ({me}) );
        
        me->move(__DIR__"tree");
     
        if( query("gender", me) != "女性" )
                message("vision",
                        me->name() + "气喘嘘嘘地从上面爬了下来。\n",
                        environment(me), ({me}) );
        else 
        if( query("age", me)<40 && query("per", me)>24 )
                message("vision","一阵清香飞来，你定眼一看，"+
                        me->name() + "已经婷婷玉立在你眼前。\n",
                        environment(me), ({me}) );   
          
        else 
                message("vision", me->name() + "战战兢兢地从上面爬了下来。\n", 
                        environment(me), ({me}) );   
        
        return 1;
}   

int valid_leave(object me, string dir)
{
        if ( dir=="down" && !wizardp(me))
                return notify_fail("这里没法直接走，看来你只能爬(climb)下去！\n");

        return 1;
}
