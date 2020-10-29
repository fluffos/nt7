// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火凤凰[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火凤凰[2;37;0m
它是闹闹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dagc");
        set("owner_name", "闹闹");
        set_temp("owner", "dagc");
        set_temp("owner_name", "闹闹");
        ::setup();
}
