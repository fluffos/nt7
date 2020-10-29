// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大白马[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "大白马[2;37;0m
它是阿多三的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonisc");
        set("owner_name", "阿多三");
        set_temp("owner", "adonisc");
        set_temp("owner_name", "阿多三");
        ::setup();
}
