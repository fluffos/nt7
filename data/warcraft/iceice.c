// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m紫玉[1;33m麒麟[2;37;0m[2;37;0m", ({"iceicer"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是冰冰凉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "iceice");
        set("owner_name", "冰冰凉");
        set_temp("owner", "iceice");
        set_temp("owner_name", "冰冰凉");
        ::setup();
}
