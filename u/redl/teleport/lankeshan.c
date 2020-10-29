// This program is a part of NITAN MudLIB  
// redl 2014/8
#include <ansi.h>  
#include <room.h>  
inherit __DIR__"normal.c";  

void create()
{
        set("short","天生石梁");
        set("long", @LONG
这里是烂柯山顶峰。左方有座石亭横书“日迟亭”，右边二人高
的石碑上面竖刻着“青霞第八洞天”。正前方有道拱如虬龙的天生石
梁，东西宽约十丈，彩虹一样高高架起，形成了个方圆百米的洞窟。
洞里幽风阵阵，清凉无比，确实是个参禅打坐的绝佳去处。
LONG );
        set("outdoors", "yangzhou");
        set("exits",([ /* sizeof() == 1 */
            "out"  : "/u/redl/teleport/teleport",
        ]));

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_magic", 1); 
        set("no_user_kill", 1); 
        set("no_sleep_room", 1);  
        setup();
}

int do_sit() 
{
        object me = this_player(); 
        string file = "/temp/qroom/" + query("id", me) + ".c";
                if (!sizeof(get_dir("/temp/qroom"))) mkdir("/temp/qroom");
        set_temp("time_enter_qroom", time() + 10, me);
        if (!(load_object(file))) 
        cp("/u/redl/teleport/qroom.c", file);
        tell_object(me, NOR CYN "你随意找了颗棋子盘腿一坐，眨眼就变幻了空间。\n" NOR); 
        me->move(file);
        return 1;
}


void init()  
{
        object me = this_player(); 
        if (query_temp("time_enter_qroom", me) < time()) {
                tell_object(me, NOR "你望着洞里阡陌纵横的棋盘，禁不住想找一颗棋子坐(" CYN "sit" NOR ")上去。\n" NOR); 
                add_action("do_sit","sit");  
        } else tell_object(me, NOR "你进出过于频繁，望着阡陌棋盘，似乎忘记了去处。\n" NOR); 
}  






