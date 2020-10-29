// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("马[2;37;0m[2;37;0m", ({"jkw"}));        
        set("gender", "男性");                
        set("long", "马[2;37;0m
它是万里无云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sangtelaqi");
        set("owner_name", "万里无云");
        set_temp("owner", "sangtelaqi");
        set_temp("owner_name", "万里无云");
        ::setup();
}
