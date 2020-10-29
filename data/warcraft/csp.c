// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m饕餮[2;37;0m[2;37;0m", ({"taotie"}));        
        set("gender", "男性");                
        set("long", "自己想想为什么他这么像lonely[2;37;0m
它是魏生金的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "csp");
        set("owner_name", "魏生金");
        set_temp("owner", "csp");
        set_temp("owner_name", "魏生金");
        ::setup();
}
