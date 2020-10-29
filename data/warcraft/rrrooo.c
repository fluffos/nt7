// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"rrroooma"}));        
        set("gender", "男性");                
        set("long", "小马[2;37;0m
它是江一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "rrrooo");
        set("owner_name", "江一");
        set_temp("owner", "rrrooo");
        set_temp("owner_name", "江一");
        ::setup();
}
