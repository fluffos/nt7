// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骡子[2;37;0m[2;37;0m", ({"luozi"}));        
        set("gender", "男性");                
        set("long", "骡子[2;37;0m
它是钱是多的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "moneymmmb");
        set("owner_name", "钱是多");
        set_temp("owner", "moneymmmb");
        set_temp("owner_name", "钱是多");
        ::setup();
}
