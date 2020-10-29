inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "渡船");
        set("long",
"[1;32m一叶小舟，最多也就能载七个人。一名精灵族的老艄公，手\n"
"持长竹篙，正在船尾吃力地撑着船。\n"
);
        set("no_clean_up", 0);
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
