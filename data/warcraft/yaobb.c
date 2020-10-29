// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("毕碧碧[2;37;0m[2;37;0m", ({"yaobbb"}));        
        set("gender", "男性");                
        set("long", "毕碧碧[2;37;0m
它是药哔哔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaobb");
        set("owner_name", "药哔哔");
        set_temp("owner", "yaobb");
        set_temp("owner_name", "药哔哔");
        ::setup();
}
