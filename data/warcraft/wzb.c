// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小样的[2;37;0m[2;37;0m", ({"wzbpet"}));        
        set("gender", "女性");                
        set("long", "小样的[2;37;0m
它是揪星星的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wzb");
        set("owner_name", "揪星星");
        set_temp("owner", "wzb");
        set_temp("owner_name", "揪星星");
        ::setup();
}
