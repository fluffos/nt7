// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create()
{
        set("short", "青石小阶");
        set("long", 
"这是一条青石板铺就的路，半浸在湖水中，延伸向湖心的小岛上。走\n"
"过间隔着的数十个青石桥墩之后，青石小阶往东转向上，渐渐可见密林间\n"
"有棟木屋。\n"
);
         //set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
                "eastup" : __DIR__"lakehouse",
                "west" : __DIR__"lake",
        ]));

                set("no_rideto", 1);
                set("no_flyto", 1);
                      set("no_magic", 1); 
        
        setup();
        
        
                remove_call_out("do_wave");
                call_out("do_wave", 10);        
}

int do_wave()
{
                switch(random(11)) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        tell_room(this_object(), CYN "≈≈"NOR HIG "一阵微风吹过，梦湖上面泛起了千百层粼粼碧波。\n" NOR);
                        break;
                        case 4:
                        case 5:
                        case 6:
                        tell_room(this_object(), CYN "≈≈"NOR HIW "湖水在沙滩边慢涨渐落，竟也似潮信绵绵不绝。\n" NOR);
                        break;
                        case 7:
                        case 8:
                        tell_room(this_object(), CYN "≈≈"NOR HIC "碧浪轻轻拂过沙滩，就像情人温柔地吻过你的脚趾。\n" NOR);
                        break;
                        case 9:
                        tell_room(this_object(), CYN "≈≈"NOR HIY "一个大浪打来，冲湿了青石小阶，再悄悄退却。\n" NOR);
                        break;
                case 10:
                        tell_room(this_object(), CYN "≈≈"NOR HIB "岸边树木摇曳沙沙作响，湖心岛上的木屋却安静如初。\n" NOR);
                        break;
            }
        call_out("do_wave", 11 + random(5));              
        return 1;
}



