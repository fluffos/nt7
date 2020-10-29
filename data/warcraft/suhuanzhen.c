// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("琉璃仙境[2;37;0m[2;37;0m", ({"susu"}));        
        set("gender", "男性");                
        set("long", "琉璃仙境[2;37;0m
它是素还真的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "suhuanzhen");
        set("owner_name", "素还真");
        set_temp("owner", "suhuanzhen");
        set_temp("owner_name", "素还真");
        ::setup();
}
