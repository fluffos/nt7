// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m捌研[2;37;0m[2;37;0m", ({"kosyjhpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyjh");
        set("owner_name", "研捌");
        set_temp("owner", "kosyjh");
        set_temp("owner_name", "研捌");
        ::setup();
}
