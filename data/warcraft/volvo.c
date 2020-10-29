// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"vlv"}));        
        set("gender", "女性");                
        set("long", "111[2;37;0m
它是斯巴鲁的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "volvo");
        set("owner_name", "斯巴鲁");
        set_temp("owner", "volvo");
        set_temp("owner_name", "斯巴鲁");
        ::setup();
}
