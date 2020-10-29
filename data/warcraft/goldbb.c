// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("牛[2;37;0m[2;37;0m", ({"goldbbb"}));        
        set("gender", "男性");                
        set("long", "牛[2;37;0m
它是金牛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldbb");
        set("owner_name", "金牛");
        set_temp("owner", "goldbb");
        set_temp("owner_name", "金牛");
        ::setup();
}
