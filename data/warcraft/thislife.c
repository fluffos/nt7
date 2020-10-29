// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("卢[2;37;0m[2;37;0m", ({"lrj"}));        
        set("gender", "男性");                
        set("long", "卢[2;37;0m
它是今生今世的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "thislife");
        set("owner_name", "今生今世");
        set_temp("owner", "thislife");
        set_temp("owner_name", "今生今世");
        ::setup();
}
