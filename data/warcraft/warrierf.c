// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是乌当忆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "warrierf");
        set("owner_name", "乌当忆");
        set_temp("owner", "warrierf");
        set_temp("owner_name", "乌当忆");
        ::setup();
}
