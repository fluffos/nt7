// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大胖马[2;37;0m[2;37;0m", ({"qqq"}));        
        set("gender", "男性");                
        set("long", "大胖马[2;37;0m
它是阿多二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonisb");
        set("owner_name", "阿多二");
        set_temp("owner", "adonisb");
        set_temp("owner_name", "阿多二");
        ::setup();
}
