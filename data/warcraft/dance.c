// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("旖旎[2;37;0m[2;37;0m", ({"demon"}));        
        set("gender", "女性");                
        set("long", "温柔[2;37;0m
它是舞衣的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dance");
        set("owner_name", "舞衣");
        set_temp("owner", "dance");
        set_temp("owner_name", "舞衣");
        ::setup();
}
