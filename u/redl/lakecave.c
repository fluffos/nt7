// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create()
{
        set("short", "山洞");
        set("long", 
"这是山腹里一片很宽阔的地方，顶高七八丈，方圆四五十丈。洞的正\n"
"中央有一座传送阵("CYN"enter"NOR")，阵旁台上有张蒲团，结跏趺坐着一个道人。\n"
);

         set("exits",([ /* sizeof() == 1 */
                 "enter" : __DIR__"suistone",
         ]));

        set("objects", ([
                __DIR__"obj/daoren" : 1,
        ]));

                set("no_rideto", 1);
                set("no_flyto", 1);
                        set("get_time", time());
        setup();
        
}

int valid_leave(object me, string dir)
{
                if (objectp(present("dao ren", this_object()))) {
                tell_object(me, NOR "你幻听到“哼..”的一声，眼前一阵模糊，竟未能离开原地半步。\n" NOR);
                return -1;
                }
        if (dir == "enter" && playerp(me)) {
                tell_object(me, YEL "你振了振衣袖，强作镇定地跨进了传送阵。\n" NOR
                                                HIY "空间乱流不停地撕裂扭曲，转眼到了随风石。\n" NOR);
        }

        return ::valid_leave(me, dir);
}

