// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火凤凰[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火凤凰[2;37;0m
它是丹书的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dagb");
        set("owner_name", "丹书");
        set_temp("owner", "dagb");
        set_temp("owner_name", "丹书");
        ::setup();
}
