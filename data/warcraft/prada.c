// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("包包[2;37;0m[2;37;0m", ({"bag"}));        
        set("gender", "女性");                
        set("long", "好贵[2;37;0m
它是骗人挨打的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "prada");
        set("owner_name", "骗人挨打");
        set_temp("owner", "prada");
        set_temp("owner_name", "骗人挨打");
        ::setup();
}
