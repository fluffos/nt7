// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天乐龙[2;37;0m[2;37;0m", ({"ttlong"}));        
        set("gender", "女性");                
        set("long", "天乐龙[2;37;0m
它是黑雨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qwer");
        set("owner_name", "黑雨");
        set_temp("owner", "qwer");
        set_temp("owner_name", "黑雨");
        ::setup();
}
