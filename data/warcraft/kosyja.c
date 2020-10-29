// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m壹研[2;37;0m[2;37;0m", ({"kosyjapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是研壹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosyja");
        set("owner_name", "研壹");
        set_temp("owner", "kosyja");
        set_temp("owner_name", "研壹");
        ::setup();
}
