// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m黑[1;34m魔[1;32m天[1;35m焰[2;37;0m[2;37;0m", ({"fireheart"}));        
        set("gender", "男性");                
        set("long", "hp -m[2;37;0m
它是辰战的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chengen");
        set("owner_name", "辰战");
        set_temp("owner", "chengen");
        set_temp("owner_name", "辰战");
        ::setup();
}
