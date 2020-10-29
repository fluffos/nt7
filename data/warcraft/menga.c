// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m哒哒[2;37;0m[2;37;0m", ({"dada"}));        
        set("gender", "男性");                
        set("long", "哒哒[2;37;0m
它是萌萌哒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "menga");
        set("owner_name", "萌萌哒");
        set_temp("owner", "menga");
        set_temp("owner_name", "萌萌哒");
        ::setup();
}
