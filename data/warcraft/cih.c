// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m瑞兽[2;37;0m[2;37;0m", ({"gyill"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是眼总的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cih");
        set("owner_name", "眼总");
        set_temp("owner", "cih");
        set_temp("owner_name", "眼总");
        ::setup();
}
