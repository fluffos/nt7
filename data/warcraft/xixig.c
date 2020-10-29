// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跟飞翔[2;37;0m[2;37;0m", ({"xixiggg"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是习跟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixig");
        set("owner_name", "习跟");
        set_temp("owner", "xixig");
        set_temp("owner_name", "习跟");
        ::setup();
}
