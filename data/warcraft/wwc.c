// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m本体[1;31m三呜[2;37;0m[2;37;0m", ({"wwcc"}));        
        set("gender", "女性");                
        set("long", "呜呜[2;37;0m
它是三呜呜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwc");
        set("owner_name", "三呜呜");
        set_temp("owner", "wwc");
        set_temp("owner_name", "三呜呜");
        ::setup();
}
