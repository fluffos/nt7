// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m朱雀[2;37;0m[2;37;0m", ({"zqq"}));        
        set("gender", "女性");                
        set("long", "$RED$朱雀[2;37;0m
它是成峰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chenb");
        set("owner_name", "成峰");
        set_temp("owner", "chenb");
        set_temp("owner_name", "成峰");
        ::setup();
}
