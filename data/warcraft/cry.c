// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哭哭[2;37;0m[2;37;0m", ({"ooo"}));        
        set("gender", "女性");                
        set("long", "哭哭[2;37;0m
它是哭哭喔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cry");
        set("owner_name", "哭哭喔");
        set_temp("owner", "cry");
        set_temp("owner_name", "哭哭喔");
        ::setup();
}
