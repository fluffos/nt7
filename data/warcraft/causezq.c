// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪猪[2;37;0m[2;37;0m", ({"causeqz"}));        
        set("gender", "男性");                
        set("long", "猪猪[2;37;0m
它是牛五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "causezq");
        set("owner_name", "牛五");
        set_temp("owner", "causezq");
        set_temp("owner_name", "牛五");
        ::setup();
}
