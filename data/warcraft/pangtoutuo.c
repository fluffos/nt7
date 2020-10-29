// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大胖[2;37;0m[2;37;0m", ({"panghu"}));        
        set("gender", "男性");                
        set("long", "一头很胖很胖的麒麟[2;37;0m
它是胖虎的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pangtoutuo");
        set("owner_name", "胖虎");
        set_temp("owner", "pangtoutuo");
        set_temp("owner_name", "胖虎");
        ::setup();
}
