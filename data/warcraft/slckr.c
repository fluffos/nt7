// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m飞行太保[2;37;0m[2;37;0m", ({"flying"}));        
        set("gender", "男性");                
        set("long", "$HIB$飞行太保[2;37;0m
它是风行者的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "slckr");
        set("owner_name", "风行者");
        set_temp("owner", "slckr");
        set_temp("owner_name", "风行者");
        ::setup();
}
