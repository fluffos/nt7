// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m雀儿[2;37;0m[2;37;0m", ({"lupuss"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是冰露儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lupus");
        set("owner_name", "冰露儿");
        set_temp("owner", "lupus");
        set_temp("owner_name", "冰露儿");
        ::setup();
}
