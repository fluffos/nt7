// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidva"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星游的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidv");
        set("owner_name", "星游");
        set_temp("owner", "lidv");
        set_temp("owner_name", "星游");
        ::setup();
}
