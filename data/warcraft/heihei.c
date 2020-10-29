// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m跟班[2;37;0m[2;37;0m", ({"genban"}));        
        set("gender", "男性");                
        set("long", "黑黑的跟班[2;37;0m
它是黑黑的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "heihei");
        set("owner_name", "黑黑");
        set_temp("owner", "heihei");
        set_temp("owner_name", "黑黑");
        ::setup();
}
