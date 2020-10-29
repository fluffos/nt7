// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天音[2;37;0m[2;37;0m", ({"lov"}));        
        set("gender", "女性");                
        set("long", "记忆中的声音……[2;37;0m
它是白朔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "drggg");
        set("owner_name", "白朔");
        set_temp("owner", "drggg");
        set_temp("owner_name", "白朔");
        ::setup();
}
