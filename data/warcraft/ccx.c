// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ccxx"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是学习的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ccx");
        set("owner_name", "学习");
        set_temp("owner", "ccx");
        set_temp("owner_name", "学习");
        ::setup();
}
