// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m本体[1;31m五呜[2;37;0m[2;37;0m", ({"wwee"}));        
        set("gender", "女性");                
        set("long", "呜呜[2;37;0m
它是五呜呜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwe");
        set("owner_name", "五呜呜");
        set_temp("owner", "wwe");
        set_temp("owner_name", "五呜呜");
        ::setup();
}
