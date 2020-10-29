// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m赤磷蝎[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "五毒神兽[2;37;0m
它是沐雨星的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "anyer");
        set("owner_name", "沐雨星");
        set_temp("owner", "anyer");
        set_temp("owner_name", "沐雨星");
        ::setup();
}
