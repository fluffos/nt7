// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("渣渣[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "你是咋咋[2;37;0m
它是湖中的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wash");
        set("owner_name", "湖中");
        set_temp("owner", "wash");
        set_temp("owner_name", "湖中");
        ::setup();
}
