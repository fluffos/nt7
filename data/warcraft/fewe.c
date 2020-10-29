// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白白白[2;37;0m[2;37;0m", ({"baii"}));        
        set("gender", "女性");                
        set("long", "白白白[2;37;0m
它是变形金的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fewe");
        set("owner_name", "变形金");
        set_temp("owner", "fewe");
        set_temp("owner_name", "变形金");
        ::setup();
}
