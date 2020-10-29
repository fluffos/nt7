// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("明明[2;37;0m[2;37;0m", ({"mingming"}));        
        set("gender", "女性");                
        set("long", "好[2;37;0m
它是明教的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ming");
        set("owner_name", "明教");
        set_temp("owner", "ming");
        set_temp("owner_name", "明教");
        ::setup();
}
