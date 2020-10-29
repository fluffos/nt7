// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m天猫[2;37;0m[2;37;0m", ({"tianmao"}));        
        set("gender", "女性");                
        set("long", "$HIW$天猫[2;37;0m
它是楚星的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xxckr");
        set("owner_name", "楚星");
        set_temp("owner", "xxckr");
        set_temp("owner_name", "楚星");
        ::setup();
}
