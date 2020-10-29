// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[41m贼马[2;37;0m[2;37;0m", ({"zmuds"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是贼马德的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zmud");
        set("owner_name", "贼马德");
        set_temp("owner", "zmud");
        set_temp("owner_name", "贼马德");
        ::setup();
}
