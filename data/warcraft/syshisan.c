// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("混世石猴[2;37;0m[2;37;0m", ({"houwang"}));        
        set("gender", "男性");                
        set("long", "混世石猴[2;37;0m
它是芳华剑盟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "syshisan");
        set("owner_name", "芳华剑盟");
        set_temp("owner", "syshisan");
        set_temp("owner_name", "芳华剑盟");
        ::setup();
}
