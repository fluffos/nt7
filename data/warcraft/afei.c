// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("土狗[2;37;0m[2;37;0m", ({"tug"}));        
        set("gender", "男性");                
        set("long", "土狗[2;37;0m
它是小飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "afei");
        set("owner_name", "小飞");
        set_temp("owner", "afei");
        set_temp("owner_name", "小飞");
        ::setup();
}
