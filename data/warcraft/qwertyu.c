// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"qwqwqwqwq"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是胡步步的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qwertyu");
        set("owner_name", "胡步步");
        set_temp("owner", "qwertyu");
        set_temp("owner_name", "胡步步");
        ::setup();
}
