// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是黄金绕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tvybun");
        set("owner_name", "黄金绕");
        set_temp("owner", "tvybun");
        set_temp("owner_name", "黄金绕");
        ::setup();
}
