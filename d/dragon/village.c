inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "精灵村落");
        set("long",
"[1;32m眼前是几处极为普通的村舍，几个精灵族的小孩子正在屋外\n"
"追逐打闹，几只肥肥的大白鹅，看见你来，伸长了脖子嘎嘎的叫，似乎奇\n"
"怪你居然找到了这里。这里每当夕阳西下的时候，厚厚的茅草毡成的屋顶\n"
"便会被淡淡的炊烟罩住，整个村里弥漫着一股诱人的米饭的香味。\n"
);
        set("exits", ([ /* sizeof() == 4 */
   "south" : __DIR__"lake",
   "west" : __DIR__"spirit10",
   "east" : __DIR__"zhanglao",
   ]));

        set("no_magic", 1);
        setup();
        replace_program(ROOM);

}

