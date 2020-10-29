// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("雌的[2;37;0m[2;37;0m", ({"cid"}));        
        set("gender", "女性");                
        set("long", "雌的[2;37;0m
它是小九的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xju");
        set("owner_name", "小九");
        set_temp("owner", "xju");
        set_temp("owner_name", "小九");
        ::setup();
}
