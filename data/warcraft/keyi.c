// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "火[2;37;0m
它是可意的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "keyi");
        set("owner_name", "可意");
        set_temp("owner", "keyi");
        set_temp("owner_name", "可意");
        ::setup();
}
