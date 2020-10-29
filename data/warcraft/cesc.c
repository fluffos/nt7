// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("唐大坑[2;37;0m[2;37;0m", ({"tangkd"}));        
        set("gender", "男性");                
        set("long", "坑爹货[2;37;0m
它是金晓辰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cesc");
        set("owner_name", "金晓辰");
        set_temp("owner", "cesc");
        set_temp("owner_name", "金晓辰");
        ::setup();
}
