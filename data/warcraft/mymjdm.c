// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("棋逢对手[2;37;0m[2;37;0m", ({"mydmgo"}));        
        set("gender", "女性");                
        set("long", "棋逢对手[2;37;0m
它是顶替于的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mymjdm");
        set("owner_name", "顶替于");
        set_temp("owner", "mymjdm");
        set_temp("owner_name", "顶替于");
        ::setup();
}
