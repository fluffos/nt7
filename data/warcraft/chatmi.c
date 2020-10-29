// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("洞房不败[2;37;0m[2;37;0m", ({"chatmism"}));        
        set("gender", "男性");                
        set("long", "撒旦发[2;37;0m
它是信息的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chatmi");
        set("owner_name", "信息");
        set_temp("owner", "chatmi");
        set_temp("owner_name", "信息");
        ::setup();
}
