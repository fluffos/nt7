// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m语嫣[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "女性");                
        set("long", "$HIM$语嫣[2;37;0m
它是参透的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kkarby");
        set("owner_name", "参透");
        set_temp("owner", "kkarby");
        set_temp("owner_name", "参透");
        ::setup();
}
