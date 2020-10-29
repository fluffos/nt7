// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大青龙[2;37;0m[2;37;0m", ({"ajumper"}));        
        set("gender", "男性");                
        set("long", "钟离汉的大青龙[2;37;0m
它是钟离汉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ajump");
        set("owner_name", "钟离汉");
        set_temp("owner", "ajump");
        set_temp("owner_name", "钟离汉");
        ::setup();
}
