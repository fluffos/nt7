// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云儿[2;37;0m[2;37;0m", ({"ccloud"}));        
        set("gender", "男性");                
        set("long", "云儿[2;37;0m
它是云沙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "crane");
        set("owner_name", "云沙");
        set_temp("owner", "crane");
        set_temp("owner_name", "云沙");
        ::setup();
}
