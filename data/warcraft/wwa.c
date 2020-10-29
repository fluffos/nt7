// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m本体[1;31m大呜[2;37;0m[2;37;0m", ({"wwaa"}));        
        set("gender", "女性");                
        set("long", "呜呜[2;37;0m
它是大呜呜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwa");
        set("owner_name", "大呜呜");
        set_temp("owner", "wwa");
        set_temp("owner_name", "大呜呜");
        ::setup();
}
