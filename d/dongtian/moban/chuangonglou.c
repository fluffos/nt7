// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "传功楼");
        set("long", 
"传功楼所有建筑都是用一种赤红色的奇异石材所筑，台阶栏杆，莫不如\n"
"此。整个传功楼高大雄伟，呈现出宝塔形状，共有三层，每高一层，便比下\n"
"面小了一半左右，但是每一层看上去几乎都有不可思议的十丈之高。远远往\n"
"上望去，整个传功楼如若一团巨大燃烧的赤红火焰，直刺苍穹，站在楼下，\n"
"如同蝼蚁一般，顿感渺小无法往上移步。\n"        
);
                //set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "west" : __DIR__"zoulang24",
                        "up" : __DIR__"chuangonglou2",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user" ,3);
//        set("owner_level", 1);可以传授给外人，隐身者和冒险者等等
        
        setup();
}

int valid_leave(object me, string dir)
{
        object gcroom = get_object(__DIR__"guangchang.c");

                if(query("dongtian/chuangong/visit_time", me)>time() && wiz_level(me) < 5 && dir=="up") {
                                tell_object(me, NOR "你等一段时间才能再上去。\n" NOR);  
                                me->start_busy(2);
                                return -1;      
                }
                
        return ::valid_leave(me, dir);
}

void init()
{
        object me = this_player();
        
        if (playerp(me)) write(NOR "脱下所有东西，包括鞋袜再上二楼去，千万不要自误。\n" NOR);

        ::init();
}
