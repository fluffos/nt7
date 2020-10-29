// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("饕餮[2;37;0m[2;37;0m", ({"mummmy"}));        
        set("gender", "女性");                
        set("long", "饕餮[2;37;0m
它是木乃伊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mummy");
        set("owner_name", "木乃伊");
        set_temp("owner", "mummy");
        set_temp("owner_name", "木乃伊");
        ::setup();
}
