// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m朱雀[2;37;0m[2;37;0m", ({"mecctpet"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是桃花潭水的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mecct");
        set("owner_name", "桃花潭水");
        set_temp("owner", "mecct");
        set_temp("owner_name", "桃花潭水");
        ::setup();
}
