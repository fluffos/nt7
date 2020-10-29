// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泥煤[2;37;0m[2;37;0m", ({"nmride"}));        
        set("gender", "女性");                
        set("long", "泥煤[2;37;0m
它是柴米油盐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nmi");
        set("owner_name", "柴米油盐");
        set_temp("owner", "nmi");
        set_temp("owner_name", "柴米油盐");
        ::setup();
}
