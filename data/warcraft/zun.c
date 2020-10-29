// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小雀儿[2;37;0m[2;37;0m", ({"quer"}));        
        set("gender", "女性");                
        set("long", "胖乎乎的小雀儿[2;37;0m
它是敖不尊的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zun");
        set("owner_name", "敖不尊");
        set_temp("owner", "zun");
        set_temp("owner_name", "敖不尊");
        ::setup();
}
