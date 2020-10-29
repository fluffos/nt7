// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("京香[2;37;0m[2;37;0m", ({"julia"}));        
        set("gender", "女性");                
        set("long", "兜腏ulia[2;37;0m
它是答答的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "reply");
        set("owner_name", "答答");
        set_temp("owner", "reply");
        set_temp("owner_name", "答答");
        ::setup();
}
