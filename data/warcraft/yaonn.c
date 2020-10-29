// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你你你[2;37;0m[2;37;0m", ({"yaonnn"}));        
        set("gender", "男性");                
        set("long", "你你你[2;37;0m
它是药妞妞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaonn");
        set("owner_name", "药妞妞");
        set_temp("owner", "yaonn");
        set_temp("owner_name", "药妞妞");
        ::setup();
}
