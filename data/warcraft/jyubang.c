// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("帮居于[2;37;0m[2;37;0m", ({"bangjyu"}));        
        set("gender", "女性");                
        set("long", "帮居于[2;37;0m
它是居于帮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jyubang");
        set("owner_name", "居于帮");
        set_temp("owner", "jyubang");
        set_temp("owner_name", "居于帮");
        ::setup();
}
