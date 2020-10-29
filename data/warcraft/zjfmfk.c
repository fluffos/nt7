// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "涅槃重生[2;37;0m
它是乔峰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zjfmfk");
        set("owner_name", "乔峰");
        set_temp("owner", "zjfmfk");
        set_temp("owner_name", "乔峰");
        ::setup();
}
