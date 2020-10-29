// This program is a part of NITAN MudLIB
// redl 2013/5
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "湖心木屋");
        set("long",
"','''╭⌒╮⌒╮.',''',,',.'',,','',.   \n"
"    ╱◥██◣''o花落香陨人不在o.'',,',.   \n"
"   ｜田｜田田│ '',,',.o青石小阶满青苔o   \n"
" ------------------≈≈≈--≈≈--≈≈≈\n"
);
         set("outdoors", "chengdu");
         set("exits",([ /* sizeof() == 1 */
                 "westdown" : __DIR__"lakeroad",
                 "enter" : __DIR__"lakehouse2",
                  //"east": "/u/gigi/swing",
         ]));

                set("no_rideto", 1);
                set("no_flyto", 1);
                      set("no_magic", 1);

        setup();
}
