// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"cbookpet"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是墨三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cbook");
        set("owner_name", "墨三");
        set_temp("owner", "cbook");
        set_temp("owner_name", "墨三");
        ::setup();
}
