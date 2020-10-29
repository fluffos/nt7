// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大河马[2;37;0m[2;37;0m", ({"xlqxca"}));        
        set("gender", "女性");                
        set("long", "丑就是丑[2;37;0m
它是乌索普的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xlqxc");
        set("owner_name", "乌索普");
        set_temp("owner", "xlqxc");
        set_temp("owner_name", "乌索普");
        ::setup();
}
