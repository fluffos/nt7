// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m羽毛[2;37;0m[2;37;0m", ({"yumao"}));        
        set("gender", "男性");                
        set("long", "一只老虎[2;37;0m
它是羽弥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jsatz");
        set("owner_name", "羽弥");
        set_temp("owner", "jsatz");
        set_temp("owner_name", "羽弥");
        ::setup();
}
