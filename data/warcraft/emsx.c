// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是罗丽控的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emsx");
        set("owner_name", "罗丽控");
        set_temp("owner", "emsx");
        set_temp("owner_name", "罗丽控");
        ::setup();
}
