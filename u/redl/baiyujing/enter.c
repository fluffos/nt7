// This program is a part of NITAN MudLIB 
// redl 2013/3
#include <ansi.h>

#define TIME_INTERVAL 86400     

inherit ROOM;

int clean_up() { return 1;}

int do_restart()
{
        set("byj/entertime", time());//用途等于uid
        return 1;
}

void set_can_up()
{
        remove_call_out("set_can_up");
        do_restart();
        call_out("set_can_up", TIME_INTERVAL);
}

void create()
{
        set("short", "玉京山");
        set("long",
"这里是玉京山顶，白色的薄雾缭绕中，隐约传来许多鸟鸣声。朦胧中\n"
"只见几条小路分别通向各方。路中间一块牌子上写着："+CYN+"正中（经验）北方\n"
"（潜能）南方（金钱）西方（精力）东方（内力）.红莲老祖二零一三年。\n"
);

        set("exits", ([
                "south"   : "/u/redl/workroom", 
                "up"   : __DIR__"byjxx",
                "northup"   : __DIR__"byjxx",
                "southup"   : __DIR__"byjxx",
                "westup"   : __DIR__"byjxx",
                "eastup"   : __DIR__"byjxx",
        ]));
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1); 
                set("no_clean_up", 1);
                set("no_fight", "1"); 
        setup();
        set_can_up();
}

void init()
{
        object me = this_player();
}


int valid_leave(object me, string dir)
{
        object *inv, ob;
        if (dir != "south"){
                if (!playerp(me)) return -1;
//              if (me->is_busy()) {
//                      tell_object(me,NOR + "你的动作还没有完成，不能移动！\n" + NOR); 
//                      return 1; 
//              }

                me->start_busy(2+random(2));
                
                if ( query("byj/entertime") == query("byj/entertime", me) ){
                        tell_object(me,NOR"今天你以及来过了，别太贪心了啊。\n"NOR); 
                        return -1; 
                }

        if( me->in_team() ) {
           tell_object(me, "你不能组队上去！\n");
           return -1;
        }

                if ( objectp(query_temp("is_riding", me)) ) return notify_fail("你骑着马没法上去！\n");

                ob = find_object(__DIR__"byjxx"); 

                if (ob) {
                inv = deep_inventory(ob);
                if( sizeof(inv) > 0 ) {
                    foreach( object ob3 in inv ) {
                                if( playerp(ob3) ) {
                                    tell_object(me,NOR"你再等等吧，现在"+query("name",ob3)+NOR+"正在"+HIC+query("short",ob)+NOR+"上神游！\n"NOR); 
                                        return -1;
                                }
                        }
                }
                }

                if (ob) destruct(ob);
                load_object(__DIR__"byjxx.c")->create();
                delete_temp("byj", me);//防止玩家没有quit过
                set("byj/entertime", query("byj/entertime"), me);
                
        }
        return ::valid_leave(me, dir);
}
