// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m张扬[2;37;0m[2;37;0m", ({"wwbzy"}));        
        set("gender", "男性");                
        set("long", "扬哥出手，天下我有！[2;37;0m
它是李小胖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "forred");
        set("owner_name", "李小胖");
        set_temp("owner", "forred");
        set_temp("owner_name", "李小胖");
        ::setup();
}
