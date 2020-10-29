// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奇鳞[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是再世孔明的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lear");
        set("owner_name", "再世孔明");
        set_temp("owner", "lear");
        set_temp("owner_name", "再世孔明");
        ::setup();
}
