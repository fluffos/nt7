// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("保时捷[2;37;0m[2;37;0m", ({"bluedragon"}));        
        set("gender", "男性");                
        set("long", "保时捷[2;37;0m
它是令狐崇的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "rsdamia");
        set("owner_name", "令狐崇");
        set_temp("owner", "rsdamia");
        set_temp("owner_name", "令狐崇");
        ::setup();
}
