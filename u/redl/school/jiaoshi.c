// This program is a part of NITAN MudLIB 
// redl 2013/8
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

int clean_up() { return 1;}

void create()
{
        set("short", "学堂教室");
        set("long", 
"这是一间崭新整洁的教室，明亮的阳光从玻璃窗外透射进来。教室正\n"
"前方墙壁上是块高大结实的黑板，黑板上写着一排大字“治世道，乱世佛\n"
"，由治到乱是儒家”。教室中间随意摆放着几排书桌和凳子，桌子上散落\n"
"着各种笔墨纸砚。\n"
);
                //set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"caochang",
                ]));
                set("objects", ([ 
                        __DIR__"npc/xue" : 1,
        ])); 

        set("no_dazuo",1);
        set("no_kill",1);
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_magic", 1); 
        set("no_sleep_room", 1); 
        
        setup();
}

void init()
{
        object ob = this_player();
        if (base_name(ob)=="/clone/user/baby") {
                ob->command("halt");
                message_vision(CYN + "$N" + CYN + "紧张地左右张望了一阵，找了个书桌空位坐下。\n" + NOR, ob);
        }
}

  
